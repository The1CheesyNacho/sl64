
/**
 * This is the behavior file for the tilting inverted pyramids in BitFS/LLL.
 * The object essentially just tilts and moves Mario with it.
 */

/**
 * Initialize the object's transform matrix with Y being up.
 */
void bhv_platform_normals_init(void) {
    vec3f_set(&o->oTiltingPyramidNormalX, 0.0f, 1.0f, 0.0f);
    mtxf_align_terrain_normal(o->transform, &o->oTiltingPyramidNormalX, &o->oPosX, 0);
}

/**
 * Main behavior for the tilting pyramids in LLL/BitFS. These platforms calculate rough normals from Mario's position,
 * then gradually tilt back moving Mario with them.
 */
void bhv_tilting_inverted_pyramid_loop(void) {
#if !PLATFORM_DISPLACEMENT_2
    Vec3f posBeforeRotation, posAfterRotation;
    Vec3f marioPos, dist;
#endif
    Vec3f targetNormal;
    Mat4 *transform = &o->transform;
    s32 marioOnPlatform = (gMarioObject->platform == o);

    if (marioOnPlatform) {
#if !PLATFORM_DISPLACEMENT_2
        // Target the normal in Mario's direction
        vec3_diff(dist, gMarioState->pos, &o->oPosX);

        // Get Mario's position before the rotation
        vec3f_copy(marioPos, gMarioState->pos);

        linear_mtxf_mul_vec3f(*transform, posBeforeRotation, dist);
        targetNormal[0] = dist[0];
        targetNormal[2] = dist[2];
#else // PLATFORM_DISPLACEMENT_2
        targetNormal[0] = gMarioState->pos[0] - o->oPosX;
        targetNormal[2] = gMarioState->pos[2] - o->oPosZ;
#endif
        targetNormal[1] = 500.0f;
        vec3f_normalize(targetNormal);
    } else {
        // Target normal is directly upwards when Mario is not on the platform.
        vec3f_set(targetNormal, 0.0f, 1.0f, 0.0f);
    }

    // Approach the normals by 0.01f towards the new goal, then create a transform matrix and orient the object. 
    // Outside of the other conditionals since it needs to tilt regardless of whether Mario is on.
    approach_f32_symmetric_bool(&o->oTiltingPyramidNormalX, targetNormal[0], 0.01f);
    approach_f32_symmetric_bool(&o->oTiltingPyramidNormalY, targetNormal[1], 0.01f);
    approach_f32_symmetric_bool(&o->oTiltingPyramidNormalZ, targetNormal[2], 0.01f);
    vec3f_normalize(&o->oTiltingPyramidNormalX);
    mtxf_align_terrain_normal(*transform, &o->oTiltingPyramidNormalX, &o->oPosX, 0x0);

#if !PLATFORM_DISPLACEMENT_2
    // If Mario is on the platform, adjust his position for the platform tilt.
    if (marioOnPlatform) {
        linear_mtxf_mul_vec3f(*transform, posAfterRotation, dist);
        marioPos[0] += posAfterRotation[0] - posBeforeRotation[0];
        marioPos[1] += posAfterRotation[1] - posBeforeRotation[1];
        marioPos[2] += posAfterRotation[2] - posBeforeRotation[2];
        vec3f_copy(gMarioState->pos, marioPos);
    }
#endif

    o->header.gfx.throwMatrix = transform;
}
