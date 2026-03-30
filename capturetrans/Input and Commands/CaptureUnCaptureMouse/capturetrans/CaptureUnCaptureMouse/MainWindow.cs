using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Net.Http;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using Microsoft.Win32;
using Windows.Graphics.Imaging;
using Windows.Media.Ocr;
using Windows.Storage.Streams;

namespace CaptureUnCaptureMouse;

public partial class MainWindow : Window
{
	private static readonly HttpClient TranslatorHttpClient = new()
	{
		Timeout = TimeSpan.FromSeconds(20)
	};

	private Bitmap? _latestCapture;

	public MainWindow()
	{
		InitializeComponent();
		TargetLanguageCombo.SelectedIndex = 0;
	}

	private async void CaptureAndRecognize_Click(object sender, RoutedEventArgs e)
	{
		CaptureButton.IsEnabled = false;
		TranslateButton.IsEnabled = false;
		StatusText.Text = "화면 캡처 중...";
		OcrResultText.Text = "화면 캡처 중...";
		TranslatedResultText.Clear();

		try
		{
			var bmp = CaptureVirtualScreen();
			_latestCapture?.Dispose();
			_latestCapture = bmp;

			CapturedImage.Source = ToBitmapImage(bmp);
			StatusText.Text = "텍스트 인식 중...";
			OcrResultText.Text = "텍스트 인식 중...";

			var text = await ExtractTextFromBitmapAsync(bmp);
			OcrResultText.Text = string.IsNullOrWhiteSpace(text)
				? "인식된 텍스트가 없습니다."
				: text;

			if (!string.IsNullOrWhiteSpace(text) && AutoTranslateCheckBox.IsChecked == true)
			{
				await TranslateCurrentOcrTextAsync();
			}
			else
			{
				StatusText.Text = "OCR 완료";
			}
		}
		catch (Exception ex)
		{
			StatusText.Text = "오류 발생";
			OcrResultText.Text = $"오류: {ex.Message}";
		}
		finally
		{
			CaptureButton.IsEnabled = true;
			TranslateButton.IsEnabled = true;
		}
	}

	private async void TranslateButton_Click(object sender, RoutedEventArgs e)
	{
		await TranslateCurrentOcrTextAsync();
	}

	private void SaveImage_Click(object sender, RoutedEventArgs e)
	{
		if (_latestCapture is null)
		{
			MessageBox.Show(this, "먼저 캡처를 실행하세요.", "안내", MessageBoxButton.OK, MessageBoxImage.Information);
			return;
		}

		var dialog = new SaveFileDialog
		{
			Filter = "PNG Image (*.png)|*.png",
			FileName = $"capture_{DateTime.Now:yyyyMMdd_HHmmss}.png"
		};

		if (dialog.ShowDialog(this) != true)
		{
			return;
		}

		_latestCapture.Save(dialog.FileName, ImageFormat.Png);
		StatusText.Text = "이미지 저장 완료";
	}

	private async Task TranslateCurrentOcrTextAsync()
	{
		var sourceText = OcrResultText.Text?.Trim() ?? string.Empty;
		if (string.IsNullOrWhiteSpace(sourceText) || sourceText == "인식된 텍스트가 없습니다.")
		{
			StatusText.Text = "번역할 텍스트가 없습니다.";
			return;
		}

		var targetLanguage = GetSelectedTargetLanguage();
		if (string.IsNullOrWhiteSpace(targetLanguage))
		{
			StatusText.Text = "대상 언어를 선택하세요.";
			return;
		}

		TranslateButton.IsEnabled = false;
		StatusText.Text = "번역 중...";

		try
		{
			var translated = await TranslateTextAsync(sourceText, targetLanguage);
			TranslatedResultText.Text = translated;
			StatusText.Text = "번역 완료";
		}
		catch (Exception ex)
		{
			TranslatedResultText.Text = string.Empty;
			StatusText.Text = $"번역 오류: {ex.Message}";
		}
		finally
		{
			TranslateButton.IsEnabled = true;
		}
	}

	private string GetSelectedTargetLanguage()
	{
		if (TargetLanguageCombo.SelectedItem is ComboBoxItem selected && selected.Tag is string code)
		{
			return code;
		}

		return "ko";
	}

