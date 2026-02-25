# Install, Build, and Launch (Windows / Visual Studio 2017)

## Running the Executable: Quick Start (minimum arguments)

This quick-start guide covers the minimal invocation of the `spivoronoimidiwin32.exe` on Windows using Visual Studio 2017 (v141). You only need to supply the path to your image folder; the application will launch a layered, frameless-ish window, cycle through the images in that folder, and render a continuous Voronoi-diagram animation.

---

### 1. Minimum Invocation

Open a Command Prompt and run:

```bat
C:\path\to\spivoronoimidiwin32.exe  C:\path\to\image\folder
```

Here, `C:\path\to\image\folder` becomes `argv[1]` and sets the folder from which `.jpg` files will be loaded .

All other parameters use their defaults:

- `global_duration_sec = 3600` seconds (1 hour)
- `global_sleeptimepervoronoi_sec = 5` seconds between frames
- Window position `(global_x,global_y) = (100,100)`
- Window size `(global_xwidth,global_yheight) = (300,300)`
- Window alpha `global_alpha = 255` (fully opaque)
- Title bar shown by default (`global_titlebardisplay = 1`)
- Menu bar hidden (`global_menubardisplay = 0`)
- Keyboard accelerators disabled (`global_acceleratoractive = 0`) .

---

### 2. Argument Parsing

On startup, `_tWinMain` invokes a custom `CommandLineToArgvA` to split the command line into `szArgList` and `nArgs`. It then applies:

```cpp
if(nArgs > 1) global_imagefolder = szArgList[1];
if(nArgs > 2) global_duration_sec = atof(szArgList[2]);
if(nArgs > 3) global_sleeptimepervoronoi_sec = atof(szArgList[3]);
// …and so on for position, size, alpha, title/menu/accelerator flags
```

---

### 3. Window Initialization

`InitInstance` registers the window class and creates the main window at `(global_x,global_y)` with dimensions `(global_xwidth,global_yheight)`. It applies layered-window attributes for per-pixel alpha blending:

```cpp
global_hwnd = CreateWindow(…,
    WS_OVERLAPPEDWINDOW or WS_POPUP,
    global_x, global_y,
    global_xwidth, global_yheight, …);

SetWindowLong(global_hwnd, GWL_EXSTYLE,
    GetWindowLong(global_hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
SetLayeredWindowAttributes(global_hwnd, 0, global_alpha, LWA_ALPHA);
ShowWindow(global_hwnd, nCmdShow);
UpdateWindow(global_hwnd);
```

A one-shot multimedia timer is scheduled to fire after 100 ms, invoking `StartGlobalProcess` to begin the image-processing loop .

---

### 4. Initial Image Enumeration

Upon receiving `WM_CREATE`, the window’s `WndProc` executes a `DIR` command to list all `.jpg` files under `global_imagefolder` (recursive, sorted by name) into `spivoronoi_filenames.txt`. It then reads each line into `global_txtfilenames`:

```cpp
system("DIR \"<global_imagefolder>\\*.jpg\" /B /S /O:N > spivoronoi_filenames.txt");
ifstream ifs("spivoronoi_filenames.txt");
while(getline(ifs, temp)) {
    global_txtfilenames.push_back(temp);
}
```

---

### 5. Voronoi Render Loop

The callback `StartGlobalProcess` implements the main loop:

1. Record `global_startstamp_ms = GetTickCount()`.
2. While `GetTickCount() - global_startstamp_ms < global_duration_sec * 1000`:
3. Load the next image path from `global_txtfilenames[global_imageid++]`.
4. Create or reuse `CAutoRescaleOW2Doc` to open the file as a pixel set.
5. Instantiate `COW2View`, assign the document, and trigger `InvalidateRect`/`WM_PAINT`.
6. In `WM_PAINT`, `COW2View::OnDraw` renders the Voronoi diagram.
7. Sleep for `global_sleeptimepervoronoi_sec * 1000` milliseconds.
8. After the loop ends, post `WM_DESTROY` to close the window and exit.

The default sleep interval is 5 seconds between frames , and the loop runs for the default duration of 3600 seconds .

---

### 6. What You Should See

- A frameless (or standard caption if enabled) window appears at 100 × 100 pixels, sized 300 × 300, with full opacity.
- The first image from your folder is loaded and its Voronoi-diagram visualization is drawn.
- Every 5 seconds, the next image in the folder is processed and rendered.
- After approximately 1 hour (3600 s) or once all images have been cycled through, the window closes and the application exits.

This minimal invocation demonstrates the core behavior: loading images, computing and rendering Voronoi diagrams in a timed loop, and clean shutdown. Adjust additional command-line parameters to fine-tune duration, frame interval, window appearance, and MIDI integration.