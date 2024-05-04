#ifndef TARGET_N64
#include <stdbool.h>
#endif
#include <PR/ultratypes.h>

#include "sm64.h"
#include "actors/common1.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "level_update.h"
#include "camera.h"
#include "print.h"
#include "ingame_menu.h"
#include "hud.h"
#include "segment2.h"
#include "area.h"
#include "save_file.h"
#include "print.h"

#ifdef EXT_OPTIONS_MENU
#ifndef TARGET_N64
#include "pc/configfile.h"
#else
int configHUD = TRUE;
#endif
#endif

#ifdef BETTERCAMERA
#include "extras/bettercamera.h"
#endif

/* @file hud.c
 * This file implements HUD rendering and power meter animations.
 * That includes stars, lives, coins, camera status, power meter, timer
 * cannon reticle, and the unused keys.
 **/

struct PowerMeterHUD {
    s8 animation;
    s16 x;
    s16 y;
    f32 unused;
};

// Stores health segmented value defined by numHealthWedges
// When the HUD is rendered this value is 8, full health.
static s16 sPowerMeterStoredHealth;

static struct PowerMeterHUD sPowerMeterHUD = {
    POWER_METER_HIDDEN,
    POWER_X,
    POWER_Y,
    1.0,
};

// Power Meter timer that keeps counting when it's visible.
// Gets reset when the health is filled and stops counting
// when the power meter is hidden.
s32 sPowerMeterVisibleTimer = 0;

u8 gHudIdle = 0;
s32 gHudIdleTimer = 0;
s32 gHudForceIdle = 0;
s32 gHudRedCoinTimer = 0;
f32 gHudOffset = 0;
f32 gHudRedCoinOffset = 0;

s16 sCameraHUDStatus = CAM_STATUS_NONE;

s32 set_hud_auto_x_pos(s32 x) {
    if (x > 200) {
        return GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(SCREEN_WIDTH - x);
    } else if (x <= 200 && x >= 120) {
        return x;
    } else {
        return GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(x);
    }
}

#ifdef HIGH_FPS_PC
static u32 sPowerMeterLastRenderTimestamp;
static s16 sPowerMeterLastY;
static Gfx *sPowerMeterDisplayListPos;

void patch_interpolated_hud(void) {
    if (sPowerMeterDisplayListPos != NULL) {
        Mtx *mtx = alloc_display_list(sizeof(Mtx));
        guTranslate(mtx, (f32) set_hud_auto_x_pos(sPowerMeterHUD.x), (f32) sPowerMeterHUD.y, 0);
        gSPMatrix(sPowerMeterDisplayListPos, VIRTUAL_TO_PHYSICAL(mtx),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
        sPowerMeterDisplayListPos = NULL;
    }
}
#endif

/**
 * Renders a rgba16 16x16 glyph texture from a table list.
 */
void render_hud_tex_lut(s32 x, s32 y, Texture *texture) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gSPDisplayList(gDisplayListHead++, &dl_hud_img_load_tex_block);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 15) << 2, (y + 15) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders a rgba16 16x16 glyph texture from a table list.
 */
void render_hud_tex_lut_big(s32 x, s32 y, Texture *texture) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gSPDisplayList(gDisplayListHead++, &dl_hud_img_load_tex_block_32);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 31) << 2, (y + 31) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders a rgba16 8x8 glyph texture from a table list.
 */
void render_hud_small_tex_lut(s32 x, s32 y, Texture *texture) {
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0,
                G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 7) << 2, (y + 7) << 2, G_TX_RENDERTILE,
                        0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders power meter health segment texture using a table list.
 */
