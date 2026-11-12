namespace TAE32.LLVirtualTest.SDK.Register;

/// <summary>Baseline-confirmed timer instance → LL module name mapping.</summary>
internal static class RegisterTimerModuleMap
{
  private static readonly IReadOnlyDictionary<string, string> InstanceToModule =
      new Dictionary<string, string>(StringComparer.Ordinal)
      {
          ["TMR0"] = "GPTMRX",
          ["TMR1"] = "GPTMRX",
          ["TMR2"] = "GPTMRX",
          ["TMR3"] = "GPTMRY",
          ["TMR4"] = "GPTMRY",
          ["TMR6"] = "LPTMR",
          ["TMR7"] = "BSTMR",
          ["TMR8"] = "BSTMR",
          ["TMR9"] = "ADTMR",
          ["TMR10"] = "ADTMR",
      };

    public static string? ResolveModuleForInstance(string instanceName)
        => InstanceToModule.TryGetValue(instanceName, out var m) ? m : null;
}
