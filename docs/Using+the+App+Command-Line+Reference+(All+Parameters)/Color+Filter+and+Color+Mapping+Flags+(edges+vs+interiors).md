# Using the App: Command-Line Reference

## Color Filter and Color Mapping Flags (Edges vs Interiors)

This section describes how to control where the Voronoi-diagram edges and polygon interiors are drawn, and where alternate-color mapping is applied, by using two sets of bitmask flags on the command line.  There are two stages:

1. **Filter Stage**: Determines which detected-color regions will have Voronoi edges or polygon interiors rendered at all.
2. **Mapping Stage**: When an alternate-colors image folder is provided, determines which of those same regions will use the alternate-color image to recolor edges or interiors instead of the default fill.

Both stages use the same set of color-detection bit flags.  You combine colors by summing their bit values.

---

## Command-Line Parameters

All parameters below appear in `CommandLineToArgvA(...)` parsing in **spivoronoimidiwin32.cpp** (argv indexes 1–n).  The relevant parameters are args 25–29 :

| Arg Index | Variable | Description |
| --- | --- | --- |
| 25 | global_voronoisetedgesfilterflag | Filter flag for **edges**: which detected-color areas to draw Voronoi edges over (default = `VORONOISET_COLOR_ALL`) . |
| 26 | global_voronoisetpointsfilterflag | Filter flag for **interiors**: which detected-color areas to draw Voronoi polygon interiors over (default = `VORONOISET_COLOR_ALL`) . |
| 27 | global_alternatecolorsimagefolder | Path to folder of alternate-colors images, used when any mapper flag is non-zero (must end with `\\`) . |
| 28 | global_voronoisetedgesmapperflag | Mapper flag for **edges**: which detected-color areas to recolor with an alternate-colors image (default = `VORONOISET_COLOR_MAP_NONE`) . |
| 29 | global_voronoisetpointsmapperflag | Mapper flag for **interiors**: which detected-color areas to recolor with an alternate-colors image (default = `VORONOISET_COLOR_MAP_NONE`) . |


---

## Filter Flags

When you set the **filter flag**, only the specified color regions will be rendered:

```c
// Default initialization in globals
int global_voronoisetedgesfilterflag   = VORONOISET_COLOR_ALL;
int global_voronoisetpointsfilterflag  = VORONOISET_COLOR_ALL;
```

| Bitmask Value | Constant | Effect |
| --- | --- | --- |
| 0 | VORONOISET_COLOR_ALL | Draw over **all** regions (no filtering). |
| 1 | VORONOISET_COLOR_HUMANSKIN | Draw only where **human skin** is detected. |
| 2 | VORONOISET_COLOR_RED | Draw only where **red** is detected. |
| 4 | VORONOISET_COLOR_GREEN | Draw only where **green** is detected. |
| 8 | VORONOISET_COLOR_BLUE | Draw only where **blue** is detected. |
| 16 | VORONOISET_COLOR_YELLOW | Draw only where **yellow** is detected. |
| 32 | VORONOISET_COLOR_ORANGE | Draw only where **orange** is detected. |


*Combine flags by summing. For example, `3` = `VORONOISET_COLOR_HUMANSKIN (1)` + `VORONOISET_COLOR_RED (2)` draws only over human-skin **and** red regions.*

---

## Mapping Flags

When an alternate-colors image folder is provided (arg 27) and the **mapper flag** is non-zero, those regions will be recolored using a random image from that folder:

```c
// Default initialization in globals
int global_voronoisetedgesmapperflag   = VORONOISET_COLOR_MAP_NONE;
int global_voronoisetpointsmapperflag  = VORONOISET_COLOR_MAP_NONE;
```

| Bitmask Value | Constant | Effect |
| --- | --- | --- |
| 0 | VORONOISET_COLOR_MAP_NONE | No alternate-color mapping. |
| 1 | VORONOISET_COLOR_MAP_HUMANSKIN | Map only **edges**/**interiors** over **human skin** areas using the alternate-colors image. |
| 2 | VORONOISET_COLOR_MAP_RED | Map only over **red** areas. |
| 4 | VORONOISET_COLOR_MAP_GREEN | Map only over **green** areas. |
| 8 | VORONOISET_COLOR_MAP_BLUE | Map only over **blue** areas. |
| 16 | VORONOISET_COLOR_MAP_YELLOW | Map only over **yellow** areas. |
| 32 | VORONOISET_COLOR_MAP_ORANGE | Map only over **orange** areas. |


*Combine flags by summing. For example, `5` = `VORONOISET_COLOR_MAP_HUMANSKIN (1)` + `VORONOISET_COLOR_MAP_GREEN (4)` maps only skin and green areas.*

---

## Putting It All Together

1. **Specify which regions get drawn** with args 25 (edges) and 26 (interiors).
2. **Optionally** specify an alternate-colors folder at arg 27.
3. **Specify which of those drawn regions** are recolored with alternates by args 28 (edges) and 29 (interiors).

### Example Usages

- Draw **all** edges but only **interiors** over red and yellow, no mapping:

```plaintext
  ... 0  (edges all)
      18 (interiors: 2+16)
      C:\AltColors\\
      0 0
```

- Draw **edges** over skin+red and **map** only those edges via alternate images; draw **all interiors** normally:

```plaintext
  ... 3   (1+2 filter edges)
      0   (all interiors)
      C:\AltColors\\
      3   (1+2 map edges)
      0   (no map interiors)
```

This two-stage bitmask approach gives you fine-grained control over exactly where Voronoi elements appear and where they take on alternate-color imagery.