void render_power_meter_health_segment(s16 numHealthWedges) {
    u8 *(*healthLUT)[];

    healthLUT = segmented_to_virtual(power_meter_health_segments_lut);

    gDPPipeSync(gDisplayListHead++);
    g_Tani_LoadTextureImage2(gDisplayListHead++, (*healthLUT)[numHealthWedges * 2], G_IM_FMT_RGBA,
                             G_IM_SIZ_16b, 32, 64, 0, 7) gSP1Triangle(gDisplayListHead++, 0, 1, 2, 0);
    gSP1Triangle(gDisplayListHead++, 0, 2, 3, 0);
    g_Tani_LoadTextureImage2(gDisplayListHead++, (*healthLUT)[(numHealthWedges * 2) + 1], G_IM_FMT_RGBA,
                             G_IM_SIZ_16b, 32, 64, 0, 7) gSP1Triangle(gDisplayListHead++, 4, 5, 6, 0);
    gSP1Triangle(gDisplayListHead++, 4, 6, 7, 0);
}

/**
 * Renders power meter display lists.
 * That includes the "POWER" base and the colored health segment textures.
 */
void render_dl_power_meter(s16 numHealthWedges) {
    Mtx *translateMtx;
    Mtx *scaleMtx;

    translateMtx = alloc_display_list(sizeof(Mtx));
    scaleMtx = alloc_display_list(sizeof(Mtx));

    if (translateMtx == NULL || scaleMtx == NULL) {
        return;
    }

    guTranslate(translateMtx, (f32) sPowerMeterHUD.x, (f32) sPowerMeterHUD.y, 0);
    guScale(scaleMtx, 0.75f, 0.75f, 1.0f);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(translateMtx++),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(scaleMtx++),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gSPDisplayList(gDisplayListHead++, &dl_power_meter_base);

    render_power_meter_health_segment(numHealthWedges);

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

/**
 * Power meter animation called when there's less than 8 health segments
 * Checks its timer to later change into deemphasizing mode.
 */
void animate_power_meter_emphasized(void) {
    s16 hudDisplayFlags = gHudDisplay.flags;

    if (!(hudDisplayFlags & HUD_DISPLAY_FLAG_EMPHASIZE_POWER)) {
        if (sPowerMeterVisibleTimer == 45.0f) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
        }
    } else {
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Power meter animation called after emphasized mode.
 * Moves power meter y pos speed until it's at 200 to be visible.
 */
static void animate_power_meter_deemphasizing(void) {
    s16 speed = 5;

    if (sPowerMeterHUD.y > HUD_POWER_METER_Y - 20) speed = 3;
    if (sPowerMeterHUD.y > HUD_POWER_METER_Y - 10) speed = 2;
    if (sPowerMeterHUD.y > HUD_POWER_METER_Y -  5) speed = 1;

    sPowerMeterHUD.y += speed;

    if (sPowerMeterHUD.y > HUD_POWER_METER_Y) {
        sPowerMeterHUD.y = HUD_POWER_METER_Y;
        sPowerMeterHUD.animation = POWER_METER_VISIBLE;
    }
}

/**
 * Power meter animation called when there's 8 health segments.
 * Moves power meter y pos quickly until it's at 301 to be hidden.
 */
static void animate_power_meter_hiding(void) {
    sPowerMeterHUD.y += 20;
    if (sPowerMeterHUD.y > HUD_POWER_METER_HIDDEN_Y) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Handles power meter actions depending of the health segments values.
 */
void handle_power_meter_actions(s16 numHealthWedges) {
    // Show power meter if health is not full, less than 8
    if (numHealthWedges < 8 && sPowerMeterStoredHealth == 8
        && sPowerMeterHUD.animation == POWER_METER_HIDDEN) {
        sPowerMeterHUD.animation = POWER_METER_EMPHASIZED;
        sPowerMeterHUD.y = HUD_POWER_METER_EMPHASIZED_Y;
    }

    // Show power meter if health is full, has 8
    if (numHealthWedges == 8 && sPowerMeterStoredHealth == 7) {
        sPowerMeterVisibleTimer = 0;
    }

    // After health is full, hide power meter
    if (numHealthWedges == 8 && sPowerMeterVisibleTimer > 45.0f) {
        sPowerMeterHUD.animation = POWER_METER_HIDING;
    }

    // Update to match health value
    sPowerMeterStoredHealth = numHealthWedges;

#ifndef BREATH_METER
    // If Mario is swimming, keep power meter visible
    if (gPlayerCameraState->action & ACT_FLAG_SWIMMING) {
        if (sPowerMeterHUD.animation == POWER_METER_HIDDEN
            || sPowerMeterHUD.animation == POWER_METER_EMPHASIZED) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
            sPowerMeterHUD.y = HUD_POWER_METER_EMPHASIZED_Y;
        }
        sPowerMeterVisibleTimer = 0;
    }
#endif
}

/**
 * Renders the power meter that shows when Mario is in underwater
 * or has taken damage and has less than 8 health segments.
 * And calls a power meter animation function depending of the value defined.
 */
f32 prevHurt = 0;
f32 hurt = 0;
f32 hurtTimer = 0;

f32 map_value(f32 srcMin, f32 srcMax, f32 dstMin, f32 dstMax, f32 x) {
    return (x - srcMin) / (srcMax - srcMin) * (dstMax - dstMin) + dstMin;
}

void render_hud_power_meter(void) {
    s16 shownHealthWedges = gHudDisplay.wedges;
    f32 powerMeterX, powerMeterY;
    f32 srcX, srcY, dstX, dstY;
    f32 interpolation, shakiness, range;
    prevHurt = hurt;
    hurt = gMarioState->hurtCounter;
    if (hurtTimer != 0) {
        hurtTimer--;
        if (hurtTimer < 16 && gMarioState->health < 0x0300) hurtTimer = 16;
    }
    if (hurt != 0 && prevHurt == 0) hurtTimer = 90;
    powerMeterX = SCREEN_CENTER_X;
    powerMeterY = SCREEN_HEIGHT - 32 - 10;
    if (hurtTimer > 15) {
        powerMeterX = SCREEN_WIDTH / 2.f - 28;
        powerMeterY = SCREEN_HEIGHT / 2.f + 32;
    }
    else if (hurtTimer <= 15 && hurtTimer != 0) {
        srcX = SCREEN_WIDTH / 2.f - 28;
        srcY = SCREEN_HEIGHT / 2.f + 32;
        dstX = powerMeterX;
        dstY = powerMeterY;
        interpolation = 1 - sqrt(1 - map_value(15, 1, 0, 1, hurtTimer));
        powerMeterX = map_value(0, 1, srcX, dstX, interpolation);
        powerMeterY = map_value(0, 1, srcY, dstY, interpolation);
    }
    shakiness = gMarioState->hurtCounter;
    range = (s32)(shakiness * 3);
    if (range > 0) {
        powerMeterX = powerMeterX + (random_float() * (range + range) - range);
        powerMeterY = powerMeterY + (random_float() * (range + range) - range);
    }
    sPowerMeterHUD.x = powerMeterX;
    sPowerMeterHUD.y = powerMeterY;
    render_dl_power_meter(shownHealthWedges);
}

/**
 * Renders the amount of lives Mario has.
 */
void render_hud_mario_lives(void) {
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(71) + (1 - gHudOffset) * 120, HUD_TOP_Y, ","); // 'Mario Head' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(56) + (1 - gHudOffset) * 120, HUD_TOP_Y, "*"); // 'X' glyph
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(44) + (1 - gHudOffset) * 120, HUD_TOP_Y, "%d", gHudDisplay.lives);
}

