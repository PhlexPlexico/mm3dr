#ifndef _RND_RHEAP_H_
#define _RND_RHEAP_H_

#include "z3d/z3DVec.h"

namespace rnd {
  void rHeap_Init(void);
  void* rHeap_Alloc(u32 bytes);
} // namespace rnd

#endif //_RND_RHEAP_H_