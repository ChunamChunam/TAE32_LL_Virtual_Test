using System.Drawing;
using System.Drawing.Drawing2D;
using System.Drawing.Imaging;

static GraphicsPath RoundedRect(float x, float y, float w, float h, float r)
{
    var gp = new GraphicsPath();
    float d = r * 2f;
    gp.AddArc(x, y, d, d, 180, 90);
    gp.AddArc(x + w - d, y, d, d, 270, 90);
    gp.AddArc(x + w - d, y + h - d, d, d, 0, 90);
    gp.AddArc(x, y + h - d, d, d, 90, 90);
    gp.CloseFigure();
    return gp;
}

static void Prep(Graphics g)
{
    g.Clear(Color.Transparent);
    g.SmoothingMode = SmoothingMode.AntiAlias;
    g.PixelOffsetMode = PixelOffsetMode.HighQuality;
    g.CompositingQuality = CompositingQuality.HighQuality;
}

// A: Bold teal face + white chip + inner node (high contrast)
static void DrawA(Graphics g, int S)
{
    Prep(g);
    var teal = Color.FromArgb(255, 47, 158, 123);
    var white = Color.FromArgb(255, 248, 252, 250);
    float pad = S * 0.06f, radius = S * 0.22f;
    using var outer = RoundedRect(pad, pad, S - 2 * pad, S - 2 * pad, radius);
    using (var b = new SolidBrush(teal)) g.FillPath(b, outer);

    float cx = S / 2f, cy = S / 2f, die = S * 0.38f, dieR = S * 0.08f;
    float dx = cx - die / 2f, dy = cy - die / 2f;
    using var chip = RoundedRect(dx, dy, die, die, dieR);
    using var wb = new SolidBrush(white);
    g.FillPath(wb, chip);

    float pinW = S * 0.07f, pinH = S * 0.055f, gap = S * 0.07f;
    for (int i = -1; i <= 1; i++)
    {
        float py = cy + i * gap - pinH / 2f;
        g.FillRectangle(wb, dx - pinW, py, pinW, pinH);
        g.FillRectangle(wb, dx + die, py, pinW, pinH);
    }

    float inner = die * 0.55f;
    using var innerPath = RoundedRect(cx - inner / 2f, cy - inner / 2f, inner, inner, S * 0.05f);
    using (var tb = new SolidBrush(teal)) g.FillPath(tb, innerPath);

    float node = S * 0.09f;
    g.FillEllipse(wb, cx - node / 2f, cy - node / 2f, node, node);
}

// B: Dark face + teal chip + white check (matches app chrome)
static void DrawB(Graphics g, int S)
{
    Prep(g);
    var deep = Color.FromArgb(255, 15, 20, 25);
    var teal = Color.FromArgb(255, 47, 158, 123);
    var white = Color.FromArgb(255, 232, 238, 244);
    float pad = S * 0.04f, radius = S * 0.22f;
    using var outer = RoundedRect(pad, pad, S - 2 * pad, S - 2 * pad, radius);
    using (var b = new SolidBrush(deep)) g.FillPath(b, outer);

    float cx = S / 2f, cy = S / 2f, die = S * 0.44f, dieR = S * 0.09f;
    float dx = cx - die / 2f, dy = cy - die / 2f;
    using var chip = RoundedRect(dx, dy, die, die, dieR);
    using var tb = new SolidBrush(teal);
    g.FillPath(tb, chip);

    var state = g.Save();
    g.SetClip(chip);
    using (var fade = new LinearGradientBrush(
               new RectangleF(dx, dy, die, die * 0.55f),
               Color.FromArgb(50, 255, 255, 255),
               Color.FromArgb(0, 255, 255, 255),
               90f))
        g.FillRectangle(fade, dx, dy, die, die * 0.55f);
    g.Restore(state);

    float pinW = S * 0.08f, pinH = S * 0.06f, gap = S * 0.09f;
    for (int i = -1; i <= 1; i++)
    {
        float py = cy + i * gap - pinH / 2f;
        g.FillRectangle(tb, dx - pinW + 1, py, pinW, pinH);
        g.FillRectangle(tb, dx + die - 1, py, pinW, pinH);
    }

    using var pen = new Pen(white, S * 0.075f)
    {
        StartCap = LineCap.Round,
        EndCap = LineCap.Round,
        LineJoin = LineJoin.Round
    };
    g.DrawLines(pen, new[]
    {
        new PointF(cx - S * 0.11f, cy + S * 0.02f),
        new PointF(cx - S * 0.02f, cy + S * 0.11f),
        new PointF(cx + S * 0.14f, cy - S * 0.10f)
    });
}

