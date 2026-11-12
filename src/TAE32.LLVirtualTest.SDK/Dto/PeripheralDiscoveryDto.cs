using System.Text.Json.Serialization;

namespace TAE32.LLVirtualTest.SDK.Dto;

public sealed class PeripheralDiscoveryDocument
{
    [JsonPropertyName("generated_at")]
    public string? GeneratedAt { get; set; }

    [JsonPropertyName("peripheral_count")]
    public int? PeripheralCount { get; set; }

    [JsonPropertyName("peripherals")]
    public List<PeripheralDto> Peripherals { get; set; } = new();
}

public sealed class PeripheralDto
{
    [JsonPropertyName("序号")]
    public int? SerialNumber { get; set; }

    [JsonPropertyName("外设名称")]
    public string Name { get; set; } = string.Empty;

    [JsonPropertyName("相关文件")]
    public List<string> RelatedFiles { get; set; } = new();

    [JsonPropertyName("LL函数数量")]
    public int InlineFunctionCount { get; set; }

    [JsonPropertyName("LL函数数量_全形式")]
    public int? AllFormsFunctionCount { get; set; }

    [JsonPropertyName("外设实例")]
    public List<string> Instances { get; set; } = new();

    [JsonPropertyName("TypeDef")]
    public List<string> Typedefs { get; set; } = new();

    [JsonPropertyName("置信度")]
    public string? Confidence { get; set; }

    [JsonPropertyName("识别状态")]
    public string? DetectionStatus { get; set; }

    [JsonPropertyName("所属芯片")]
    public string? ChipName { get; set; }

    [JsonPropertyName("notes")]
    public string? Notes { get; set; }

    [JsonPropertyName("is_common_driver")]
    public bool IsCommonDriver { get; set; }
}
