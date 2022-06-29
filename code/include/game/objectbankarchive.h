#ifndef _GAME_OBJECT_BANK_ARCHIVE_H
#define _GAME_OBJECT_BANK_ARCHIVE_H

#include "common/types.h"
#include "common/utils.h"
#include "game/resarchiveheader.h"

namespace game::ObjectBank {
  struct Archive {
    u8* raw;
    ResArchiveHeader* header;
    ResArchiveFileType* types;
    ResArchiveFileInfo* info;
    u32* data_offsets;
  };
  static_assert(sizeof(Archive) == 0x14);

  struct Csab {
    u32 field_0;
    u32 field_4;
    u8 field_8;
  };  // size == 0x09?
  static_assert(sizeof(Csab) == 0x0C);

  struct Cmab {
    void* vtable;
    int field_4;
    u8 field_8;
    u8 gap_9[3];
    u32 field_C;
    u32 field_10;
    u32 field_14;
    u32 field_18;
  };  // size == 0x09?
  static_assert(sizeof(Cmab) == 0x1C);

  struct ObjectBankArchive {
    u32 field_0;
    Archive archive;
    u32 archive_data;
    u32 file_type_indices[16];
    u8 field_5C;
    u8 gap_5D;
    u16 actor_id;
    void*** cmb_files;
    Csab*** csab_files;
    void*** ctxb_files;
    void*** ptxb_files;
    Cmab*** cmab_files;
    void*** zsi_files;
    void*** qdb_files;
    void*** faceb_files;
    void*** tbd_files;
    void*** ccb_files;
    void*** linkb_files;
    void*** colb_files;
    void*** gfb_files;
    void*** vwx_files;
    void*** other_files;
  };
  static_assert(sizeof(ObjectBankArchive) == 0x9C);

  void init(ObjectBankArchive*, u32, ResArchiveHeader*, int, char);
  void* getCmbFile(ObjectBankArchive*, u32, u32);
  void free(ObjectBankArchive*);
}  // namespace game::ObjectBank

#endif