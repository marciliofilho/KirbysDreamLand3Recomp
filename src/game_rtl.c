#include "game_rtl.h"
#include "common_cpu_infra.h"
#include "common_rtl.h"
#include "beam_frame_driver.h"
#include "snes/ppu.h"
#include "snes/snes.h"
#include "snes/apu.h"
#include "snes/cart.h"

static int _apu_primed = 0;

void GameRunOneFrame(void)
{
    if (!_apu_primed && g_snes && g_snes->apu) {
        /* Prime the SPC700 IPL ROM once the machine exists. On hardware the
         * APU boots within a few microseconds of reset, long before the
         * S-CPU reaches the SPC upload handshake ($00:DD61 checks $2140 for
         * $AA). The generic scheduler only advances the SPC on APU-port
         * writes, and the first write is inside that same handshake, so
         * without this the SPC is still at its reset vector when the
         * handshake polls and the upload is skipped forever. */
        RtlApuLock();
        apu_runCycles(g_snes->apu, 4096);
        RtlApuUnlock();
        _apu_primed = 1;
    }
    snes_beam_frame_driver_run_frame();
}

void GameDrawPpuFrame(void)
{
    snes_beam_frame_driver_draw_ppu_frame();
}

void GameSessionReset(void)
{
    _apu_primed = 0;
    snes_beam_frame_driver_reset();
}

void GameInitialize(void)
{
    /* Machine reset happens after this hook; the APU is primed at the first
     * frame instead (see GameRunOneFrame). */
    snes_beam_frame_driver_reset();
}

const RtlGameInfo kGameInfo = {
    .title = "kirbydreamland3",
    .initialize = &GameInitialize,
    .run_frame = &GameRunOneFrame,
    .draw_ppu_frame = &GameDrawPpuFrame,
    .save_name_prefix = "save",
    .session_reset = &GameSessionReset,
};
