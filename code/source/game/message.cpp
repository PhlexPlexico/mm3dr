#include "game/message.h"

#include "common/utils.h"

#ifdef ENABLE_DEBUG
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace game {
  #ifdef ENABLE_DEBUG
  static bool declareTestMessage = false;
  static MessageResEntry ptrCustomMessageEntries[1] = {0};
  volatile const u32 numCustomMessageEntries = 1;
  #else
  volatile const MessageResEntry *ptrCustomMessageEntries = {0};
  volatile const u32 numCustomMessageEntries = {0};
  #endif
  MessageResEntry customIceMessage = {0};
  MessageResEntry customSwordMessage = {0};

  MessageMgr &MessageMgr::Instance() {
    return rnd::util::GetPointer<MessageMgr &()>(0x1C51D0)();
  }

  bool MessageData::Get(u32 id, Message *msg) const {
    #ifdef ENABLE_DEBUG
    if(!declareTestMessage) {
      ptrCustomMessageEntries[0].id = 0x6133;
      ptrCustomMessageEntries[0].field_2 = 0xFFFF;
      ptrCustomMessageEntries[0].field_4 = 0x3FFFFFFF;
      ptrCustomMessageEntries[0].flags = 0xFF0000;
      ptrCustomMessageEntries[0].texts[0].offset = "Hmmph...  I've been made a \x7f:\x00\x01\x00\x46OOL\x7f\x00:\x00\x0b\x00 of!\x7f\x00\x31";
      ptrCustomMessageEntries[0].texts[0].length = 55;
      declareTestMessage = true;
    }
    #endif
    int start = 0;
    int end = res_header->num_msgs - 1;
    int customEnd = numCustomMessageEntries - 1;
    bool isCustom = false;
    const auto get_entry = [this](size_t idx) {
      return reinterpret_cast<const MessageResEntry *>((const u8 *)res_entries + res_entry_size * idx);
    };
    const auto get_custom_entry = [this](size_t idx) {
      return reinterpret_cast<const MessageResEntry *>((const u8 *)ptrCustomMessageEntries + idx);
    };
    
    const MessageResEntry *entry = nullptr;
    
    if (id == 0x0012) {
      customIceMessage.id = 0x0012;
      customIceMessage.field_2 = 0xFFFF;
      customIceMessage.field_4 = 0x3FFFFFFF;
      customIceMessage.flags = 0xFF0000;
      //customIceMessage.texts[0].offset = "Hmmph...  I've been made a \x7f:\x00\x01\x00\x46OOL\x7f\x00:\x00\x0b\x00 of!\x7f\x00\x31";
      customIceMessage.texts[0].offset = " \x7f:\x00\x01\x00\x46OOL!\x7f:\x00\x0b\x00\x7f\x00\x31";
      customIceMessage.texts[0].length = 22;
      entry = &customIceMessage;
      isCustom = true;
    } else if (id == 0x0037) {
      customSwordMessage.id = 0x0037;
      customSwordMessage.field_2 = 0xFFFF;
      customSwordMessage.field_4 = 0x3FFFFFF;
      customSwordMessage.flags = 0x4D0000;
      customSwordMessage.texts[0].offset = "\x7f\x00'\x00You got the \x7f\x00:\x00\x01\x00Kokiri sword!\x7f:\x00\x00\x00\x7f\x00\x31\x00";
      customSwordMessage.texts[0].length = 48;
      entry = &customSwordMessage;
      isCustom = true;
    }
    while (!entry && start <= customEnd) {
      const int current_entry_idx = (start + customEnd) / 2;
      const auto *candidate = get_custom_entry(current_entry_idx);
      if (candidate->id < id)
        start = current_entry_idx + 1;
      else if (candidate->id > id)
        customEnd = current_entry_idx - 1;
      else {
        entry = candidate;
        isCustom = true;
      }
        
    }

    if (!entry) {
      start = 0;
      while (!entry && start <= end) {
        const int current_entry_idx = (start + end) / 2;
        const auto *candidate = get_entry(current_entry_idx);
        if (candidate->id < id)
          start = current_entry_idx + 1;
        else if (candidate->id > id)
          end = current_entry_idx - 1;
        else
          entry = candidate;
      }
    }
    if (!entry || !msg)
      return false;


    msg->msgid = entry->id;
    msg->is_flag1 = entry->flags & 1;
    msg->is_flag1000 = entry->flags & 0x1000;
    msg->is_flag2000 = entry->flags & 0x2000;
    msg->flag10 = u32(u8(entry->flags)) << 0x18 >> 0x1C;
    msg->flag100 = u32(u16(entry->flags)) << 0x16 >> 0x1E;
    msg->field_10 = entry->field_2;
    auto x14 = entry->flags << 8 >> 0x18;
    msg->field_14 = x14 == 0xFF ? -1 : x14;
    auto x18 = entry->field_4 & 0x3FF;
    msg->field_18 = x18 == 0x3FF ? -1 : x18;
    auto x1C = u32(entry->field_4 << 0xC) >> 0x16;
    msg->field_1C = x1C == 0x3FF ? -1 : x1C;
    auto x20 = u32(entry->field_4 >> 0x14) & 0xFFFFF3FF;
    msg->field_20 = x20 == 0x3FF ? -1 : x20;

    for (size_t i = 0, res_idx = 0; i < NumLanguages; ++i) {
      auto &text = msg->texts[i];
      text.reader = rnd::util::GetPointer<MessageReader *(Language)>(0x1C519C)(Language(i));
      if (res_header->languages.IsSet(Language(i))) {
        #ifdef ENABLE_DEBUG
        //rnd::util::Print("%s: Here's some info for text length: %u\n", __func__, entry->texts[res_idx].length);
        #endif
        text.ptr = isCustom ? (u8*)entry->texts[res_idx].offset : (u8*)res_header + (u32)entry->texts[res_idx].offset;
        text.size = entry->texts[res_idx].length;
        ++res_idx;
      } else {
        text.ptr = nullptr;
        text.size = 0;
      }
    }
    

    return true;
  }

  void PlayMessagePassSound() {
    rnd::util::GetPointer<void()>(0x1AF034)();
  }

  void PlayMessageCancelSound() {
    rnd::util::GetPointer<void()>(0x1AE498)();
  }

  extern "C" {
  bool GetMessageFromId(MessageData *self, u32 id, Message *msg) {
    return self->Get(id, msg);
  }
  }

} // namespace game
