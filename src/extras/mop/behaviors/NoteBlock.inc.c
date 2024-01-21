void bhv_noteblock_loop(void) {
	f32 Yspd = 64.0f;
	u32 CarmackMeme;
	if (cur_obj_is_mario_on_platform()) {
		//this is awful
		if (gMarioState->controller->buttonPressed & A_BUTTON) {
			Yspd = 200;
		}
		set_mario_action(gMarioState, ACT_DOUBLE_JUMP, 0);
		CarmackMeme = *(u32 *) &Yspd;
		CarmackMeme += (o->oBhvParams2ndByte << 16);
		Yspd = *(f32 *) &CarmackMeme;
		gMarioState->vel[1] = Yspd;
		o->oAction = 1;
		gMarioState->flags |= MARIO_NO_FALL_DAMAGE;
	}
	if (o->oAction == 1) {
		if (o->oTimer == 4) {
			o->oAction = 0;
			o->oPosY = o->oHomeY;
		} else {
			if (o->oTimer > 2) {
				o->oPosY = o->oHomeY + (f32)(o->oTimer % 3) * 6;
			} else {
				o->oPosY = o->oHomeY - (f32)(o->oTimer) * 6;
			}
		}
	}
}
