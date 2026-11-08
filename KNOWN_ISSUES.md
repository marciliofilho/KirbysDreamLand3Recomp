# Known issues and limitations

This port is playable, but the launcher and runtime still have a few rough
edges. They are listed here so players and contributors know what is a real
bug, what is a framework limitation, and what simply is not exposed yet.

## Settings that are verified working

- ROM picker + digest verification (CRC32/SHA-256), region/file display.
- SAVES panel: `saves/save.srm`, Import and Clear.
- Player 1/2 source (None / Keyboard / Gamepad), deadzone slider, keyboard
  rebinds (`keybinds.ini`), gamepad rebinds (`config.ini [GamepadMap]`),
  per-device profiles.
- Display: window scale (1x–8x), renderer (Auto/OpenGL/SDL), fullscreen,
  display aspect (4:3 / 8:7 / 1:1), linear filtering, frame blending, shader
  presets (CRT Soft / LCD Grid / Sharp / Warm Composite), VSync, run-ahead.
- Audio: sample rate, volume.
- Hotkeys (13 rows), including Rewind (F12) and Save-state menu (F11).
- Rewind: on/off, buffer (50/100/150/200 snapshots), interval
  (1/4/8/12/15/30 frames), persisted to `[Rewind]`.
- Mods page: features, packages, install `.snesmod`, HD Mode 7 multiplier.
- Skip launcher on boot.

The launcher commits on Play and on window close; edits are written back to
`config.ini` / `keybinds.ini` surgically, preserving comments and other keys.

## Known limitations

1. **Per-player deadzone is displayed, but the runtime has one global value.**
   `[GamepadMap] Deadzone` (Player 1) drives both seats. `DeadzoneP2` is stored
   by the launcher but the SNES input poller only reads the global
   `GamepadDeadzone`. Until the runtime grows a per-seat deadzone, the Player 2
   slider has no independent effect.

2. **Frame blending wins over HD Mode 7.** With `[Graphics] FrameBlend = 1`,
   the presenter uses the base frame and HD Mode 7 is bypassed; the Mods page
   still reports the feature as Enabled. They are mutually exclusive today.

3. **HD Mode 7 only works with the OpenGL renderer.** With Software/Auto→SDL it
   is shown as Enabled but has no effect. Select OpenGL (or a shader preset,
   which switches to OpenGL) to use it.

4. **"Generate & rebuild" is only reachable from the first-run setup wizard.**
   With `src/gen/` present and a valid ROM, the launcher has no entry point for
   it. Regenerate with `tools/regen.sh` and rebuild.

5. **The "connected" badge means "assigned", not "device present".** A keyboard
   player (or an unplugged pad) is shown as connected. The gamepad dropdown
   does mark saved-but-absent devices as `(disconnected)`.

6. **A custom `[Graphics] WindowSize = WxH` overrides Window scale.** The
   launcher always shows the scale row; if the config pins an explicit window
   size, changing the scale does nothing until that key is removed.

7. **`config.local.ini` is applied last by the runtime but ignored by the
   launcher's KeyMap/GamepadMap editors.** A local override can therefore win
   over an edit made in the launcher. Edit the main `config.ini` or remove the
   local override.

8. **Launcher hotkey defaults (F8/F7) differ from the SNES runtime defaults
   (F12/F11) for a config.ini that lacks those `[KeyMap]` lines.** A fresh
   config written by this build has F11/F12, so this only affects older or
   hand-trimmed files. Set the keys explicitly in the launcher if in doubt.

9. **Audio can only be disabled in `config.ini`.** There is no Enable-audio row
   in the shared launcher; the host now preserves `[Sound] EnableAudio`
   instead of forcing it on. Use `EnableAudio = 0` if you need silence.

10. **Late-game coverage is incomplete.** Boot, menus, Level 1 and the
    level-entry/portal transitions are verified. Later stages, boss fights and
    every special effect have not been exhaustively tested.

## Reporting a bug

Please include:

- The ROM revision (CRC32/SHA-256) — only the USA dump `ec8a48f6` is supported.
- The launcher settings (`config.ini`) and controller/bind files if relevant.
- A save state (`.state`) and the `last_run_report.json` written beside the
  executable after a crash.
- What you did, what you expected, and what happened.
