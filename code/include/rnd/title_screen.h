#ifndef _RND_TITLE_SCREEN_H_
#define _RND_TITLE_SCREEN_H_

#include "z3D/z3Dvec.h"
#include "game/actor.h"
#include "game/context.h"

// TODO: Make new struct for EnMag?
typedef struct {
    game::act::Actor actor;
    //SkeletonAnimationModel* logoModel;
    //SkeletonAnimationModel* fireModel;
    //SkeletonAnimationModel* copyrightModel;
    //char unk_1B0[0x30];
} EnMag; //size 0x1E0;

void EnMag_rInit(game::act::Actor* thisx, game::GlobalContext* globalCtx);

#endif //_TITLE_SCREEN_H_