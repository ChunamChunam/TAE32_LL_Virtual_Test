using System.Text.Json;
using System.Text.Json.Serialization;
using TAE32.LLVirtualTest.Core.Models;

namespace TAE32.LLVirtualTest.Infrastructure.TestEngine;

internal static class LlTestJson
{
    private static readonly JsonSerializerOptions Options = new()
    {
        PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
        WriteIndented = true,
        Converters = { new JsonStringEnumConverter() },
        DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull
    };

    private sealed class ParametersEnvelope
    {
        public List<LlTestParameterValue> Parameters { get; set; } = new();
        public List<LlTestCallStep> PreludeCalls { get; set; } = new();
    }

    public static string SerializeParametersEnvelope(
        IEnumerable<LlTestParameterValue> parameters,
        IEnumerable<LlTestCallStep>? prelude = null)
    {
        var env = new ParametersEnvelope
        {
            Parameters = parameters.ToList(),
            PreludeCalls = prelude?.ToList() ?? new()
        };
        return JsonSerializer.Serialize(env, Options);
    }

    public static (List<LlTestParameterValue> Parameters, List<LlTestCallStep> Prelude)
        DeserializeParametersEnvelope(string? json)
    {
        if (string.IsNullOrWhiteSpace(json) || json.Trim() is "{}" or "[]")
            return (new(), new());

        var trimmed = json.TrimStart();
        // Legacy: bare parameter array
        if (trimmed.StartsWith('['))
        {
            var list = JsonSerializer.Deserialize<List<LlTestParameterValue>>(json, Options) ?? new();
            return (list, new());
        }

        var env = JsonSerializer.Deserialize<ParametersEnvelope>(json, Options);
        return (env?.Parameters ?? new(), env?.PreludeCalls ?? new());
    }

    public static string SerializeInitial(IEnumerable<LlTestInitialRegister> items)
        => JsonSerializer.Serialize(items.ToList(), Options);

    public static List<LlTestInitialRegister> DeserializeInitial(string? json)
        => string.IsNullOrWhiteSpace(json)
            ? new List<LlTestInitialRegister>()
            : JsonSerializer.Deserialize<List<LlTestInitialRegister>>(json, Options) ?? new();

    public static string SerializeAssertions(IEnumerable<LlTestAssertionSpec> items)
        => JsonSerializer.Serialize(items.ToList(), Options);

    public static List<LlTestAssertionSpec> DeserializeAssertions(string? json)
        => string.IsNullOrWhiteSpace(json)
            ? new List<LlTestAssertionSpec>()
            : JsonSerializer.Deserialize<List<LlTestAssertionSpec>>(json, Options) ?? new();

    public static string Serialize<T>(T value) => JsonSerializer.Serialize(value, Options);

    public static T? Deserialize<T>(string? json)
        => string.IsNullOrWhiteSpace(json) ? default : JsonSerializer.Deserialize<T>(json, Options);
}
