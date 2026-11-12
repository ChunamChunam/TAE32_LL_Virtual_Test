using System.Text.RegularExpressions;
using ClangSharp.Interop;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.SDK.Parse;

/// <summary>
/// Register access from AST member refs + known SDK macros evidenced in original source.
/// Macro names alone are never enough; CallExpr and/or source-token evidence is required.
/// </summary>
public sealed class LlRegisterAccessAnalyzer
{
    private static readonly HashSet<string> RegMacros = new(StringComparer.Ordinal)
    {
        "SET_BIT", "CLEAR_BIT", "READ_BIT", "READ_BIT_SHIFT", "CLEAR_REG",
        "WRITE_REG", "READ_REG", "MODIFY_REG"
    };

    private static readonly Regex MacroCallRegex = new(
        @"\b(SET_BIT|CLEAR_BIT|READ_BIT|READ_BIT_SHIFT|CLEAR_REG|WRITE_REG|READ_REG|MODIFY_REG)\s*\(",
        RegexOptions.Compiled);

    private static readonly Regex MemberRegex = new(
        @"\b([A-Za-z_][A-Za-z0-9_]*)\s*->\s*([A-Za-z_][A-Za-z0-9_]*)",
        RegexOptions.Compiled);

    public void Analyze(CXCursor body, LlAstFunctionResult result)
    {
        var seen = new HashSet<string>(StringComparer.Ordinal);

        ClangCursorHelpers.VisitRecursive(body, (cursor, parent) =>
        {
            if (cursor.Kind == CXCursorKind.CXCursor_CallExpr)
                TryRegisterMacroCall(cursor, result, seen);
            else if (cursor.Kind == CXCursorKind.CXCursor_MemberRefExpr)
                TryMemberAccess(cursor, parent, result, seen);
            else if (cursor.Kind is CXCursorKind.CXCursor_BinaryOperator or CXCursorKind.CXCursor_CompoundAssignOperator)
                TryExpandedAssignment(cursor, result, seen);
        });

        // Correlate original (pre-expansion) source tokens for SDK register macros.
        CollectFromSourceText(result, seen);
    }

    private static void TryRegisterMacroCall(CXCursor call, LlAstFunctionResult result, HashSet<string> seen)
    {
        var name = GetCalleeName(call);
        if (name is null || !RegMacros.Contains(name))
            return;

        AddAccess(result, seen,
            ClassifyMacro(name),
            ClangCursorHelpers.GetSpelling(call),
            TryExtractRegisterPath(call),
            name,
            ClangCursorHelpers.GetStartLine(call),
            ClangCursorHelpers.GetEndLine(call),
            call.Kind.ToString());
    }

    private static void TryMemberAccess(CXCursor memberRef, CXCursor parent, LlAstFunctionResult result, HashSet<string> seen)
    {
        var path = BuildMemberPath(memberRef);
        if (path is null)
            return;

        var kind = IsWriteContext(parent) ? LlRegisterAccessKind.Write : LlRegisterAccessKind.Read;
        AddAccess(result, seen,
            kind,
            path,
            path,
            null,
            ClangCursorHelpers.GetStartLine(memberRef),
            ClangCursorHelpers.GetEndLine(memberRef),
            memberRef.Kind.ToString());
    }

    /// <summary>
    /// After macro expansion, SET_BIT/CLEAR_BIT/WRITE_REG become |= &= = on member exprs.
    /// </summary>
    private static void TryExpandedAssignment(CXCursor binary, LlAstFunctionResult result, HashSet<string> seen)
    {
        var children = ClangCursorHelpers.Children(binary);
        if (children.Count < 2)
            return;

        var lhs = children[0];
        if (lhs.Kind != CXCursorKind.CXCursor_MemberRefExpr)
            return;

        var path = BuildMemberPath(lhs);
        if (path is null)
            return;

        var spell = ClangCursorHelpers.GetSpelling(binary);
        var kind = spell.Contains("|=") || spell.Contains("&=")
            ? LlRegisterAccessKind.Modify
            : LlRegisterAccessKind.Write;

        // Prefer source-macro correlation when available; here record AST assignment evidence.
        AddAccess(result, seen,
            kind,
            spell,
            path,
            null,
            ClangCursorHelpers.GetStartLine(binary),
            ClangCursorHelpers.GetEndLine(binary),
            binary.Kind.ToString());
    }

