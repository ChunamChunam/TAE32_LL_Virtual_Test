using System.IO;
using System.Text.Json;
using CommunityToolkit.Mvvm.ComponentModel;

namespace TAE32.LLVirtualTest.App.Services;

public sealed partial class UiScaleService : ObservableObject
{
    public static IReadOnlyList<double> Presets { get; } = new[] { 0.85, 0.9, 1.0, 1.1, 1.25, 1.5 };

    private static string ScaleFilePath => Path.Combine(AppPaths.DataDirectory, "ui-scale.json");

    [ObservableProperty] private double _scale = 1.0;

    public UiScaleService()
    {
        TryLoad();
    }

    partial void OnScaleChanged(double value)
    {
        OnPropertyChanged(nameof(ScaleTransform));
        TrySave();
    }

    public System.Windows.Media.ScaleTransform ScaleTransform => new(Scale, Scale);

    public void TryLoad()
    {
        try
        {
            if (!File.Exists(ScaleFilePath)) return;
            var json = File.ReadAllText(ScaleFilePath);
            var doc = JsonSerializer.Deserialize<UiScaleFile>(json);
            if (doc is { Scale: > 0.5 and < 2.5 })
                Scale = doc.Scale;
        }
        catch
        {
            // ignore corrupt file
        }
    }

    private void TrySave()
    {
        try
        {
            Directory.CreateDirectory(AppPaths.DataDirectory);
            var json = JsonSerializer.Serialize(new UiScaleFile { Scale = Scale });
            File.WriteAllText(ScaleFilePath, json);
        }
        catch
        {
            // non-fatal
        }
    }

    private sealed class UiScaleFile
    {
        public double Scale { get; set; } = 1.0;
    }
}