void render_hud_coins(void) {
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(71) + (1 - gHudOffset) * 120, HUD_TOP_Y - 40, "+"); // 'Coin' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(56) + (1 - gHudOffset) * 120, HUD_TOP_Y - 40, "*"); // 'X' glyph
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(44) + (1 - gHudOffset) * 120, HUD_TOP_Y - 40, "%d", gHudDisplay.coins);
}

/**
	@@ -432,22 +471,19 @@ void render_hud_coins(void) {
 */
void render_hud_stars(void) {
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(71) + (1 - gHudOffset) * 120, HUD_TOP_Y - 20, "-"); // 'Star' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(56) + (1 - gHudOffset) * 120, HUD_TOP_Y - 20, "*"); // 'X' glyph
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(44) + (1 - gHudOffset) * 120,HUD_TOP_Y - 20, "%d", gHudDisplay.stars);
}

/**
 * Unused function that renders the amount of keys collected.
 * Leftover function from the beta version of the game.
 */
void render_hud_keys(void) {
    char* keys[] = { ".", "/" };
    for (u8 i = 0; i < 3; i++) {
        print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(71) + (1 - gHudOffset) * 120 + i * 15, HUD_TOP_Y - 60, keys[i < gMarioState->numKeys]);
    }
}


/**
 * Renders the timer when Mario start sliding in PSS.
 */
