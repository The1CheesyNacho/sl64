#ifndef HUD_H
#define HUD_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

enum PowerMeterAnimation {
    POWER_METER_HIDDEN,
    POWER_METER_EMPHASIZED,
    POWER_METER_DEEMPHASIZING,
    POWER_METER_HIDING,
    POWER_METER_VISIBLE
};

enum CameraHUDLut {
    GLYPH_CAM_CAMERA,
    GLYPH_CAM_MARIO_HEAD,
    GLYPH_CAM_LAKITU_HEAD,
    GLYPH_CAM_FIXED,
    GLYPH_CAM_ARROW_UP,
    GLYPH_CAM_ARROW_DOWN
};
#define HUD_POWER_METER_X            0
#define HUD_POWER_METER_EMPHASIZED_Y 166
#define HUD_POWER_METER_Y            200
#define HUD_POWER_METER_HIDDEN_Y     300

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)

#define HUD_TOP_Y 209
#define HUD_BOTTOM_Y 19 // Same height as the Lakitu icon

#define HUD_COINS_X 168
#define HUD_CAMERA_X 54 // This starts counting from the right edge
void set_hud_camera_status(s16 status);
void render_hud(void);

#endif // HUD_H
