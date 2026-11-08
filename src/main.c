/*
 * Kirby's Dream Land 3 — desktop host shim.
 *
 * Identity and hooks, nothing else. The host itself is the framework's
 * (snesrecomp/runner/src/desktop/host_main.h): the pre-boot launcher, ROM
 * resolution and digest checks, config.ini and keybinds.ini, the window and
 * the SDL / OpenGL presenters, audio, gamepads, the in-game save-state
 * browser and rewind filmstrip, the OSD, the pacing clock, crash handlers and
 * the post-mortem report, mod packages, Generate & rebuild, and the netplay
 * barrier when the project is built with it. A fix there reaches this
 * project on a submodule pull; nothing in this file needs to change for it.
 *
 * This file used to BE the host -- a ~700-line copy made at scaffold time --
 * so every project scaffolded before a fix kept the bug. Two ports of the
 * same game, a week apart, had different hosts.
 *
 * Nothing here ever ships a ROM. The player supplies one; the host makes
 * that easy (launcher, then positional argument, then a copy beside the
 * executable, then the rom.cfg cache, then a file picker) and checks what it
 * is handed against the digests in rom_identity.txt.
 *
 * Grow this file only with what is specific to THIS title: a custom
 * presenter (prepare_frame / draw_frame), an SPC player, a pacing rule
 * (keep_pacing_debt), a Mods provider. See SnesDesktopHostGame for the
 * complete list of hooks and what each is for.
 */

#include "host_main.h"
#include "game_rtl.h"
#include "recomp_launcher.h"          /* RecompLauncherCGameInfo (launcher identity) */
#include "snesrecomp_rom_identity.h"  /* generated from rom_identity.txt */

#ifndef __ANDROID__
#define SDL_MAIN_HANDLED 1
#endif
#include "desktop/sdl_compat.h"
#ifdef __ANDROID__
/* SDLActivity loads libmain.so and dlsyms its SDL_main. */
#define main SDL_main
#endif

#ifndef SNES_GAME_VERSION
#define SNES_GAME_VERSION "dev"
#endif

/* Per-title launcher identity, applied after the shared "snes" profile has
 * seeded the neutral CRT look. Only the palette is replaced: the console's
 * platform label, controller vocabulary, ROM noun and capability set stay the
 * framework's, so this hook cannot make the SNES page drift from its siblings.
 * "kirby" is the built-in theme in recomp-ui/src/common/launcher_theme.h. */
static void ConfigureLauncher(struct RecompLauncherCGameInfo *info)
{
    if (!info) return;
    info->theme = "kirby";
}

static const SnesDesktopHostGame kGameHost = {
    .display_name        = "Kirby's Dream Land 3",
    .window_title        = "Kirby's Dream Land 3 (Recompiled)",
    .region              = SNESRECOMP_ROM_REGION,
    .rom_file            = SNESRECOMP_ROM_FILE,
    .expected_sha256_hex = SNESRECOMP_ROM_EXPECTED_SHA256,
    .expected_crc32_hex  = SNESRECOMP_ROM_EXPECTED_CRC32,
    .game_id             = SNESRECOMP_ROM_GAME_ID,
    .build_version       = SNES_GAME_VERSION,
    .game_info           = &kGameInfo,
    .num_players         = 2,
    /* SNES pixel proportions (4:3 / 8:7 / 1:1) in the launcher's DISPLAY card. */
    .display_aspect_supported = 1,
    /* GLSL preset picker. snesrecomp_target_shader_presets() in CMake stages
     * the shared catalog next to the executable. */
    .shader_supported    = 1,
    /* Rewind rows (on/off, depth, interval) and persistence to [Rewind]. The
     * F12 hotkey already works with the built-in defaults; this is what lets
     * the player size or disable the 19 MB snapshot ring. */
    .rewind_settings     = 1,
    /* Battery-backed SRAM shows the launcher's SAVES panel. Leave NULL for a
     * title without one. The path is exe-relative. */
    .sram_path           = "saves/save.srm",
    .configure_launcher  = &ConfigureLauncher,
};

#ifndef __ANDROID__
#undef main   /* desktop: keep plain main() even if SDL_main.h remapped it */
#endif
int main(int argc, char **argv)
{
    return snesrecomp_desktop_main(&kGameHost, argc, argv);
}
