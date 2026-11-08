# Credits and attribution

This port exists because a lot of other people's work is doing the heavy
lifting. Thank you to everyone below.

## Port

- **Project and port work** — marciliofilho
  ([@marciliofilho](https://github.com/marciliofilho)).
  Title-specific hosting, the Kirby launcher identity, launcher assets, and the
  issue/validation work documented in the README.

## Frameworks

- **snesrecomp** — [RetroPortingToolKit](https://github.com/RetroPortingToolKit)
  / Matthew Stanley ([1379.tech](https://1379.tech)).
  License: **PolyForm Noncommercial 1.0.0** (`snesrecomp/LICENSE`).
  The SNES hardware models (65c816, PPU, APU/SPC700, DMA/HDMA, SA-1, other
  coprocessors), the static recompiler, the beam-aligned frame driver, the
  desktop host (ROM resolution, config, presenters, save states, rewind,
  post-mortem reports) and the third-party attribution catalog
  (`snesrecomp/THIRD_PARTY_ATTRIBUTION.md`).
- **recomp-ui** — [RetroPortingToolKit](https://github.com/RetroPortingToolKit)
  / Matthew Stanley.
  License: **MIT** (`recomp-ui/LICENSE`).
  The Dear ImGui launcher, ROM verification UI, theme system, controller
  configuration, hotkey editor, Mods page and the launcher asset catalog.
  The `kirby` theme in this project is an addition to that theme set.

## Third-party software

The framework vendors or links a number of third-party projects, each under its
own license. The authoritative list, with license texts, is
[`snesrecomp/THIRD_PARTY_ATTRIBUTION.md`](snesrecomp/THIRD_PARTY_ATTRIBUTION.md).
Highlights:

| Project | Use | License |
|---|---|---|
| [snesrev/zelda3](https://github.com/snesrev/zelda3) and [snesrev/smw](https://github.com/snesrev/smw) | Basis of the vendored C SNES hardware core | MIT |
| [ares](https://github.com/ares-emulator/ares) | SA-1, Cx4 and DSP-1 reference implementations | ISC |
| [libretro](https://github.com/libretro/RetroArch) | `libretro.h` API header | MIT |
| [SDL](https://github.com/libsdl-org/SDL) (SDL2/SDL3) | Window, input, audio, filesystem | zlib |
| [Dear ImGui](https://github.com/ocornut/imgui) | Launcher and overlay UI | MIT |
| [stb](https://github.com/nothings/stb) | Image loading (TGA/PNG/JPEG) | MIT / public domain |
| [IsoFrieze/SMWDisX](https://github.com/IsoFrieze/SMWDisX) | Super Mario World disassembly reference | see attribution |
| [perplexes/snesrecomp](https://github.com/perplexes/snesrecomp) | Native analyzer foundation | MIT |
| Lato (Łukasz Dziedzic) | Launcher body font | SIL OFL 1.1 |
| Noto Sans Symbols 2, Noto Color Emoji | Symbol/flag fallback and flag sheet | SIL OFL 1.1 |
| OpenMoji | Emoji fallback | CC BY-SA 4.0 |

The framework also names reference emulators used for behaviour checks
(bsnes libretro, Snes9x libretro) and other projects that inspired specific
pieces; see the attribution document for the full accounting. Those cores are
not part of the distributed game.

## Tools

- **CMake**, **Ninja**, **MSVC / GCC / Clang**, **Python 3**.
- **Snes9x libretro** — used during development as a reference oracle for
  frame-by-frame rendering comparisons. Not distributed with this project.
- **GNU Make / shell tooling** used by `tools/regen.sh`.

## Game

**Kirby's Dream Land 3** © 1997 HAL Laboratory / Nintendo.
"Kirby", "Kirby's Dream Land" and related names are trademarks of Nintendo /
HAL Laboratory. This is an unofficial fan project and is not affiliated with,
endorsed by, or sponsored by Nintendo or HAL Laboratory.

No game ROM, game code, extracted graphics, audio or other game assets are
included in this repository or its releases.

## Community

Thanks to the SNES reverse-engineering and static-recompilation community —
snesrev, the ares team, the libretro/RetroArch project, the snesrecomp
contributors, and everyone who documented the SA-1, the SPC700 and the SNES PPU
in public. None of this would be possible without that work.

If you believe something here is mis-attributed or used without permission,
please open an issue and it will be corrected promptly.
