# Troubleshooting and FAQ – Reading debug.txt Logs

When you run spivoronoimidiwin32, a debug log named debug.txt is created in the application’s working directory. This file captures key internal steps—folder paths, random seeds, system commands used to enumerate images, and MIDI initialization details—which you can use to diagnose missing images, export failures, or MIDI setup issues.

## Log File Location and Lifecycle

- **Location**: Created in the same folder where the executable runs.
- **Creation**: At program start, before any image or MIDI processing, the file is opened for writing, overwriting any existing debug.txt:

```cpp
  pFILE = fopen("debug.txt", "w");
  if(pFILE){
      fprintf(pFILE, "%s\n", global_vorotransoutputfolder.c_str());
      fflush(pFILE);
  }
```

- **Closure**: On application exit (WM_DESTROY), the log is closed:

```cpp
  if(pFILE) fclose(pFILE);
```

## Key Sections of debug.txt

### 1. Output Folder Path

The very first line records the output folder where Voronoi-rendered images will be saved:

```plaintext
D:\video\animals-vorotrans\
```

This corresponds to `global_vorotransoutputfolder` and helps verify that your output path was parsed correctly .

### 2. Random Seed Initialization

Next, the log shows the seed used for all subsequent `rand()` calls:

```plaintext
random number generator seeded with 3168625
```

This seed is derived from `GetTickCount()` and logged immediately after folder path . Consistency in this number can help reproduce rendering sequences.

### 3. Image-Folder Enumeration

Under the WM_CREATE handler, the application issues a Windows DIR command to list all JPEG files in the input folder:

```text
DIR "D:\video\animals\\*.jpg"/B /S /O:N > spivoronoi_filenames.txt
```

That exact command string is echoed to the debug log:

```cpp
system(systemcommand.c_str());
if(pFILE){
    fprintf(pFILE, "%s\n", systemcommand.c_str());
    fflush(pFILE);
}
```

If you have enabled background-colors or alternate-colors folders, equivalent DIR commands for

`spivoronoi_backgroundcolors_filenames.txt` and

`spivoronoi_alternatecolors_filenames.txt`

are also logged in the same manner .

### 4. Image Filenames Loaded

As each image is opened for processing, its full path is written:

```plaintext
image filename D:\video\animals\01-endangered-species-mountain-gorilla(rgb-color-1-layer).jpg
image filename D:\video\animals\03_06_2017_Bobby_Magill_…(scaled-1052x701).jpg
…
```

This comes from:

```cpp
if(pFILE){
    fprintf(pFILE, "image filename %s\n", global_txtfilenames[global_imageid].c_str());
    fflush(pFILE);
}
```

Use these entries to confirm that the correct set of files was discovered and opened.

### 5. MIDI Initialization and Device Selection

If MIDI output is enabled (`global_bsendmidi == true`), the log includes:

- **Header**:

```plaintext
  MIDI output devices:
```

- **Device Enumeration**: One line per output device:

```plaintext
  0: CoreMIDI, loopMIDI Port 1
  1: CoreMIDI, Microsoft GS Wavetable Synth
  …
```

Logged via:

```cpp
  for(int i=0; i < Pm_CountDevices(); i++){
      const PmDeviceInfo* info = Pm_GetDeviceInfo(i);
      if(info->output){
          fprintf(pFILE, "%d: %s, %s\n", i, info->interf, info->name);
      }
  }
```

- **Selected Device Mapping**:

```plaintext
  loopMIDI Port 1 maps to 3
  device 3 selected
```

Indicates which device index was chosen based on `global_midioutputdevicename` .

- **Error Text** (if `Pm_OpenOutput` fails):

```plaintext
  PortMidi error: Unable to open device
```

Logged directly from `Pm_GetErrorText(err)` .

### 6. Cleanup and Finalization

No further entries are written after MIDI timers are set. The application proceeds to render and send MIDI events. On exit, timers are killed, notes are turned off, and `fclose(pFILE)` finalizes the log.

## Using debug.txt to Diagnose Common Issues

1. **No DIR Command Logged**

If you see only the output-folder line and seed, but no DIR command, the WM_CREATE block may not have executed—check your command-line arguments for the input folder path.

1. **Empty Filename List**

A DIR command logged but no subsequent `image filename` entries indicates that the folder was empty or contained no `.jpg` files. Verify your `global_imagefolder` and that files match the pattern.

1. **Failed Export to Image Files**

If you see filenames but no errors, but output folder remains empty, ensure that `global_vorotransoutputfolder` exists and is writable. The initial path line confirms where files should be written.

1. **No MIDI Output Devices Listed**

If you do not see the “MIDI output devices:” header, either `global_bsendmidi` is false or PortMidi failed to initialize. Check that PortMidi libraries are present and that `Pm_Initialize()` returned success.

1. **PortMidi Errors**

If the selected device line is present but followed immediately by an error string from `Pm_GetErrorText`, the device was found but could not be opened. Confirm no other application holds exclusive access and that the device name matches exactly.

## FAQ

**Q: debug.txt is not created at all.**

A: Ensure the working directory is writable by the user. Also verify that `fopen("debug.txt","w")` returned non-null by checking permissions or antivirus settings.

**Q: I see duplicate slashes in the DIR command (e.g., **`**D:\video\animals\\*.jpg**`**).**

A: The code concatenates folder path and pattern without normalizing trailing backslashes. This does not affect Windows’ DIR semantics but can be cleaned by removing the trailing slash in your `global_imagefolder` parameter.

**Q: I want to persist previous logs.**

A: By design, debug.txt is opened with mode `"w"`, which overwrites existing logs. To append instead, you could modify the code to use `"a"` for fopen.

---

Reading debug.txt in sequence—from the initial output folder and seed, through system commands and filename entries, to MIDI device logs—provides a clear step-by-step trace of the application's startup and resource discovery phases, making it your first line of defense when diagnosing setup or runtime issues.