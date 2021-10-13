#include "rnd/custom_models.h"
#include "z3D/z3Dvec.h"
//#include "rnd/objects.h"
#include "rnd/title_screen.h"

namespace rnd {
#define EnMag_Init_addr 0x32433C
#define EnMag_Init ((ActorFunc)EnMag_Init_addr)

  // TODO: Init hooks for title screen.
  void EnMag_rInit(EnMag* self, game::GlobalContext* globalCtx) {
    // void* cmbPtr = rnd::util::GetPointer<void*(u32)>(0x1F28AC)(3);
    // self->model->spawn(cmbPtr);
    return;
    // EnMag *enmag = (EnMag *)thisx;

    // s8 objBankIdx = enmag->actor.objBankIndex;
    // void *titleScreenZAR = globalCtx->objectCtx.status[objBankIdx].zarInfo.buf;
    // void *cmabMan;

    // s16 exObjectBankIdx = Object_GetIndex(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    // if (exObjectBankIdx < 0) {
    //   exObjectBankIdx = Object_Spawn(&rExtendedObjectCtx, OBJECT_CUSTOM_GENERAL_ASSETS);
    // }

    // CustomModel_EditTitleScreenLogo(titleScreenZAR);

    // EnMag_Init(thisx, globalCtx);

    // cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, TEXANIM_TITLE_LOGO_US);
    // TexAnim_Spawn(enmag->logoModel->unk_0C, cmabMan);
    // enmag->logoModel->unk_0C->animSpeed = 0.0f;
    // enmag->logoModel->unk_0C->animMode = 0;

    // cmabMan = ZAR_GetCMABByIndex(&rExtendedObjectCtx.status[exObjectBankIdx].zarInfo, TEXANIM_COPY_NINTENDO);
    // TexAnim_Spawn(enmag->copyrightModel->unk_0C, cmabMan);
    // enmag->copyrightModel->unk_0C->animSpeed = 0.0f;
    // enmag->copyrightModel->unk_0C->animMode = 0;
  }
}
