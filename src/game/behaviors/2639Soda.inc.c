

#define o2639SodaLatch OBJECT_FIELD_S32(0x1B)
int ThereIsOneSodaInThisGame = 0;

void bhv_2639Soda_init(void) {
	o->o2639SodaLatch = 0;
    o->oForwardVel = 45;
    o->oMoveAngleYaw = gMarioObject->header.gfx.angle[1];
    o->oFaceAngleYaw = gMarioObject->header.gfx.angle[1];
        // if (o->oBehParams2ndByte == 1) {
        //  o->oVelY = 30.f;
        // }
}
void bhv_2639Soda_loop(void) {
	switch(o->oHeldState) {
        case HELD_FREE:
            break;

        case HELD_HELD:
        	ThereIsOneSodaInThisGame = 1;
            cur_obj_unrender_set_action_and_anim(-1, 0);
            obj_copy_pos(o, gMarioObject);
            break;

        case HELD_THROWN:
        case HELD_DROPPED:
        	ThereIsOneSodaInThisGame = 0;
            cur_obj_get_dropped();
            break;
    }

    if (ThereIsOneSodaInThisGame == 1 && gCurrAreaIndex == 4
    	&& o->o2639SodaLatch == 0
    ) {
    	gMarioState->action = ACT_HOLD_FREEFALL;
    	gMarioState->heldObj = o;
    	o->o2639SodaLatch = 1;
    }

    cur_obj_move_standard(78);

    o->oForwardVel-=5.f;
    // o->oVelY -= 5.f;
    if (o->oForwardVel < 0.f)
        o->oForwardVel = 0;
}
