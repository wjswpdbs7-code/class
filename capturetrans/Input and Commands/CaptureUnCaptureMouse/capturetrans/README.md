# CaptureUnCaptureMouse

전체 화면 캡처 + OCR(텍스트 추출) + 번역 WPF 예제입니다.

## 기능

- 전체 가상 화면(멀티 모니터 포함) 캡처
- 캡처 이미지 미리보기
- OCR로 텍스트 추출 (기본: 한국어 가능 시 `ko`, 아니면 `en`)
- OCR 결과 텍스트 번역 (한국어/영어/일본어/중국어 간체)
- 캡처 이미지를 PNG로 저장

## 요구 사항

- Windows 10/11
- .NET 8 SDK 이상
- 시스템 OCR 언어 팩(한국어/영어)
- 인터넷 연결(번역 API 호출)

## 실행

```bash
dotnet restore
dotnet run
```

## exe 만들기

### 방법 1) 스크립트 사용

- CMD: `publish-win-x64.bat`
- PowerShell: `./publish-win-x64.ps1`

### 방법 2) 직접 명령 실행

```bash
dotnet restore
dotnet publish -c Release -r win-x64 --self-contained true /p:PublishSingleFile=true /p:IncludeNativeLibrariesForSelfExtract=true /p:PublishTrimmed=false
```

생성 경로:

`bin/Release/net8.0-windows10.0.19041.0/win-x64/publish/`

## 사용 방법

1. `전체 화면 캡처 + OCR` 버튼 클릭
2. OCR 텍스트가 추출되며 자동 번역 옵션이 켜져 있으면 번역까지 실행
3. 수동 번역은 대상 언어 선택 후 `텍스트 번역` 버튼 클릭
4. 필요 시 `이미지 저장` 버튼으로 PNG 저장

## 주요 파일

- `MainWindow.xaml`: UI(캡처, OCR, 번역)
- `MainWindow.cs`: 캡처/OCR/번역/저장 로직
- `CaptureUnCaptureMouse.csproj`: WPF + Windows SDK + 배포 설정
