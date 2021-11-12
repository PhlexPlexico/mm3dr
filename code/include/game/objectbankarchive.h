#ifndef _GAME_OBJECT_BANK_ARCHIVE_H
#define _GAME_OBJECT_BANK_ARCHIVE_H

#include "common/types.h"
namespace game {
  struct Archive {
    void *raw;
    void *header;
    void *types;
    void *info;
    void *data_offsets;
  };
  static_assert(sizeof(Archive) == 0x14);

  struct ObjectBankArchive {
    u32 field_0;
    Archive archive;
    u32 archive_data;
    u32 file_type_indices[16];
    u8 field_5C;
    u8 gap_5D;
    u16 field_5E;
    void *cmb_files;
    void *csab_files;
    void *ctxb_files;
    void *ptxb_files;
    void *cmab_files;
    void *zsi_files;
    void *qdb_files;
    void *faceb_files;
    void *tbd_files;
    void *ccb_files;
    void *linkb_files;
    void *colb_files;
    void *gfb_files;
    void *vwx_files;
    void *other_files;
  };
  static_assert(sizeof(ObjectBankArchive) == 0x9C);
} // namespace game

#endif