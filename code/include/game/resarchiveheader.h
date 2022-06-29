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

  struct ResArchiveFileType {
    u32 numFiles;
    u32 file_indices_offset;
    u32 name_offset;
    u32 field_C;
  };
  static_assert(sizeof(ResArchiveFileType) == 0x10);

  struct ResArchiveFileInfo {
    u32 size;
    u32 file_stem_offset;
    u32 name_offset;
  };
  static_assert(sizeof(ResArchiveFileInfo) == 0x0C);

}  // namespace game

#endif