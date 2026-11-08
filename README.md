# Kirby's Dream Land 3 — Native Recompilation

A native, statically recompiled PC port of **Kirby's Dream Land 3 (USA)** for the
Super Nintendo, built on the [snesrecomp](https://github.com/RetroPortingToolKit/snesrecomp)
framework and the [recomp-ui](https://github.com/RetroPortingToolKit/recomp-ui)
launcher.

The game's 65c816 code is translated ahead-of-time from the player's own ROM into
C, then compiled into a native executable. There is no emulator core in the
gameplay path: the SNES hardware model (PPU, APU, DMA, SA-1) is the framework's,
and the game code runs as compiled C.

> **You must legally own a copy of Kirby's Dream Land 3 (USA).**
> No ROM data and no recompiler output is distributed with this project — not in
> the repository, not in releases. The recompiled C (`src/gen/`) is generated
> locally from your own dump and is never committed.

> This is an unofficial fan project. It is **not affiliated with, endorsed by,
> or sponsored by Nintendo or HAL Laboratory**. "Kirby" and "Kirby's Dream Land"
> are trademarks of Nintendo / HAL Laboratory. See [Legal](#legal).

## Status

**Playable.** The port boots, reaches the title/menu flow, enters the first
level and completes the level-entry/portal raster transitions. Verified on
Windows 11 x64.

What has been validated:

- Boot, Nintendo/SA-1 handshake, menus, save SRAM.
- Level 1 entry, gameplay, and the fade/iris transition into a stage.
- Raster splits: the game programs its display registers from a raster IRQ at
  scanline 167; the port delivers that IRQ at the latch line, not in vblank.
- Mid-frame palette swaps: the PPU raster journal carries CGRAM per line, so a
  stage that patches its palette mid-field renders the intended colours.

Still a work in progress: later stages, special chips/effects and edge cases
have not all been exhaustively tested. Bug reports with the ROM revision and a
save state are welcome. See [`KNOWN_ISSUES.md`](KNOWN_ISSUES.md) for the
launcher/runtime limitations and the verified settings list.

## ROM identity

| | |
|---|---|
| Title | Kirby's Dream Land 3 |
| Region | USA |
| File used in testing | `Kirby's Dream Land 3 (USA).sfc` |
| Size | 4,194,304 bytes (4 MiB) |
| Mapping | SA-1 (LoROM) |
| Coprocessor | SA-1 |
| CRC32 | `ec8a48f6` |
| MD5 | `201e7658f6194458a3869dde36bf8ec2` |
| SHA-1 | `12aff7538f43641a1e2bf424593df5b49fe150f6` |
| SHA-256 | `b50bf9d95485e8aeb7a6730e9f9f9c9c4ec23a85b336a4fb2e3b63034531e36f` |

These digests come from [`rom_identity.txt`](rom_identity.txt), the single source
of truth shared by the build, `tools/regen.sh` and CI. The launcher refuses a
dump that does not match them.

## Requirements

- **Windows 10/11 x64** (tested), or Linux/macOS with a C11/C++17 toolchain.
- CMake 3.20+ and Ninja (or another CMake generator).
- Visual Studio 2022 Build Tools (MSVC) on Windows, or GCC/Clang elsewhere.
- Python 3 (for `tools/regen.sh` and the snesrecomp CLI).
- SDL3 (the CMake build fetches/uses the framework's SDL target).
- Your own **Kirby's Dream Land 3 (USA)** ROM.

The prebuilt **setup pack** released from CI contains the setup host, the
recompiler and the toolchain; it generates and builds the playable game on your
machine from your own ROM. Source builds do the same steps directly.

## Build from source

```sh
git clone --recurse-submodules https://github.com/marciliofilho/KirbysDreamLand3Recomp.git
cd KirbysDreamLand3Recomp

# Point at your own dump (or put kirby3.sfc beside the repo).
export SNESRECOMP_ROM="/path/to/Kirby's Dream Land 3 (USA).sfc"

# Regenerate src/gen/*.c from the ROM (verifies the digests first).
bash tools/regen.sh --rom "$SNESRECOMP_ROM"

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

`src/gen/` is recompiler output derived from the ROM: it is git-ignored and must
never be committed. Re-run `tools/regen.sh` after changing anything under
`recomp/`.

On Windows with MSVC, use the Developer Command Prompt (or `vcvars64.bat`) and
the same CMake commands.

## Run

```sh
./build/Kirbydreamland3SNESRecomp
```

With no ROM on the command line the build opens the launcher: ROM picker with
digest verification, SAVES panel, display/audio/input settings, hotkeys, rewind
and the Mods page. The choice is cached in `rom.cfg` beside the executable.

```sh
./build/Kirbydreamland3SNESRecomp "/path/to/Kirby's Dream Land 3 (USA).sfc" --no-launcher
```

Command-line extras: `--launcher`, `--no-launcher`, `--config <path>`,
`--script <path>` (scripted input), `--framedump <dir>`, `--paused`,
`--resume-state <path>`, `--help`.

### Controls (defaults)

| SNES | Keyboard | Gamepad |
|---|---|---|
| D-pad | Arrow keys | D-pad / left stick |
| A | X | B |
| B | Z | A |
| X | S | Y |
| Y | A | X |
| L / R | C / V | LB / RB |
| Start | Return | Start |
| Select | Right Shift | Back |

Hotkeys: `Alt+Enter` fullscreen, `Ctrl+R` reset, `Shift+P` pause, `Tab`
fast-forward, `Ctrl+Up/Down` window size, `F11` save-state menu, `F12` rewind.
All of them are rebindable in the launcher.

## Launcher identity

The launcher ships a Kirby-specific palette (`kirby` in
`recomp-ui/src/common/launcher_theme.h`): twilight-plum ground, Kirby pink as the
primary accent, Warp Star yellow for section headings, sky-blue focus ring and
CRT scanlines. No character artwork is bundled: the GAME card uses the
launcher's generic cartridge placeholder and the header uses the shared
recomp-ui brand mark.

## Layout

| Path | Contents |
|---|---|
| `src/` | Port host code: `main.c` (identity/hooks), `game_rtl.c` (frame glue) |
| `src/gen/` | Recompiled game C — generated locally, never committed |
| `recomp/` | Analysis input: `bank*.cfg`, `symbols.toml`, generated `funcs.h` |
| `rom_identity.txt` | ROM digests (build, regen, CI, launcher) |
| `snesrecomp/` | Framework submodule (CPU/PPU/APU/DMA/SA-1, recompiler, host) |
| `recomp-ui/` | Launcher submodule (Dear ImGui) |
| `tools/regen.sh` | ROM → C pipeline |
| `scripts/package_release.sh` | Player-facing setup zip |
| `framework_pins.txt` | Framework commits this build is pinned to |

## Technical notes

- **Frame model.** The port uses the framework's beam-aligned driver: one frame
  is one PPU field, cut at the beam's vblank edge. Interrupts are delivered where
  the beam latches them, and the field is rasterised from a per-line register
  journal with real HDMA (`snesrecomp/runner/src/beam_frame_driver.c`).
- **Raster IRQ in the AOT tier.** The game's split IRQ latches at `V=167`; the
  fixed interpreter sampled the IRQ line between instructions, but the AOT tier
  used to stop only at the end-of-field deadline, delivering the handler in
  vblank. `interp_bridge.c` now samples the CPU IRQ line at AOT block boundaries
  as well, so the handler runs at the latch line.
- **Per-line CGRAM.** `ppu.c` journals the palette (and the `$2122` port latch)
  as per-line display state, so a mid-field palette patch renders correctly and
  the guest's live palette is restored after the reconstructed field.
- **APU priming.** `game_rtl.c` primes the SPC700 IPL ROM once the machine
  exists; the first APU-port write happens inside the SA-1 upload handshake, and
  without priming the SPC would still be at its reset vector.

## Credits

See [`CREDITS.md`](CREDITS.md) for the full list. In short:

- **snesrecomp** — RetroPortingToolKit / Matthew Stanley (PolyForm Noncommercial
  1.0.0). CPU/PPU/APU/DMA/SA-1 models, recompiler, desktop host, frame driver.
- **recomp-ui** — RetroPortingToolKit / Matthew Stanley (MIT). Dear ImGui
  launcher, theme system, ROM verification UI.
- **Third-party** — SDL, Dear ImGui, stb, ares (ISC), snesrev zelda3/smw (MIT),
  Lato, Noto Sans Symbols 2, OpenMoji, and others. Full attribution lives in
  `snesrecomp/THIRD_PARTY_ATTRIBUTION.md` and the submodules' own notices.
- **Game** — Kirby's Dream Land 3 © 1997 HAL Laboratory / Nintendo.

## Legal

This project is an unofficial, noncommercial fan work. It contains no game ROM,
no game code, and no assets extracted from the ROM. The player must supply their
own legally obtained cartridge dump. The project is not affiliated with,
endorsed by, or sponsored by Nintendo or HAL Laboratory. All trademarks and
copyrights in the game belong to their respective owners.

The project's own source is licensed under the **PolyForm Noncommercial License
1.0.0** — see [`LICENSE`](LICENSE). The framework submodules carry their own
licenses (`snesrecomp/LICENSE`, `recomp-ui/LICENSE`); nothing here overrides
them. If you are a rights holder and want content changed or removed, please
open an issue.