void render_hud_timer(void) {
    u8 *(*hudLUT)[58] = segmented_to_virtual(&main_hud_lut);
    u16 timerValFrames = gHudDisplay.timer;
    // 30 frames * 60 seconds (1 minute) = 1800
    u16 timerMins = timerValFrames / 1800;
    u16 timerSecs = (timerValFrames - (timerMins * 1800)) / 30;
    u16 timerFracSecs = (timerValFrames - (timerMins * 1800) - (timerSecs * 30)) / 3;
    char *str;
#ifdef VERSION_EU
    switch (eu_get_language()) {
        case LANGUAGE_ENGLISH:
            str = "TIME";
            break;
        case LANGUAGE_FRENCH:
            str = "TEMPS";
            break;
        case LANGUAGE_GERMAN:
            str = "ZEIT";
            break;
    }
#else
    str = "TIME";
    // If set_hud_auto_x_pos is used, the "TIME" text will be very separate from the actual timer
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(SCREEN_WIDTH - HUD_TIME_X), HUD_TIME_Y, str);
#endif

    print_text_fmt_int(set_hud_auto_x_pos(HUD_TIME_MIN_X), HUD_TIME_Y, "%0d", timerMins);
    print_text_fmt_int(set_hud_auto_x_pos(HUD_TIME_SEC_X), HUD_TIME_Y, "%02d", timerSecs);
    print_text_fmt_int(set_hud_auto_x_pos(HUD_TIME_FSEC_X), HUD_TIME_Y, "%d", timerFracSecs);

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(set_hud_auto_x_pos(HUD_TIME_MIN_A_X), HUD_TIME_A_Y, (*hudLUT)[GLYPH_APOSTROPHE]);
    render_hud_tex_lut(set_hud_auto_x_pos(HUD_TIME_SEC_AA_X), HUD_TIME_A_Y, (*hudLUT)[GLYPH_DOUBLE_QUOTE]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/**
 * Sets HUD status camera value depending of the actions
 * defined in update_camera_status.
 */
void set_hud_camera_status(s16 status) {
    sCameraHUDStatus = status;
}

/**
 * Renders camera HUD glyphs using a table list, depending of
 * the camera status called, a defined glyph is rendered.
 */
void render_hud_camera_status(void) {
    u8 *(*cameraLUT)[6] = segmented_to_virtual(&main_hud_camera_lut);
    s32 x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(54);
    s32 y = 205;

    if (sCameraHUDStatus == CAM_STATUS_NONE) {
        return;
    }

#ifdef BETTERCAMERA
    if (gPuppyCam.enabled && !gCurrDemoInput) {
        puppycam_hud();
        return;
    }
#endif

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(x, y, (*cameraLUT)[GLYPH_CAM_CAMERA]);

    switch (sCameraHUDStatus & CAM_STATUS_MODE_GROUP) {
        case CAM_STATUS_MARIO:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_MARIO_HEAD]);
            break;
        case CAM_STATUS_LAKITU:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_LAKITU_HEAD]);
            break;
        case CAM_STATUS_FIXED:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_FIXED]);
            break;
    }

    switch (sCameraHUDStatus & CAM_STATUS_C_MODE_GROUP) {
        case CAM_STATUS_C_DOWN:
            render_hud_small_tex_lut(x + 4, y + 16, (*cameraLUT)[GLYPH_CAM_ARROW_DOWN]);
            break;
        case CAM_STATUS_C_UP:
            render_hud_small_tex_lut(x + 4, y - 8, (*cameraLUT)[GLYPH_CAM_ARROW_UP]);
            break;
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

void render_hud_red_coins() {
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(8), 16 - (1 - gHudRedCoinOffset) * 120, "#"); // 'Coin' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(23), 16 - (1 - gHudRedCoinOffset) * 120, "*"); // 'X' glyph
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(35), 16 - (1 - gHudRedCoinOffset) * 120, "%d", gRedCoinsCollected);
}

