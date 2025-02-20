// sparkle_spawn_star.inc.c

struct ObjectHitbox sSparkleSpawnStarHitbox = {
    /* interactType:      */ INTERACT_STAR_OR_KEY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_spawned_star_init(void) {
    if (!(o->oInteractionSubtype & INT_SUBTYPE_NO_EXIT)) {
        o->oBehParams = o->parentObj->oBehParams;
    }
    s32 param = GET_BPARAM1(o->oBehParams);
    if ((1 << param) & save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(gCurrCourseNum))) {
        cur_obj_set_model(MODEL_TRANSPARENT_STAR);
    }

    cur_obj_play_sound_2(SOUND_GENERAL2_STAR_APPEARS);
}

void set_sparkle_spawn_star_hitbox(void) {
    obj_set_hitbox(o, &sSparkleSpawnStarHitbox);
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        obj_mark_for_deletion(o);
        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void set_home_to_mario(void) {
    vec3f_copy_y_off(&o->oHomeVec, &gMarioObject->oPosVec, 250.0f);

    o->oPosY = o->oHomeY;

    f32 lateralDist;
    vec3f_get_lateral_dist(&o->oPosVec, &o->oHomeVec, &lateralDist);

    o->oForwardVel = lateralDist / 23.0f;
}

void set_y_home_to_pos(void) {
    o->oForwardVel = 0.0f;
    o->oHomeY = o->oPosY;
}

void slow_star_rotation(void) {
    if (o->oAngleVelYaw > 0x400) {
        o->oAngleVelYaw -= 0x40;
    }
}

void bhv_spawned_star_loop(void) {
    if (o->oAction == SPAWN_STAR_POS_CUTSCENE_ACT_START) {
        if (o->oTimer == 0) {
            cutscene_object(CUTSCENE_STAR_SPAWN, o);
            set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
            o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            o->oAngleVelYaw = 0x800;
            if (o->oBehParams2ndByte == SPAWN_STAR_POS_CUTSCENE_BP_SPAWN_AT_MARIO) {
                set_home_to_mario();
            } else {
                set_y_home_to_pos();
            }
            o->oMoveAngleYaw = cur_obj_angle_to_home();
            o->oVelY = 50.0f;
            o->oGravity = -4.0f;
            spawn_mist_particles();
        }
        cur_obj_play_sound_1(SOUND_ENV_STAR);
        spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
        if (o->oVelY < 0 && o->oPosY < o->oHomeY) {
            o->oAction++; // SPAWN_STAR_POS_CUTSCENE_ACT_BOUNCE
            o->oForwardVel = 0;
            o->oVelY = 20.0f;
            o->oGravity = -1.0f;
            if (!in2639Level()) {
                play_power_star_jingle();
            }
        }
    } else if (o->oAction == SPAWN_STAR_POS_CUTSCENE_ACT_BOUNCE) {
        if (o->oVelY < -4.0f) {
            o->oVelY = -4.0f;
        }
        if (o->oVelY < 0 && o->oPosY < o->oHomeY) {
            gObjCutsceneDone = TRUE;
            o->oVelY = 0;
            o->oGravity = 0;
            o->oAction++; // SPAWN_STAR_POS_CUTSCENE_ACT_END
        }
        spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
    } else if (o->oAction == SPAWN_STAR_POS_CUTSCENE_ACT_END) {
        if (gCamera->cutscene == 0 && gRecentCutscene == 0) {
            clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
            o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            o->oAction++; // SPAWN_STAR_POS_CUTSCENE_ACT_SLOW_STAR_ROTATION
        }
    } else { // SPAWN_STAR_POS_CUTSCENE_ACT_SLOW_STAR_ROTATION
        set_sparkle_spawn_star_hitbox();
        slow_star_rotation();
    }

    cur_obj_move_using_fvel_and_gravity();
    o->oFaceAngleYaw += o->oAngleVelYaw;
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_spawn_star_no_level_exit(u32 params) {
    struct Object *starObj = spawn_object(o, MODEL_STAR, bhvSpawnedStarNoLevelExit);
    SET_BPARAM1(starObj->oBehParams, params);
    starObj->oInteractionSubtype = INT_SUBTYPE_NO_EXIT;
    obj_set_angle(starObj, 0x0, 0x0, 0x0);
}


/**
 * Construct the 'to' point which is distance 'dist' away from the 'from' position,
 * and has the angles pitch and yaw.
 */
// #define vec3_set_dist_and_angle(from, to, dist, pitch, yaw) { \
//     register f32 dcos = (dist * coss(pitch)); \
//     to[0] = (from[0] + (dcos * sins(yaw  ))); \
//     to[1] = (from[1] + (dist * sins(pitch))); \
//     to[2] = (from[2] + (dcos * coss(yaw  ))); \
// }
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, Angle32 pitch, Angle32 yaw);
//     vec3_set_dist_and_angle(from, to, dist, pitch, yaw);
// }

void bhv_spawn_star_get_outta_here(u32 params) {
    Vec3f newPos;
    vec3f_set_dist_and_angle(&gCurrentObject->oPosX, newPos, 200.0f, 200.0f, gCurrentObject->oMoveAngleYaw);
    struct Object *starObj = NULL;
    starObj = spawn_star(starObj, newPos[0], newPos[1] + 100, newPos[2]);
    starObj->oBehParams = params << 24;
    starObj->parentObj = gCurrentObject;

    // if (params == 6) {
    //     vec3f_copy(&starObj->oPosX, gMarioState->pos);
    // } else {
    // }

    // starObj->oInteractionSubtype = INT_SUBTYPE_NO_EXIT;
    obj_set_angle(starObj, 0, 0, 0);
}
