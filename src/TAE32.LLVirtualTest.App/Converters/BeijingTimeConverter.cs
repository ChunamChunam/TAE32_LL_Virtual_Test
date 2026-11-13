using System.Globalization;
using System.Windows.Data;

namespace TAE32.LLVirtualTest.App.Converters;

/// <summary>Convert stored UTC (or unspecified-as-UTC) DateTime to Beijing local text.</summary>
public sealed class BeijingTimeConverter : IValueConverter
{
    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        if (value is null) return "";
        if (value is not DateTime dt) return value;
        var format = parameter as string;
        return BeijingTime.Format(dt, string.IsNullOrWhiteSpace(format) ? null : format);
    }

    public object ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
        => throw new NotSupportedException();
}

public static class BeijingTime
{
    private static readonly TimeZoneInfo Zone = ResolveZone();

    private static TimeZoneInfo ResolveZone()
    {
        try
        {
            return TimeZoneInfo.FindSystemTimeZoneById("China Standard Time");
        }
        catch (TimeZoneNotFoundException)
        {
            try
            {
                return TimeZoneInfo.FindSystemTimeZoneById("Asia/Shanghai");
            }
            catch (TimeZoneNotFoundException)
            {
                return TimeZoneInfo.CreateCustomTimeZone(
                    "Beijing", TimeSpan.FromHours(8), "Beijing", "Beijing");
            }
        }
    }

    public static DateTime ToBeijing(DateTime value)
    {
        var utc = value.Kind switch
        {
            DateTimeKind.Utc => value,
            DateTimeKind.Local => value.ToUniversalTime(),
            // SQLite/EF typically returns Unspecified for values written with UtcNow.
            _ => DateTime.SpecifyKind(value, DateTimeKind.Utc)
        };
        return TimeZoneInfo.ConvertTimeFromUtc(utc, Zone);
    }

    public static string Format(DateTime value, string? format = null)
        => ToBeijing(value).ToString(format ?? "yyyy-MM-dd HH:mm:ss", CultureInfo.InvariantCulture);

    public static string Format(DateTime? value, string? format = null)
        => value is DateTime dt ? Format(dt, format) : "";
}
