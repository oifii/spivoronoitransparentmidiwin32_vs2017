# Licensing and Legal – GPL Licensing and Source Headers

## GPL License Notice in `spivoronoimidiwin32.h`

Each primary source file in the project begins with the following GNU General Public License notice. This block asserts copyright, grants permission under GPL v3 or later, and disclaims warranty:

```cpp
/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

#include "resource.h"
```

This header appears at the top of **spivoronoimidiwin32.h**  and is identical across all `.cpp`, `.h`, and `.c` files, ensuring consistent license attribution.

## Project-Wide License Header Template (`spi.licenseheader`)

The file **spi.licenseheader** defines the template for the GPL notice and instructs code generators or IDE extensions to prepend it to new source files:

```text
extensions: .cs .cpp .h .c
/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
```

This template applies to source files (`.cpp`, `.h`, `.c`) as well as designer-generated and other code files, standardizing legal headers across the codebase .

## Inclusion in the Visual Studio Project

The project file **spivoronoimidiwin32.vcxproj** explicitly includes `spi.licenseheader` as a non-compilable item, ensuring IDE tooling recognizes and applies the license header to new and existing source files:

```xml
<ItemGroup>
  <None Include="ReadMe.txt" />
  <None Include="spivoronoimidiwin32.ico" />
  <None Include="spi.licenseheader" />
</ItemGroup>
```

This `<None>` entry ensures Visual Studio’s **File → Advanced Save Options** and any header-injection extensions can locate and use the license template .

## Redistribution and Modification under GPL v3

The project is licensed under the GNU General Public License version 3 (or any later version). Key obligations for anyone redistributing or modifying the code include:

- **Preserve Notices:** Keep intact all existing copyright notices, license

declarations, and warranty disclaimers in every file.

- **License Copy:** Distribute a copy of the full GPL v3 text (see **LICENSE** in the repository root) with any binary or source distribution .
- **Source Availability:** When distributing compiled binaries, make the corresponding complete source code available under the same GPL v3 terms.
- **Derivatives Must GPL:** Any modified version of the program must be licensed as a whole under GPL v3 (no sublicensing under more restrictive terms).
- **Modification Notices:** Prominently mark any changes you make and the date of the modification.
- **No Warranty:** The work is provided “as is,” without any warranty of merchantability or fitness for a particular purpose.

Interactive interfaces (e.g., message boxes or “About” dialogs) should display an “Appropriate Legal Notice” that informs users of their rights under the GPL.

## Source Header Maintenance and Compliance

- **Automated Insertion:** New source files should be created using project/IDE templates that automatically include the `spi.licenseheader`.
- **Manual Edits:** If manually adding new files, copy the license block exactly from **spi.licenseheader** to the top of each `.cpp`, `.h`, or `.c` file.
- **Modification Tracking:** When editing an existing file, update the header block or add a separate “Modified by” line below the original to indicate authorship and date of change.

Adhering to these practices ensures the project remains in full compliance with GPL v3 requirements and that all recipients retain the freedoms intended by the license.