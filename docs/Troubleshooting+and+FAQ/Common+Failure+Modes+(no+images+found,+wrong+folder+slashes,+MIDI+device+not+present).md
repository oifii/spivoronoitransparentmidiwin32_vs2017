# Troubleshooting and FAQ – Common Failure Modes

When running spivoronoimidiwin32, you may encounter situations where no images load, folder paths aren’t recognized correctly, or MIDI output fails silently. This guide explains the most frequent issues, their underlying causes, and concrete steps to fix them.

## 1. “No Images Found” at Startup

Symptom

• After launching, the window remains blank or the log shows zero filenames loaded from `spivoronoi_filenames.txt`.

Possible Causes

• The image folder path passed in `global_imagefolder` (or `global_backgroundcolorsimagefolder` / `global_alternatecolorsimagefolder`) is incorrect or not terminated by a backslash.

• All files in the folder use an extension other than `.jpg`, but the built‐in DIR filter only scans for `*.jpg`.

Solutions

1. Ensure each folder argument ends with a double backslash:
2. Background‐colors folder: must end with `\\`
3. Alternate‐colors folder: must end with `\\`
4. Confirm your images match the `*.jpg` filter used in the DIR command:

```cpp
   // spivoronoimidiwin32.cpp, WM_CREATE handler
   pathfilter = path + "\\*.jpg";
   systemcommand = "DIR \"" + pathfilter + "\" /B /S /O:N > spivoronoi_filenames.txt";
```

If your files are `.bmp`, change `*.jpg` to `*.bmp` in source before recompiling .

1. Verify the folder exists and the application has read permissions.

## 2. Incorrect Folder Slash Usage

Symptom

• DIR returns “File Not Found” or produces an empty filename list.

Cause

• Windows paths require backslashes (`\`), not forward slashes (`/`), and the code appends its own `\\*.jpg`.

Fix

• Always supply folder paths using Windows backslashes, with a trailing `\\`, for example:

```plaintext
  C:\Images\Set1\\
```

This ensures `path + "\\*.jpg"` expands correctly .

## 3. MIDI Device Not Present

Symptom

• No MIDI notes are generated; log contains PortMidi error text, and MIDI output is silently disabled.

Underlying Logic

```cpp
// After listing devices into global_midioutputdevicemap…
int midioutputdeviceid = 13;
auto it = global_midioutputdevicemap.find(global_midioutputdevicename);
if (it != global_midioutputdevicemap.end())
    midioutputdeviceid = it->second;
PmError err = Pm_OpenOutput(&global_pPmStream, midioutputdeviceid, …);
if (err) {
    fprintf(pFILE, "%s\n", Pm_GetErrorText(err));
    global_bsendmidi = false;  // disable MIDI on open error
}
```

Default Settings

```cpp
string global_midioutputdevicename = "loopMIDI Port 1";
bool   global_bsendmidi         = false;
```

Solutions

1. Enable MIDI and view the detected device list:
2. Set `global_bsendmidi = true` in code or via command‐line argument.
3. Check the debug log for lines starting with “MIDI output devices:” to see available names.
4. Update the device name:
5. Change `global_midioutputdevicename` to one of the logged names.
6. Rebuild the application or pass the new name as the corresponding command‐line argument.
7. Confirm that a virtual MIDI driver (e.g., loopMIDI) is installed and running.

## 4. Export Folder Not Writable

Symptom

• Voronoi‐rendered images fail to appear in your output directory, with no error dialog shown.

Cause

• The default output folder (`global_vorotransoutputfolder`) points to a directory that may not exist or isn’t writable.

Default Value

```cpp
string global_vorotransoutputfolder = "d:\\temp\\";
```

Fix

• Verify that `d:\temp\` exists and you have write permissions.

• To change it, update `global_vorotransoutputfolder` in source or supply the corresponding command‐line argument, then rebuild.

---

These steps address the most frequent failure modes in spivoronoimidiwin32. Following them should restore image loading, correct folder path handling, and reliable MIDI output.