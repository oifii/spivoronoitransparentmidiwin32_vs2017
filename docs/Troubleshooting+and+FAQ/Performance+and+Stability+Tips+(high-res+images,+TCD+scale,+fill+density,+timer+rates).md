# Troubleshooting and FAQ – Performance and Stability Tips

This section covers how to tune key parameters for heavy processing scenarios—particularly with large, high-resolution images—and how to control both Voronoi rendering load and MIDI event density.

## High-Resolution Images and TCD Scale

When processing very large images (e.g. 8K–12K), the **tree-crown detection (TCD)** convolution kernel can become a bottleneck. The following settings control its granularity and threshold:

- **global_TCDScale_inpixel**

­ Default: 3 (pixels)

­ Must be odd (3, 5, 7, … 31, etc.)

­ Larger scales reduce the number of local-maximum searches and speed up processing at the cost of coarser detection.

- **global_TCDThreshold_inlevel**

­ Default: 80 (level 0–255)

­ Raises this to skip low-intensity areas entirely (fewer candidate points).

**Tip:** For 12 K images, try a scale of 15–27 and threshold ≥ 100. You can override via command-line argument 30 (TCD scale) and 31 (TCD threshold).

## Controlling Fill Density

Voronoi interior fills can dominate CPU when set to 100% density. Two globals let you trade fidelity for speed:

- **global_portionofvoronoipolygonstofill**

­ Default: 1.00 (100% of polygons considered)

­ Lower to e.g. 0.50 to process only half of the polygons per frame.

- **global_inverseprob_onpixelfill**

­ Default: 4 (fills ~ 1/4 of each polygon’s pixels)

­ Increase to e.g. 8 for ~ 1/8 fill (sparser interiors).

**Tip:** Combine both controls to dramatically reduce per-frame raster work:

```cpp
global_portionofvoronoipolygonstofill = 0.5f;  // only 50% of polygons
global_inverseprob_onpixelfill    = 8;       // only 12.5% pixel fill
```

Use command-line args 17 (portion) and 18 (inverse-probability) to override at startup.

## Adjusting Processing Pace (Sleep Per Step)

After each Voronoi-MIDI cycle, the app calls:

```cpp
Sleep((int)(global_sleeptimepervoronoi_sec * 1000));
```

- **global_sleeptimepervoronoi_sec**

­ Default: 5 s

­ Increase (e.g. 8–16 s) to throttle CPU/GPU load and maintain UI responsiveness.

­ Decrease (e.g. 2 s) for faster iteration on lower-resolution images.

**Tip:** If you see high CPU spikes or UI lag, try doubling the sleep interval first.

## MIDI Timing and Event Scheduling

MIDI throughput is driven by two Win32 timers and the event-list mechanism:

- **Note playback timer**

­ Setup:

```cpp
  SetTimer(hWnd, global_miditimer, global_midistep_ms, NULL);
```

­ Default **global_midistep_ms**: 250 ms between processing slots  &

­ Lowering to 125 ms increases note density; raising to 500 ms reduces CPU use.

- **Program-change timer**

­ Default **global_midiprogramchangeperiod_ms**: 1000 * 3 * 60 = 180 000 ms (3 min)

- **Event-list size**

­ **global_pmeventlistsize**: 64 slots

­ If slots fill and events backlog, consider raising this value or ensuring your note-generation logic (`global_miditimerskip`) can skip frames.

**Tip:** For very rapid MIDI sequences, reduce `global_midistep_ms` first; only enlarge the event list if you observe drops due to slot exhaustion.

---

By tuning these four areas—TCD scale, fill density, sleep interval, and MIDI timer rates—you can optimize **spivoronoimidiwin32** for both high-resolution batch runs and lightweight, real-time visualizations.