	private static async Task<string> TranslateTextAsync(string text, string targetLanguage)
	{
		var escaped = Uri.EscapeDataString(text);
		var url = $"https://translate.googleapis.com/translate_a/single?client=gtx&sl=auto&tl={targetLanguage}&dt=t&q={escaped}";

		using var response = await TranslatorHttpClient.GetAsync(url);
		response.EnsureSuccessStatusCode();

		var payload = await response.Content.ReadAsStringAsync();
		using var doc = JsonDocument.Parse(payload);

		if (doc.RootElement.ValueKind != JsonValueKind.Array || doc.RootElement.GetArrayLength() == 0)
		{
			throw new InvalidOperationException("번역 응답 형식이 올바르지 않습니다.");
		}

		var chunks = doc.RootElement[0];
		if (chunks.ValueKind != JsonValueKind.Array)
		{
			throw new InvalidOperationException("번역 텍스트를 해석할 수 없습니다.");
		}

		var sb = new StringBuilder();
		foreach (var chunk in chunks.EnumerateArray())
		{
			if (chunk.ValueKind == JsonValueKind.Array && chunk.GetArrayLength() > 0)
			{
				var translated = chunk[0].GetString();
				if (!string.IsNullOrWhiteSpace(translated))
				{
					sb.Append(translated);
				}
			}
		}

		var result = sb.ToString().Trim();
		if (string.IsNullOrWhiteSpace(result))
		{
			throw new InvalidOperationException("번역 결과가 비어 있습니다.");
		}

		return result;
	}

	private static Bitmap CaptureVirtualScreen()
	{
		var left = (int)SystemParameters.VirtualScreenLeft;
		var top = (int)SystemParameters.VirtualScreenTop;
		var width = (int)SystemParameters.VirtualScreenWidth;
		var height = (int)SystemParameters.VirtualScreenHeight;

		var bitmap = new Bitmap(width, height, PixelFormat.Format32bppArgb);

		using var g = Graphics.FromImage(bitmap);
		g.CopyFromScreen(left, top, 0, 0, new Size(width, height), CopyPixelOperation.SourceCopy);

		return bitmap;
	}

	private static BitmapImage ToBitmapImage(Bitmap bitmap)
	{
		using var stream = new MemoryStream();
		bitmap.Save(stream, ImageFormat.Png);
		stream.Position = 0;

		var image = new BitmapImage();
		image.BeginInit();
		image.CacheOption = BitmapCacheOption.OnLoad;
		image.StreamSource = stream;
		image.EndInit();
		image.Freeze();

		return image;
	}

	private static async Task<string> ExtractTextFromBitmapAsync(Bitmap bitmap)
	{
		if (!OcrEngine.IsLanguageSupported(new Windows.Globalization.Language("ko")) &&
			!OcrEngine.IsLanguageSupported(new Windows.Globalization.Language("en")))
		{
			throw new InvalidOperationException("OCR 언어(ko/en)가 시스템에 설치되어 있지 않습니다.");
		}

		var preferredLanguage = OcrEngine.IsLanguageSupported(new Windows.Globalization.Language("ko"))
			? new Windows.Globalization.Language("ko")
			: new Windows.Globalization.Language("en");

		var engine = OcrEngine.TryCreateFromLanguage(preferredLanguage) ?? OcrEngine.TryCreateFromUserProfileLanguages();
		if (engine is null)
		{
			throw new InvalidOperationException("OCR 엔진을 초기화할 수 없습니다.");
		}

		using var ms = new MemoryStream();
		bitmap.Save(ms, ImageFormat.Png);
		ms.Position = 0;

		using IRandomAccessStream ras = ms.AsRandomAccessStream();
		var decoder = await BitmapDecoder.CreateAsync(ras);
		var softwareBitmap = await decoder.GetSoftwareBitmapAsync();

		var result = await engine.RecognizeAsync(softwareBitmap);
		return result.Text?.Trim() ?? string.Empty;
	}

	protected override void OnClosed(EventArgs e)
	{
		_latestCapture?.Dispose();
		base.OnClosed(e);
	}
}
