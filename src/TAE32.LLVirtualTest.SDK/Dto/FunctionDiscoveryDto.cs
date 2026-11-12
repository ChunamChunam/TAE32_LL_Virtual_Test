using System.Text.Json.Serialization;

namespace TAE32.LLVirtualTest.SDK.Dto;

public sealed class FunctionDiscoveryDocument
{
    [JsonPropertyName("generated_at")]
    public string? GeneratedAt { get; set; }

    [JsonPropertyName("function_count_total")]
    public int? FunctionCountTotal { get; set; }

    [JsonPropertyName("function_count_inline_definition")]
    public int? InlineDefinitionCount { get; set; }

    [JsonPropertyName("functions")]
    public List<FunctionDto> Functions { get; set; } = new();
}

public sealed class FunctionDto
{
    [JsonPropertyName("FunctionName")]
    public string FunctionName { get; set; } = string.Empty;

    [JsonPropertyName("ReturnType")]
    public string? ReturnType { get; set; }

    [JsonPropertyName("Parameters")]
    public string? Parameters { get; set; }

    [JsonPropertyName("FunctionType")]
    public string? FunctionType { get; set; }

    [JsonPropertyName("Form")]
    public string? Form { get; set; }

    [JsonPropertyName("Peripheral")]
    public string? Peripheral { get; set; }

    [JsonPropertyName("Chip")]
    public string? Chip { get; set; }

    [JsonPropertyName("FilePath")]
    public string FilePath { get; set; } = string.Empty;

    [JsonPropertyName("StartLine")]
    public int StartLine { get; set; }

    [JsonPropertyName("EndLine")]
    public int EndLine { get; set; }

    [JsonPropertyName("DetectionStatus")]
    public string? DetectionStatus { get; set; }
}