// C: Dark + layered virtual plates + corner marks
static void DrawC(Graphics g, int S)
{
    Prep(g);
    var deep = Color.FromArgb(255, 15, 20, 25);
    var teal = Color.FromArgb(255, 47, 158, 123);
    var soft = Color.FromArgb(255, 31, 111, 88);
    var white = Color.FromArgb(255, 232, 238, 244);
    float pad = S * 0.05f, radius = S * 0.22f;
    using var outer = RoundedRect(pad, pad, S - 2 * pad, S - 2 * pad, radius);
    using (var b = new SolidBrush(deep)) g.FillPath(b, outer);

    float cx = S / 2f, cy = S / 2f, sz = S * 0.40f, r = S * 0.08f;
    using (var back = RoundedRect(cx - sz / 2f + S * 0.045f, cy - sz / 2f - S * 0.045f, sz, sz, r))
    using (var sb = new SolidBrush(soft))
        g.FillPath(sb, back);

    float fx = cx - sz / 2f - S * 0.02f, fy = cy - sz / 2f + S * 0.02f;
    using var front = RoundedRect(fx, fy, sz, sz, r);
    using (var tb = new SolidBrush(teal)) g.FillPath(tb, front);

    using var pen = new Pen(white, S * 0.045f)
    {
        StartCap = LineCap.Round,
        EndCap = LineCap.Round
    };
    float m = S * 0.11f;
    g.DrawLines(pen, new[]
    {
        new PointF(fx + m, fy + m * 0.35f),
        new PointF(fx + m * 0.35f, fy + m * 0.35f),
        new PointF(fx + m * 0.35f, fy + m)
    });
    g.DrawLines(pen, new[]
    {
        new PointF(fx + sz - m, fy + sz - m * 0.35f),
        new PointF(fx + sz - m * 0.35f, fy + sz - m * 0.35f),
        new PointF(fx + sz - m * 0.35f, fy + sz - m)
    });

    float barW = sz * 0.40f, barH = S * 0.055f;
    using var wb = new SolidBrush(white);
    float bx = cx - barW / 2f - S * 0.02f, by = cy - barH / 2f + S * 0.02f;
    g.FillRectangle(wb, bx, by, barW, barH);
    g.FillEllipse(wb, bx + barW - barH / 2f, by, barH, barH);
}

// D: Teal face, clean geometric T (TAE) — brand monogram
static void DrawD(Graphics g, int S)
{
    Prep(g);
    var tealTop = Color.FromArgb(255, 56, 176, 140);
    var tealBot = Color.FromArgb(255, 36, 132, 104);
    var white = Color.FromArgb(255, 248, 252, 250);
    float pad = S * 0.05f, radius = S * 0.22f;
    using var outer = RoundedRect(pad, pad, S - 2 * pad, S - 2 * pad, radius);
    using (var fade = new LinearGradientBrush(
               new RectangleF(0, 0, S, S), tealTop, tealBot, 90f))
        g.FillPath(fade, outer);

    float cx = S / 2f, cy = S / 2f;
    float thick = S * 0.10f;
    using var pen = new Pen(white, thick)
    {
        StartCap = LineCap.Round,
        EndCap = LineCap.Round,
        LineJoin = LineJoin.Round
    };
    float topY = cy - S * 0.15f;
    float botY = cy + S * 0.18f;
    float half = S * 0.175f;
    g.DrawLine(pen, cx - half, topY, cx + half, topY);
    g.DrawLine(pen, cx, topY, cx, botY);
}

// E: Dark chrome match — teal T monogram only (no chip clutter)
static void DrawE(Graphics g, int S)
{
    Prep(g);
    var deep = Color.FromArgb(255, 15, 20, 25);
    var panel = Color.FromArgb(255, 23, 30, 38);
    var teal = Color.FromArgb(255, 47, 158, 123);
    float pad = S * 0.04f, radius = S * 0.22f;
    using var outer = RoundedRect(pad, pad, S - 2 * pad, S - 2 * pad, radius);
    using (var b = new SolidBrush(deep)) g.FillPath(b, outer);

    // subtle inner panel
    float inset = S * 0.10f;
    using var inner = RoundedRect(inset, inset, S - 2 * inset, S - 2 * inset, S * 0.16f);
    using (var pb = new SolidBrush(panel)) g.FillPath(pb, inner);

    float cx = S / 2f, cy = S / 2f;
    using var pen = new Pen(teal, S * 0.10f)
    {
        StartCap = LineCap.Round,
        EndCap = LineCap.Round,
        LineJoin = LineJoin.Round
    };
    float topY = cy - S * 0.14f;
    float botY = cy + S * 0.17f;
    float half = S * 0.16f;
    g.DrawLine(pen, cx - half, topY, cx + half, topY);
    g.DrawLine(pen, cx, topY, cx, botY);
}

