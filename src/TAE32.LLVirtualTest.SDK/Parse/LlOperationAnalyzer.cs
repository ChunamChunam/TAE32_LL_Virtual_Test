using ClangSharp.Interop;
using TAE32.LLVirtualTest.Core.Entities;
using TAE32.LLVirtualTest.Core.Enums;

namespace TAE32.LLVirtualTest.SDK.Parse;

public sealed class LlOperationAnalyzer
{
    private int _seq;
    private Guid? _currentParent;

    public void Analyze(CXCursor body, LlAstFunctionResult result)
    {
        _seq = 0;
        _currentParent = null;
        ClangCursorHelpers.VisitRecursive(body, (cursor, _) => Walk(cursor, result));
    }

    private void Walk(CXCursor cursor, LlAstFunctionResult result)
    {
        var opKind = MapOpKind(cursor.Kind);
        Guid? opId = null;
        if (opKind != LlFunctionOpKind.Unknown)
        {
            opId = Guid.NewGuid();
            result.Operations.Add(new LlFunctionOperation
            {
                Id = opId.Value,
                OpKind = opKind.ToString(),
                Sequence = _seq++,
                SourceText = ClangCursorHelpers.GetSpelling(cursor),
                StartLine = ClangCursorHelpers.GetStartLine(cursor),
                EndLine = ClangCursorHelpers.GetEndLine(cursor),
                AstKind = cursor.Kind.ToString(),
                ParentOpId = _currentParent
            });
        }

        var prevParent = _currentParent;
        _currentParent = opId ?? _currentParent;
        _currentParent = prevParent;
    }

    private static LlFunctionOpKind MapOpKind(CXCursorKind kind) => kind switch
    {
        CXCursorKind.CXCursor_IfStmt => LlFunctionOpKind.If,
        CXCursorKind.CXCursor_ForStmt => LlFunctionOpKind.For,
        CXCursorKind.CXCursor_WhileStmt => LlFunctionOpKind.While,
        CXCursorKind.CXCursor_DoStmt => LlFunctionOpKind.Do,
        CXCursorKind.CXCursor_SwitchStmt => LlFunctionOpKind.Switch,
        CXCursorKind.CXCursor_ReturnStmt => LlFunctionOpKind.Return,
        CXCursorKind.CXCursor_BinaryOperator => LlFunctionOpKind.BinaryOperator,
        CXCursorKind.CXCursor_UnaryOperator => LlFunctionOpKind.UnaryOperator,
        CXCursorKind.CXCursor_CallExpr => LlFunctionOpKind.Call,
        CXCursorKind.CXCursor_MemberRefExpr => LlFunctionOpKind.MemberRef,
        CXCursorKind.CXCursor_CompoundAssignOperator => LlFunctionOpKind.CompoundAssign,
        CXCursorKind.CXCursor_DeclStmt => LlFunctionOpKind.Decl,
        _ => LlFunctionOpKind.Unknown
    };
}
