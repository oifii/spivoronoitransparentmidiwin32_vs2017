# Install, Build, and Launch (Windows / Visual Studio 2017)

## System Requirements

- **Operating System**

Windows desktop (Win32). The application targets  and the Windows desktop API.

- **Compiler & Toolset**

Microsoft Visual Studio 2017 (PlatformToolset = v141) with “Desktop development with C++” workload, including MFC support (UseOfMfc = Dynamic) and Unicode character set .

- **Disk Space**

Approximately 50 MB for source, headers, and prebuilt libraries under `lib-src`.

## Vendored Dependency Layout

All third-party libraries are vendored under the top-level `lib-src` directory:

- **FreeImagePlus**
- `lib-src/freeimage_vs2017/` (x86)
- `Source/` – FreeImage headers and sources
- `Wrapper/FreeImagePlus/` – C++ wrapper headers
- `Wrapper/FreeImagePlus/dist/x32/` – `FreeImagePlus.lib` for x86
- `lib-src/freeimage_vs2017(x64)/` (x64)
- Same structure, with `dist/x64/FreeImagePlus.lib`

- **oifii libraries** (MFC extensions/resource DLL)
- `lib-src/oifii_vs2017u/oifiilib/`
- `Debug/` and `Release/` subfolders for both x86 and x64 (`oifiilib.lib`)
- `lib-src/oifii_vs2017u/ow_ipl/`
- `Debug/` and `Release/` for x86 (`ow_ipl.lib`) and `x64/Debug`, `x64/Release` for x64
- `lib-src/oifii_vs2017u/ow_iff/`
- Same layout as `ow_ipl`

- **PortMidi**
- `lib-src/portmidi/` (x86)
- `pm_common/` – headers
- `Release/portmidi_s.lib` – static import library
- `lib-src/portmidi(x64)/` (x64)
- `pm_common/` – headers
- `x64/Release/portmidi-static.lib` – static library

- **Windows Multimedia**
- `winmm.lib` (system library for timer and MIDI event scheduling)

## Include and Library Configuration

Paths are configured per Configuration|Platform via the project’s `AdditionalIncludeDirectories` and `AdditionalDependencies` settings.

