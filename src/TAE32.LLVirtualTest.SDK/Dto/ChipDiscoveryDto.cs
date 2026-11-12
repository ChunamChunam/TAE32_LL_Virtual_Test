using System.Text.Json.Serialization;

namespace TAE32.LLVirtualTest.SDK.Dto;

public sealed class ChipDiscoveryDocument
{
    [JsonPropertyName("generated_at")]
    public string? GeneratedAt { get; set; }

    [JsonPropertyName("chips")]
    public List<ChipDto> Chips { get; set; } = new();

    [JsonPropertyName("chip_count")]
    public int? ChipCount { get; set; }
}

public sealed class ChipDto
{
    [JsonPropertyName("chip_model")]
    public string ChipModel { get; set; } = string.Empty;

    [JsonPropertyName("related_files")]
    public List<string> RelatedFiles { get; set; } = new();

    [JsonPropertyName("detection_status")]
    public string? DetectionStatus { get; set; }

    [JsonPropertyName("confidence")]
    public string? Confidence { get; set; }

    [JsonPropertyName("notes")]
    public string? Notes { get; set; }
}
