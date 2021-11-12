#include "game/objectbankarchive.h"

namespace game::ObjectBank {
  //set_field_5c always = 0 in code calls.
  void init(ObjectBankArchive* obj_bank_archive, u32 actor_id, ResArchiveHeader* data, int size, char set_field_5c) {
    return rnd::util::GetPointer<void(ObjectBankArchive*, u32, ResArchiveHeader*, int, char)>(0x1F57DC)(obj_bank_archive, actor_id, data, size, set_field_5c);
  }
  void* getCmbFile(ObjectBankArchive* obj_bank_archive, u32 cmb_file_index, u32 archive_type) {
    return rnd::util::GetPointer<void*(ObjectBankArchive*, u32, u32)>(0x1F5C00)(obj_bank_archive, cmb_file_index, archive_type);
  }
  void free(ObjectBankArchive* obj_bank_archive) {
    return rnd::util::GetPointer<void(ObjectBankArchive*)>(0x1E477C)(obj_bank_archive);
  }
}