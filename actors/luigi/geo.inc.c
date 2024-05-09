#include "src/game/envfx_snow.h"

const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1_mat_override_eyes_half_v4_001_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1_mat_override_eyes_closed_v4_001_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1_mat_override_eyes_custom_v4_001_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt4[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1_mat_override_eyes_closed_v4_001_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt5[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1_mat_override_eyes_closed_v4_001_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt6[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1_mat_override_eyes_closed_v4_001_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt7[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1_mat_override_eyes_dead_v4_001_3),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_armature_002_switch_option_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(0, geo_switch_mario_eyes),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_002_switch_option_head__no_cap__mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt1),
			GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt2),
			GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt3),
			GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt4),
			GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt5),
			GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt6),
			GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt1_switch_face_opt7),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_right_hand_open_armature_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, luigi_002_switch_option_right_hand_open_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_left_hand_open_armature_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, luigi_002_switch_option_left_hand_open_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_HELD_OBJECT(0, 0, 0, 0, geo_switch_mario_hand_grab_pos),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_left_hand_peace_armature_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, luigi_004_switch_option_left_hand_peace_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_left_hand_cap_armature_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, luigi_005_switch_option_left_hand_cap_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_left_hand_wing_cap_armature_001[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 60, 0, 0, luigi_006_switch_option_left_hand_wing_cap_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_ALPHA, luigi_006_switch_option_left_hand_wing_cap_wings_mesh_layer_4),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt0_000_switch_001_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_000_displaylist_mesh_layer_1_mat_override_eyes_half_v4_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt0_000_switch_001_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_000_displaylist_mesh_layer_1_mat_override_eyes_closed_v4_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_002_switch_opt0_001_switch_opt0_000_switch_opt0_000_switch_001_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_000_displaylist_mesh_layer_1_mat_override_eyes_dead_v4_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout luigi_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(0, 180, 105),
		GEO_OPEN_NODE(),
			GEO_SCALE(LAYER_FORCE, 24576),
			GEO_OPEN_NODE(),
				GEO_ASM(0, geo_mirror_mario_backface_culling),
				GEO_ASM(0, geo_mirror_mario_set_alpha),
				GEO_SWITCH_CASE(0, geo_switch_mario_stand_run),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_SWITCH_CASE(0, geo_switch_mario_cap_effect),
						GEO_OPEN_NODE(),
							GEO_NODE_START(),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, luigi_000_offset_mesh_layer_1),
									GEO_OPEN_NODE(),
										GEO_ASM(0, geo_move_mario_part_from_parent),
										GEO_ASM(0, geo_mario_tilt_torso),
										GEO_ROTATION_NODE(LAYER_FORCE, 0, 0, 0),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 46, 0, 0, luigi_000_offset_001_mesh_layer_1),
											GEO_OPEN_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 88, 0, 0, NULL),
												GEO_OPEN_NODE(),
													GEO_ASM(0, geo_mario_head_rotation),
													GEO_ROTATION_NODE(LAYER_FORCE, 0, 0, 0),
													GEO_OPEN_NODE(),
														GEO_SWITCH_CASE(0, geo_switch_mario_cap_on_off),
														GEO_OPEN_NODE(),
															GEO_NODE_START(),
															GEO_OPEN_NODE(),
																GEO_SWITCH_CASE(0, geo_switch_mario_eyes),
																GEO_OPEN_NODE(),
																	GEO_NODE_START(),
																	GEO_OPEN_NODE(),
																		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_000_displaylist_mesh_layer_1),
																	GEO_CLOSE_NODE(),
																	GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt0_000_switch_001_opt1),
																	GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt0_000_switch_001_opt2),
																	GEO_BRANCH(1, luigi_002_switch_opt0_001_switch_opt0_000_switch_opt0_000_switch_001_opt3),
																GEO_CLOSE_NODE(),
															GEO_CLOSE_NODE(),
															GEO_BRANCH(1, luigi_armature_002_switch_option_001),
														GEO_CLOSE_NODE(),
														GEO_TRANSLATE_ROTATE(LAYER_FORCE, 143, -51, -127, 15, -33, -133),
														GEO_OPEN_NODE(),
															GEO_ASM(0, geo_mario_rotate_wing_cap_wings),
															GEO_ROTATION_NODE(LAYER_FORCE, 0, 0, 0),
															GEO_OPEN_NODE(),
																GEO_DISPLAY_LIST(LAYER_TRANSPARENT, luigi_000_displaylist_001_mesh_layer_5),
															GEO_CLOSE_NODE(),
														GEO_CLOSE_NODE(),
														GEO_TRANSLATE_ROTATE(LAYER_FORCE, 143, -51, 127, -15, 33, -133),
														GEO_OPEN_NODE(),
															GEO_ASM(1, geo_mario_rotate_wing_cap_wings),
															GEO_ROTATION_NODE(LAYER_FORCE, 0, 0, 0),
															GEO_OPEN_NODE(),
																GEO_DISPLAY_LIST(LAYER_TRANSPARENT, luigi_000_displaylist_002_mesh_layer_5),
															GEO_CLOSE_NODE(),
														GEO_CLOSE_NODE(),
													GEO_CLOSE_NODE(),
												GEO_CLOSE_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 67, -6, 46, NULL),
												GEO_OPEN_NODE(),
													GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, luigi_000_offset_003_mesh_layer_1),
													GEO_OPEN_NODE(),
														GEO_ANIMATED_PART(LAYER_OPAQUE, 72, 0, 0, luigi_000_offset_004_mesh_layer_1),
														GEO_OPEN_NODE(),
															GEO_SWITCH_CASE(1, geo_switch_mario_hand),
															GEO_OPEN_NODE(),
																GEO_NODE_START(),
																GEO_OPEN_NODE(),
																	GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, NULL),
																	GEO_OPEN_NODE(),
																		GEO_ASM(1, geo_mario_hand_foot_scaler),
																		GEO_SCALE(LAYER_FORCE, 65536),
																		GEO_OPEN_NODE(),
																			GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_000_displaylist_003_mesh_layer_1),
																		GEO_CLOSE_NODE(),
																	GEO_CLOSE_NODE(),
																GEO_CLOSE_NODE(),
																GEO_BRANCH(1, luigi_right_hand_open_armature_001),
															GEO_CLOSE_NODE(),
														GEO_CLOSE_NODE(),
													GEO_CLOSE_NODE(),
												GEO_CLOSE_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 68, -6, -46, NULL),
												GEO_OPEN_NODE(),
													GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, luigi_000_offset_006_mesh_layer_1),
													GEO_OPEN_NODE(),
														GEO_ANIMATED_PART(LAYER_OPAQUE, 72, 0, 0, luigi_000_offset_007_mesh_layer_1),
														GEO_OPEN_NODE(),
															GEO_SWITCH_CASE(0, geo_switch_mario_hand),
															GEO_OPEN_NODE(),
																GEO_NODE_START(),
																GEO_OPEN_NODE(),
																	GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, NULL),
																	GEO_OPEN_NODE(),
																		GEO_ASM(0, geo_mario_hand_foot_scaler),
																		GEO_SCALE(LAYER_FORCE, 65536),
																		GEO_OPEN_NODE(),
																			GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_000_displaylist_004_mesh_layer_1),
																		GEO_CLOSE_NODE(),
																		GEO_HELD_OBJECT(0, 0, 0, 0, geo_switch_mario_hand_grab_pos),
																	GEO_CLOSE_NODE(),
																GEO_CLOSE_NODE(),
																GEO_BRANCH(1, luigi_left_hand_open_armature_001),
																GEO_BRANCH(1, luigi_left_hand_peace_armature_001),
																GEO_BRANCH(1, luigi_left_hand_cap_armature_001),
																GEO_BRANCH(1, luigi_left_hand_wing_cap_armature_001),
															GEO_CLOSE_NODE(),
														GEO_CLOSE_NODE(),
													GEO_CLOSE_NODE(),
												GEO_CLOSE_NODE(),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, -3, -5, 30, NULL),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, luigi_000_offset_009_mesh_layer_1),
											GEO_OPEN_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 90, 0, 0, luigi_000_offset_010_mesh_layer_1),
												GEO_OPEN_NODE(),
													GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, luigi_000_offset_011_mesh_layer_1),
												GEO_CLOSE_NODE(),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
										GEO_ANIMATED_PART(LAYER_OPAQUE, -3, -5, -30, NULL),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, luigi_000_offset_012_mesh_layer_1),
											GEO_OPEN_NODE(),
												GEO_ANIMATED_PART(LAYER_OPAQUE, 90, 0, 0, luigi_000_offset_013_mesh_layer_1),
												GEO_OPEN_NODE(),
													GEO_ANIMATED_PART(LAYER_OPAQUE, 67, 0, 0, NULL),
													GEO_OPEN_NODE(),
														GEO_ASM(2, geo_mario_hand_foot_scaler),
														GEO_SCALE(LAYER_FORCE, 65536),
														GEO_OPEN_NODE(),
															GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_000_displaylist_005_mesh_layer_1),
														GEO_CLOSE_NODE(),
													GEO_CLOSE_NODE(),
												GEO_CLOSE_NODE(),
											GEO_CLOSE_NODE(),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_ASM(1, geo_mirror_mario_backface_culling),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, luigi_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, luigi_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, luigi_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
