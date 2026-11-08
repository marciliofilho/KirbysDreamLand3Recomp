# Changelog

## v0.1.1 — 2026-11-08

First properly versioned release.

- Windows x64 player package (`kirbydreamland3-0.1.1-windows-x64.zip`):
  prebuilt native build plus launcher assets, **no ROM**, no `src/gen` source and
  no toolchain. The player supplies their own USA dump.
- Default image-quality profile aligned with SNES ports: OpenGL, 4x integer
  scale, Sharp shader, linear filtering off, frame blending off, HD Mode 7 8x.
- Windows CI fix: removed hardcoded MSVC Windows SDK include paths.
- Public name standardized to "Kirby's Dream Land 3"; stale JPN references
  corrected (the supported dump is USA, `game_id = kirbydreamland3-usa`).
- Character artwork removed from the repository and its history.
- Supersedes v0.1.0, which was edited in place during initial packaging.

## v0.1.0 — 2026-11-08

Initial public release. Superseded by v0.1.1.
