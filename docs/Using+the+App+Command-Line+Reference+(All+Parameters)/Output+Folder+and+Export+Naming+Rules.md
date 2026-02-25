# Using the App: Command-Line Reference (All Parameters)

## Output Folder and Export Naming Rules

This section describes how to configure the output folder via the command line, how the application ensures that the folder exists before writing files, and how it derives each output filename from the corresponding input image’s base filename.

### 1. Command-Line Parameter for Output Folder

The output folder is set by the 16th command-line argument (zero-based index 16). In `_tWinMain`, after parsing earlier parameters, the code checks:

```cpp
if (nArgs > 16) {
    global_vorotransoutputfolder = szArgList[16];  // should be terminated by "\\"
}
```

This assigns the raw string provided by the user to the global variable `global_vorotransoutputfolder`. The folder path supplied **must** end with a backslash (`\\`) so that subsequent filename concatenation produces a valid path.

### 2. Output Folder Path Requirements

- **Trailing Backslash**

The folder path string passed in must end with `\\`.

- **Literal Use**

The application does **not** append or normalize path separators; it uses `global_vorotransoutputfolder` exactly as provided.

### 3. Ensuring the Output Folder Exists

Before exporting each Voronoi-diagram image, the application explicitly creates the directory if it does not already exist:

```cpp
string fullpath = global_vorotransoutputfolder;
_mkdir(fullpath.c_str());
```

Here, `_mkdir` (from `<direct.h>`) is invoked with the folder path. If the folder already exists, `_mkdir` returns an error code that is ignored; otherwise, it creates the directory so that the subsequent save operation succeeds.

### 4. Export Filename Construction

Each output file is named by taking the base filename (including extension) of the current input image and appending it to the output folder path:

```cpp
// 1. Start with the output folder
string fullpath = global_vorotransoutputfolder;

// 2. Extract base filename from the input list
string base_filename =
    global_txtfilenames[global_imageid]
        .substr(
            global_txtfilenames[global_imageid]
                .find_last_of("/\\") + 1
        );

// 3. Concatenate to form the full output path
fullpath += base_filename;

// 4. Export the rendered diagram
global_pOW2Doc->SaveVoronoiDiagramColoredWithPixelsetAsImagefile(
    utf8_decode(fullpath).c_str(),
    global_pOW2View,
    global_portionofvoronoipolygonstofill,
    global_inverseprob_onpixelfill,
    global_ibackgroundfill,
    global_ired,
    global_igreen,
    global_iblue,
    global_imagechannel,
    global_pBackgroundColorsOW2Doc,
    global_voronoisetedgesfilterflag,
    global_voronoisetpointsfilterflag,
    global_pAlternateColorsOW2Doc,
    global_voronoisetedgesmapperflag,
    global_voronoisetpointsmapperflag
);
```

- **Base Filename Extraction**

Uses `find_last_of("/\\") + 1` on the full input path to locate the final directory separator, then `substr` to copy from that position through the end of the string.

- **Preserved Extension**

Since the base filename includes the original extension (e.g., `.jpg`), the exported image filename will match the input filename.

- **Save Function**

`SaveVoronoiDiagramColoredWithPixelsetAsImagefile()` takes the full output path (folder + base filename) to write the rendered Voronoi diagram to disk.

---

With these rules, users can control exactly where rendered diagrams are saved and guarantee that filenames correspond one-to-one with their input images, simply by supplying:

```plaintext
spivoronoimidiwin32.exe  <imageFolder> <duration> … <beginScript> <endScript> "<outputFolderWithTrailingBackslash>" …
```