// F: Teal face + white chip silhouette (refined thinner pins, solid die — no lens look)
static void DrawF(Graphics g, int S)
{
    Prep(g);
    var tealTop = Color.FromArgb(255, 56, 176, 140);
    var tealBot = Color.FromArgb(255, 36, 132, 104);
    var white = Color.FromArgb(255, 248, 252, 250);
    float pad = S * 0.05f, radius = S * 0.22f;
    using var outer = RoundedRect(pad, pad, S - 2 * pad, S - 2 * pad, radius);
    using (var fade = new LinearGradientBrush(
               new RectangleF(0, 0, S, S), tealTop, tealBot, 90f))
        g.FillPath(fade, outer);

    float cx = S / 2f, cy = S / 2f;
    float die = S * 0.36f, dieR = S * 0.07f;
    float dx = cx - die / 2f, dy = cy - die / 2f;
    using var wb = new SolidBrush(white);
    using var chip = RoundedRect(dx, dy, die, die, dieR);
    g.FillPath(wb, chip);

    // thinner pins
    float pinW = S * 0.055f, pinH = S * 0.042f, gap = S * 0.065f;
    for (int i = -1; i <= 1; i++)
    {
        float py = cy + i * gap - pinH / 2f;
        g.FillRectangle(wb, dx - pinW, py, pinW, pinH);
        g.FillRectangle(wb, dx + die, py, pinW, pinH);
    }

    // tiny center mark: vertical bar (not a lens)
    float barW = S * 0.045f, barH = S * 0.14f;
    using var mark = new SolidBrush(tealBot);
    g.FillRectangle(mark, cx - barW / 2f, cy - barH / 2f, barW, barH);
    // small top crossbar to hint T inside chip
    g.FillRectangle(mark, cx - S * 0.08f, cy - barH / 2f, S * 0.16f, barW);
}

static void SavePng(Action<Graphics, int> draw, string path, int size = 512)
{
    using var bmp = new Bitmap(size, size, PixelFormat.Format32bppArgb);
    using (var g = Graphics.FromImage(bmp)) draw(g, size);
    bmp.Save(path, ImageFormat.Png);
}

static void SaveIco(Action<Graphics, int> draw, string path, int[] sizes)
{
    var images = new List<byte[]>();
    foreach (var size in sizes)
    {
        using var bmp = new Bitmap(size, size, PixelFormat.Format32bppArgb);
        using (var g = Graphics.FromImage(bmp)) draw(g, size);
        using var ms = new MemoryStream();
        bmp.Save(ms, ImageFormat.Png);
        images.Add(ms.ToArray());
    }

    using var fs = File.Create(path);
    using var bw = new BinaryWriter(fs);
    bw.Write((ushort)0);
    bw.Write((ushort)1);
    bw.Write((ushort)images.Count);
    int offset = 6 + 16 * images.Count;
    for (int i = 0; i < images.Count; i++)
    {
        int size = sizes[i];
        bw.Write((byte)(size >= 256 ? 0 : size));
        bw.Write((byte)(size >= 256 ? 0 : size));
        bw.Write((byte)0);
        bw.Write((byte)0);
        bw.Write((ushort)1);
        bw.Write((ushort)32);
        bw.Write(images[i].Length);
        bw.Write(offset);
        offset += images[i].Length;
    }
    foreach (var data in images) bw.Write(data);
}

var preview = args.Length > 0 ? args[0] : @"C:\Users\zhangqi\.cursor\projects\d-Code-12-TAE32-LL-Virtual-Test\assets";
Directory.CreateDirectory(preview);

SavePng(DrawA, Path.Combine(preview, "icon-candidate-A.png"));
SavePng(DrawB, Path.Combine(preview, "icon-candidate-B.png"));
SavePng(DrawC, Path.Combine(preview, "icon-candidate-C.png"));
SavePng(DrawD, Path.Combine(preview, "icon-candidate-D.png"));
SavePng(DrawE, Path.Combine(preview, "icon-candidate-E.png"));
SavePng(DrawF, Path.Combine(preview, "icon-candidate-F.png"));

// Final ship: D — teal monogram T (clean, readable at 16px)
var appAssets = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "..", "..", "src", "TAE32.LLVirtualTest.App", "Assets"));
var installer = Path.GetFullPath(Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "..", "..", "installer"));
if (!Directory.Exists(appAssets))
{
    appAssets = @"d:\Code\12_TAE32_LL_Virtual_Test\src\TAE32.LLVirtualTest.App\Assets";
    installer = @"d:\Code\12_TAE32_LL_Virtual_Test\installer";
}
Directory.CreateDirectory(appAssets);
Directory.CreateDirectory(installer);

var sizes = new[] { 16, 24, 32, 48, 64, 128, 256 };
SavePng(DrawD, Path.Combine(appAssets, "App.png"), 512);
SavePng(DrawD, Path.Combine(installer, "App.png"), 512);
SavePng(DrawD, Path.Combine(preview, "App-final.png"), 512);
SaveIco(DrawD, Path.Combine(appAssets, "App.ico"), sizes);
SaveIco(DrawD, Path.Combine(installer, "App.ico"), sizes);
File.Copy(Path.Combine(appAssets, "App.png"), Path.Combine(appAssets, "app-icon-source.png"), overwrite: true);
Console.WriteLine("Final icon written:");
Console.WriteLine("  " + Path.Combine(appAssets, "App.ico"));
Console.WriteLine("  " + Path.Combine(installer, "App.ico"));