void hud_set_idle(u8 idle) {
    gHudIdle = idle;
}

void hud_force_idle() {
    gHudIdleTimer = MAX(15, gHudIdleTimer);
    gHudForceIdle = 150;
}


/**
 * Render HUD strings using hudDisplayFlags with it's render functions,
 * excluding the cannon reticle which detects a camera preset for it.
 */
void render_hud(void) {
    if (gHudIdle || gHudForceIdle > 0) {
        gHudIdleTimer++;
        if (gHudIdleTimer > 60) gHudIdleTimer = 60;
    }
    else {
        gHudIdleTimer--;
        if (gHudIdleTimer < 0) gHudIdleTimer = 0;
    }
    if (gHudForceIdle > 0) gHudForceIdle--;
    gHudOffset = (1 - (1 - gHudIdleTimer / 60.f) * (1 - gHudIdleTimer / 60.f));
    if (gRedCoinsCollected > 0) {
        gHudRedCoinTimer++;
        if (gHudRedCoinTimer > 60) gHudRedCoinTimer = 60;
        gHudRedCoinOffset = (1 - (1 - gHudRedCoinTimer / 60.f) * (1 - gHudRedCoinTimer / 60.f));
    }
    s16 hudDisplayFlags = gHudDisplay.flags;

    if (hudDisplayFlags == HUD_DISPLAY_NONE) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterStoredHealth = 8;
        sPowerMeterVisibleTimer = 0;
    } else {
#ifdef VERSION_EU
        // basically create_dl_ortho_matrix but guOrtho screen width is different
        Mtx *mtx = alloc_display_list(sizeof(*mtx));

        if (mtx == NULL) {
            return;
        }

        create_dl_identity_matrix();
        guOrtho(mtx, -16.0f, SCREEN_WIDTH + 16, 0, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx),
                  G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
#else
        create_dl_ortho_matrix();
#endif

        if (gCurrentArea != NULL && gCurrentArea->camera->mode == CAMERA_MODE_INSIDE_CANNON) {
            render_hud_cannon_reticle();
        }

#ifdef EXT_OPTIONS_MENU
        if (!configHUD) {
            return;
        }
#endif
#if SHOW_LIVES
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_LIVES) {
            render_hud_mario_lives();
        }
#endif
#if SHOW_COINS
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_COIN_COUNT) {
            render_hud_coins();
            render_hud_red_coins();
        }
#endif
#if SHOW_STARS
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_STAR_COUNT) {
            render_hud_stars();
        }
#endif
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_KEYS) {
            render_hud_keys();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_CAMERA_AND_POWER) {
            render_hud_power_meter();
#if SHOW_CAM
            render_hud_camera_status();
#endif
        }
#if SHOW_TIMER
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_TIMER) {
            render_hud_timer();
        }
#endif
    }
}
