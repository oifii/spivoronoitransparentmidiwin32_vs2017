# Using the App: Command-Line Reference (All Parameters)

## Advanced Rendering Controls: Polygon Fill Density, Background Modes, and Channel Selection

When running the application from the command line, arguments 17 through 23 control how Voronoi polygons are filled, how the background is rendered, and which image channel is used when exporting the diagram to an image file. These parameters feed directly into the call to `SaveVoronoiDiagramColoredWithPixelsetAsImagefile()`, allowing precise tuning of the visual output.

### Command-Line Arguments (Indices 17–23)

| Index | Global Variable | Type | Description |
| --- | --- | --- | --- |
| 17 | `global_portionofvoronoipolygonstofill` | float | Fraction of each Voronoi polygon interior eligible for fill. |


0.00 = 0% (no fill),

1.00 = 100% (full fill).                                            |

| 18 | `global_inverseprob_onpixelfill` | int | Inverse probability N for pixel sampling inside each polygon. |
| --- | --- | --- | --- |


A value of 4 means “1 out of 4 pixels” (25%) are filled.                              |

| 19 | `global_ibackgroundfill` | int | Background fill mode: |
| --- | --- | --- | --- |


0 = solid black,

1 = solid RGB color,

2 = select image channel as background.                                      |

| 20 | `global_ired` | int | Red component (0–255) of solid color background when mode 1 is selected. |
| --- | --- | --- | --- |
| 21 | `global_igreen` | int | Green component (0–255) of solid color background when mode 1 is selected. |
| 22 | `global_iblue` | int | Blue component (0–255) of solid color background when mode 1 is selected. |
| 23 | `global_imagechannel` | int | Channel index when mode 2 is selected: |


0 = all channels (RGB),

1 = red only,

2 = green only,

3 = blue only,

4 = gray composite (luma).                                   |

### Background Fill Modes

- **Mode 0 (Black):** Renders a solid black background beneath the Voronoi diagram.
- **Mode 1 (Solid RGB):** Uses the RGB triple (`global_ired`, `global_igreen`, `global_iblue`) as a uniform background color.
- **Mode 2 (Image Channel):** Extracts a single channel from the source image or a background‐colors image folder:
- 0 – all color channels combined (RGB).
- 1 – red channel.
- 2 – green channel.
- 3 – blue channel.
- 4 – gray composite (luma) .

### Export Call: SaveVoronoiDiagramColoredWithPixelsetAsImagefile()

After each frame is processed and the Voronoi diagram is computed, the application invokes:

```cpp
global_pOW2Doc->SaveVoronoiDiagramColoredWithPixelsetAsImagefile(
    utf8_decode(fullpath).c_str(),      // destination file path
    global_pOW2View,                    // view containing the rendered polygons
    global_portionofvoronoipolygonstofill,
    global_inverseprob_onpixelfill,
    global_ibackgroundfill,
    global_ired,
    global_igreen,
    global_iblue,
    global_imagechannel,
    global_pBackgroundColorsOW2Doc,     // background‐colors document (if any)
    global_voronoisetedgesfilterflag,   // edge filter flags
    global_voronoisetpointsfilterflag,  // interior filter flags
    global_pAlternateColorsOW2Doc,      // alternate‐colors document (if any)
    global_voronoisetedgesmapperflag,   // edge mapping flags
    global_voronoisetpointsmapperflag   // interior mapping flags
);
```

#### Parameter Mapping

| Parameter | Source Variable | Description |
| --- | --- | --- |
| `portionToFill` | `global_portionofvoronoipolygonstofill` | Fraction of polygon area to consider for filling. |
| `inverseProb` | `global_inverseprob_onpixelfill` | Inverse pixel-fill probability (1 in N pixels). |
| `backgroundMode` | `global_ibackgroundfill` | Background mode index (0, 1, 2). |
| `iRed`, `iGreen`, `iBlue` | `global_ired`, `global_igreen`, `global_iblue` | RGB components for solid‐color background (mode 1). |
| `imageChannel` | `global_imagechannel` | Selected image channel for background (mode 2). |
| `pBackgroundDoc` | `global_pBackgroundColorsOW2Doc` | Document providing a pool of background images (when using random backgrounds). |
| `edgesFilterFlag`, `pointsFilterFlag` | `global_voronoisetedgesfilterflag`, `global_voronoisetpointsfilterflag` | Bitmask flags to restrict rendering to certain detected areas (e.g., skin, red, green). |
| `pAlternateDoc` | `global_pAlternateColorsOW2Doc` | Document providing a pool of alternate‐color images for mapping polygon colors. |
| `edgesMapperFlag`, `pointsMapperFlag` | `global_voronoisetedgesmapperflag`, `global_voronoisetpointsmapperflag` | Bitmask flags to apply alternate‐color mapping to edges/interiors over specific detected areas. |


This combination of parameters gives full control over how much of each polygon is painted, how densely pixels are sampled, what lies behind the diagram, and which channel or solid color to use—enabling fine‐grained visual tuning for exports.