    private static void CollectFromSourceText(LlAstFunctionResult result, HashSet<string> seen)
    {
        if (string.IsNullOrWhiteSpace(result.SourceText) || result.StartLine <= 0)
            return;

        var lines = result.SourceText.Replace("\r\n", "\n").Split('\n');
        for (var i = 0; i < lines.Length; i++)
        {
            var lineNo = result.StartLine + i;
            var line = lines[i];
            foreach (Match m in MacroCallRegex.Matches(line))
            {
                var macro = m.Groups[1].Value;
                string? path = null;
                var pathMatch = MemberRegex.Match(line[m.Index..]);
                if (pathMatch.Success)
                    path = $"{pathMatch.Groups[1].Value}->{pathMatch.Groups[2].Value}";

                AddAccess(result, seen,
                    ClassifyMacro(macro),
                    line.Trim(),
                    path,
                    macro,
                    lineNo,
                    lineNo,
                    "SourceMacroToken");
            }
        }
    }

    private static void AddAccess(
        LlAstFunctionResult result,
        HashSet<string> seen,
        LlRegisterAccessKind kind,
        string? expression,
        string? registerPath,
        string? macroName,
        int startLine,
        int endLine,
        string astKind)
    {
        var key = $"{startLine}|{macroName}|{registerPath}|{kind}|{expression}";
        if (!seen.Add(key))
            return;

        result.RegisterAccesses.Add(new LlRegisterAccess
        {
            AccessKind = kind.ToString(),
            Expression = expression,
            RegisterPath = registerPath,
            MacroName = macroName,
            StartLine = startLine,
            EndLine = endLine,
            AstKind = astKind
        });
    }

    private static LlRegisterAccessKind ClassifyMacro(string name) => name switch
    {
        "READ_REG" or "READ_BIT" or "READ_BIT_SHIFT" => LlRegisterAccessKind.Read,
        "WRITE_REG" or "SET_BIT" or "CLEAR_BIT" or "CLEAR_REG" => LlRegisterAccessKind.Write,
        "MODIFY_REG" => LlRegisterAccessKind.Modify,
        _ => LlRegisterAccessKind.Test
    };

    private static bool IsWriteContext(CXCursor parent)
    {
        return parent.Kind is CXCursorKind.CXCursor_BinaryOperator
            or CXCursorKind.CXCursor_CompoundAssignOperator
            or CXCursorKind.CXCursor_UnaryOperator;
    }

    private static string? BuildMemberPath(CXCursor memberRef)
    {
        var member = ClangCursorHelpers.GetSpelling(memberRef);
        if (string.IsNullOrWhiteSpace(member))
            return null;

        foreach (var child in ClangCursorHelpers.Children(memberRef))
        {
            if (child.Kind == CXCursorKind.CXCursor_DeclRefExpr)
                return $"{ClangCursorHelpers.GetSpelling(child)}->{member}";
            if (child.Kind == CXCursorKind.CXCursor_UnexposedExpr)
            {
                foreach (var nested in ClangCursorHelpers.Children(child))
                {
                    if (nested.Kind == CXCursorKind.CXCursor_DeclRefExpr)
                        return $"{ClangCursorHelpers.GetSpelling(nested)}->{member}";
                }
            }
        }

        return null;
    }

    private static string? GetCalleeName(CXCursor call)
    {
        foreach (var child in ClangCursorHelpers.Children(call))
        {
            if (child.Kind == CXCursorKind.CXCursor_DeclRefExpr)
                return ClangCursorHelpers.GetSpelling(child);
            if (child.Kind == CXCursorKind.CXCursor_UnexposedExpr)
            {
                foreach (var nested in ClangCursorHelpers.Children(child))
                {
                    if (nested.Kind == CXCursorKind.CXCursor_DeclRefExpr)
                        return ClangCursorHelpers.GetSpelling(nested);
                }
            }
        }

        var spell = ClangCursorHelpers.GetSpelling(call);
        var idx = spell.IndexOf('(');
        return idx > 0 ? spell[..idx].Trim() : null;
    }

    private static string? TryExtractRegisterPath(CXCursor call)
    {
        foreach (var arg in ClangCursorHelpers.Children(call))
        {
            if (arg.Kind == CXCursorKind.CXCursor_MemberRefExpr)
                return BuildMemberPath(arg);
            if (arg.Kind == CXCursorKind.CXCursor_UnexposedExpr)
            {
                foreach (var nested in ClangCursorHelpers.Children(arg))
                {
                    if (nested.Kind == CXCursorKind.CXCursor_MemberRefExpr)
                        return BuildMemberPath(nested);
                }
            }
        }

        return null;
    }
}
