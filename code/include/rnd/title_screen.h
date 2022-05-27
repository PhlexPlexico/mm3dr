#ifndef _RND_TITLE_SCREEN_H_
#define _RND_TITLE_SCREEN_H_

#include "z3d/z3DVec.h"
#include "game/actor.h"
#include "game/context.h"

// TODO: Make new struct for EnMag?
struct SkeletonAnimationModel { 
    void spawn(void* cmbPtr);
};

struct EnMag {
    game::act::Actor actor;
    //SkeletonAnimationModel* model;
    //SkeletonAnimationModel* fireModel;
    //SkeletonAnimationModel* copyrightModel;
    //char unk_1B0[0x30];
}; //size 0x1E0;

void EnMag_rInit(game::act::Actor* thisx, game::GlobalContext* globalCtx);

#endif //_TITLE_SCREEN_H_