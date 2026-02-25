# Install, Build, and Launch (Windows / Visual Studio 2017) – Building the App (Win32/x64, Debug/Release)

This section walks you through installing prerequisites, opening the project in Visual Studio 2017, configuring build settings, compiling for both Win32 and x64 in Debug and Release modes, and launching the resulting executable.

## Prerequisites

- **Visual Studio 2017** with the “Desktop development with C++” workload installed
- **Windows 10 SDK 10.0.17134.0** (or later)
- Third-party libraries checked out under the `lib-src` folder:
- FreeImagePlus (`freeimage_vs2017`)
- OIFII OIFIILIB / OW_IPL (`oifii_vs2017u`)
- PortMidi (`portmidi`)
- Ensure `lib-src\…\dist\…\*.lib` and include headers exist at the paths defined in the project

## 1. Open the Project

1. Launch Visual Studio 2017.
2. From the **File** menu, choose **Open › Project/Solution…**.
3. Navigate to the repository root and select **spivoronoimidiwin32.vcxproj**.

## 2. Select Configuration and Platform

1. In the Standard toolbar, locate the **Solution Platforms** and **Solution Configurations** dropdowns.
2. Choose one of:
3. Configuration: **Debug** or **Release**
4. Platform: **Win32** or **x64**
5. Alternatively, open **Build › Configuration Manager…**, then set each project row accordingly.

## 3. Verify Key Project Settings

Open **Project › Properties** and inspect the following under each Configuration | Platform:

| Setting | Expected Value | Location in `.vcxproj` |  |
| --- | --- | --- | --- |
| WindowsTargetPlatformVersion | 10.0.17134.0 | `<WindowsTargetPlatformVersion>` in Globals |  |
| PlatformToolset | v141 | `<PlatformToolset>` under each Configuration | Platform group |
| Use of MFC | Dynamic | `<UseOfMfc>Dynamic</UseOfMfc>` |  |
| Character Set | Unicode | `<CharacterSet>Unicode</CharacterSet>` |  |
| Preprocessor Definitions (Debug) | WIN32;_CRT_SECURE_NO_WARNINGS;_DEBUG;_WINDOWS;_AFXDLL | `<PreprocessorDefinitions>` in ClCompile |  |
| Runtime Library (Debug) | MultiThreadedDebugDLL | `<RuntimeLibrary>` |  |
| Preprocessor Definitions (Release) | WIN32;_CRT_SECURE_NO_WARNINGS;NDEBUG;_WINDOWS;_AFXDLL |  |  |
| Runtime Library (Release) | MultiThreadedDLL |  |  |
| Ignore Specific Default Libraries (Release) | LIBCMT | `<IgnoreSpecificDefaultLibraries>LIBCMT</IgnoreSpecificDefaultLibraries>` in Link |  |
| Additional Include Directories | `..\lib-src\…\Source\;..\lib-src\…\oifiilib;…` | `<AdditionalIncludeDirectories>` |  |
| Additional Dependencies (Win32/Debug) | FreeImagePlus.lib; oifiilib\Debug\ow_ipl.lib; etc. | `<AdditionalDependencies>` in Link |  |
| Additional Dependencies (x64/Release) | portmidi-static.lib; winmm.lib; ow_iff.lib; etc. |  |  |


## 4. Build the Project

> **Note:** The project relies on dynamic MFC (_AFXDLL). If you switch to static MFC, you will encounter linker errors and resource-loading issues.

1. With your desired Configuration/Platform selected, choose **Build › Build Solution** (or press **Ctrl + Shift + B**).
2. Monitor the **Output** window for errors:
3. **Cannot find Windows SDK version**: install or retarget to a version you have.
4. **MFC/ATL missing**: ensure the “Desktop development with C++” workload is installed.
5. **LIBCMT conflicts**: verify that `<IgnoreSpecificDefaultLibraries>LIBCMT</IgnoreSpecificDefaultLibraries>` is present in the Release Link settings.
6. On success, Visual Studio reports **“Build: 1 succeeded”**.

## 5. Locate and Launch the Executable

> **Incremental Linking:** - **Debug**: `<LinkIncremental>true</LinkIncremental>` - **Release**: `<LinkIncremental>false</LinkIncremental>`

1. In **Solution Explorer**, right-click the project and select **Open Folder in File Explorer**.
2. Navigate to:
3. `Debug\Win32\` or `Debug\x64\`
4. `Release\Win32\` or `Release\x64\`
5. Double-click **spivoronoimidiwin32.exe** to launch.
6. (Optional) In Visual Studio, press **F5** to run under the debugger.

## Common Build Pitfalls

- **Mismatched SDK Version:** If the installed Windows SDK differs from `10.0.17134.0`, update the project’s `<WindowsTargetPlatformVersion>` or install the required SDK.
- **Missing MFC DLLs:** Ensure that the MFC “Redistributable DLLs” matching your Visual Studio installation are present on your PATH or alongside the EXE.
- **Library Path Errors:** Verify that the folder structure under `lib-src` matches the AdditionalIncludeDirectories and AdditionalDependencies entries.
- **Linker “unresolved external symbol” Errors:**
- Confirm that all `.lib` files for FreeImagePlus, oifiilib, OW_IPL, PortMidi, and WinMM are referenced.
- Check that `_AFXDLL` is defined so MFC symbols are resolved from the shared DLL.

---

By following these steps, you will have successfully built and launched the spivoronoimidiwin32 application in both 32- and 64-bit configurations, for Debug and Release modes.