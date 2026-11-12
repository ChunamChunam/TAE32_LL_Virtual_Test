namespace TAE32.LLVirtualTest.SDK.Register;

internal static class RegisterNaturalKeys
{
    public static string Instance(Guid projectId, string instanceName)
        => $"{projectId:N}|inst|{instanceName}";

    public static string Register(Guid projectId, string structName, string memberName)
        => $"{projectId:N}|reg|{structName}|{memberName}";

    public static string Field(Guid registerId, string fieldName)
        => $"{registerId:N}|fld|{fieldName}";

    public static string Macro(Guid projectId, string macroName, string referenceFile, int line)
        => $"{projectId:N}|macro|{macroName}|{referenceFile}|{line}";
}
