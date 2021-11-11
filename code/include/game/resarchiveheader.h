#ifndef _GAME_RES_ARCHIVE_HEADER_H
#define _GAME_RES_ARCHIVE_HEADER_H

#include "common/types.h"

namespace game {

  struct ResArchiveHeader {
    u32 magic;
    u32 size;
    u16 num_types;
    u16 num_files;
    u32 types_offest;
    u32 info_offset;
    u32 data_offsets_offset;
    char creator[8];
  };
  static_assert(sizeof(ResArchiveHeader) == 0x20);

} // namespace game

#endif