| Configuration | Platform | Include Directories | Libraries |
| --- | --- | --- | --- |
| Debug | Win32 | `..\lib-src\freeimage_vs2017\Source;..\lib-src\oifii_vs2017u\oifiilib;..\lib-src\oifii_vs2017u\ow_ipl;..\lib-src\oifii_vs2017u\ow_iff;..\lib-src\portmidi\pm_common;..\lib-src\freeimage_vs2017\Wrapper\FreeImagePlus` | `..\lib-src\freeimage_vs2017\Wrapper\FreeImagePlus\dist\x32\FreeImagePlus.lib;..\lib-src\oifii_vs2017u\oifiilib\Debug\oifiilib.lib;..\lib-src\oifii_vs2017u\ow_ipl\Debug\ow_ipl.lib;..\lib-src\oifii_vs2017u\ow_iff\Debug\ow_iff.lib;winmm.lib;..\lib-src\portmidi\Release\portmidi_s.lib` |
| Release | Win32 | `..\lib-src\freeimage_vs2017\Source;..\lib-src\oifii_vs2017u\oifiilib;..\lib-src\oifii_vs2017u\ow_ipl;..\lib-src\oifii_vs2017u\ow_iff;..\lib-src\portmidi\pm_common;..\lib-src\freeimage_vs2017\Wrapper\FreeImagePlus` | `..\lib-src\freeimage_vs2017\Wrapper\FreeImagePlus\dist\x32\FreeImagePlus.lib;..\lib-src\oifii_vs2017u\oifiilib\Release\oifiilib.lib;..\lib-src\oifii_vs2017u\ow_ipl\Release\ow_ipl.lib;..\lib-src\oifii_vs2017u\ow_iff\Release\ow_iff.lib;winmm.lib;..\lib-src\portmidi\Release\portmidi_s.lib` |
| Debug | x64 | `..\lib-src\freeimage_vs2017(x64)\Source;..\lib-src\oifii_vs2017u\oifiilib;..\lib-src\oifii_vs2017u\ow_ipl;..\lib-src\oifii_vs2017u\ow_iff;..\lib-src\portmidi(x64)\pm_common;..\lib-src\freeimage_vs2017(x64)\Wrapper\FreeImagePlus` | `..\lib-src\freeimage_vs2017(x64)\Wrapper\FreeImagePlus\dist\x64\FreeImagePlus.lib;..\lib-src\oifii_vs2017u\oifiilib\x64\Debug\oifiilib.lib;..\lib-src\oifii_vs2017u\ow_ipl\x64\Debug\ow_ipl.lib;..\lib-src\oifii_vs2017u\ow_iff\x64\Debug\ow_iff.lib;winmm.lib;..\lib-src\portmidi(x64)\x64\Release\portmidi-static.lib` |
| Release | x64 | `..\lib-src\freeimage_vs2017(x64)\Source;..\lib-src\oifii_vs2017u\oifiilib;..\lib-src\oifii_vs2017u\ow_ipl;..\lib-src\oifii_vs2017u\ow_iff;..\lib-src\portmidi(x64)\pm_common;..\lib-src\freeimage_vs2017(x64)\Wrapper\FreeImagePlus` | `..\lib-src\freeimage_vs2017(x64)\Wrapper\FreeImagePlus\dist\x64\FreeImagePlus.lib;..\lib-src\oifii_vs2017u\oifiilib\x64\Release\oifiilib.lib;..\lib-src\oifii_vs2017u\ow_ipl\x64\Release\ow_ipl.lib;..\lib-src\oifii_vs2017u\ow_iff\x64\Release\ow_iff.lib;winmm.lib;..\lib-src\portmidi(x64)\x64\Release\portmidi-static.lib` |


## Linking and Runtime Behavior

- **FreeImagePlus.lib**

Statically linked; ensure that the matching `FreeImagePlus.dll` (if used) is copied alongside the executable for image I/O.

- **oifiilib.lib** (MFC extension)

Requires `oifiilib.dll` at runtime; MFC’s DLL loading mechanism will load this extension.

- **ow_ipl.lib**, **ow_iff.lib**

Static libraries providing OW2 document/image processing routines.

- **portmidi_s.lib**, **portmidi-static.lib**

Static libraries for MIDI I/O. No additional DLLs required.

- **winmm.lib**

Windows multimedia system library; provides `timeSetEvent` and timer APIs.

At runtime, if any of the above dynamic DLLs (e.g., `FreeImagePlus.dll`, `oifiilib.dll`) are not in the system path, copy them from their respective `lib-src` folders into the output directory (`Debug\Win32`, `Release\x64`, etc.).

## Build Instructions

1. **Clone the Repository**

```batch
   git clone https://github.com/oifii/spivoronoitransparentmidiwin32_vs2017.git
   cd spivoronoitransparentmidiwin32_vs2017
```

1. **Open in Visual Studio 2017**

Load the `spivoronoimidiwin32.vcxproj` file.

1. **Select Configuration & Platform**

Choose Debug/Release and Win32/x64 as needed.

1. **Build**

Build → Build Solution (or press F7). All vendored libraries are prebuilt; no external build steps required.

1. **Copy Runtime DLLs**

If using Debug builds, copy any required `.dll` (e.g., `oifiilib.dll`, `FreeImagePlus.dll`) from `lib-src\…\Debug\` into the project’s output folder.

## Launch

- After a successful build, the executable (`spivoronoimidiwin32.exe`) is located in:
- `.\Debug\Win32\` or `.\Release\x64\`, etc.
- Ensure all dependency DLLs are present alongside the EXE.
- Double-click `spivoronoimidiwin32.exe` or run from a command prompt.

No command-line arguments are required for basic launch; optional script paths and MIDI device names can be configured via the UI once running.