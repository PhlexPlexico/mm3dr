/**
 * @file actor.cpp
 * @author leoetlino (https://github.com/leoetlino/)
 * @brief
 * @date 2021-09-15
 *
 * Brought in from the Project Restoration libraries. Modified for custom messages.
 */
#include "game/message.h"
#include "rnd/custom_messages.h"

#include "common/utils.h"

#if defined ENABLE_DEBUG || defined DEBUG_PRINT
#include "common/debug.h"
extern "C" {
#include <3ds/svc.h>
}
#endif

namespace game {
  MessageResEntry customEntry = {0};

  MessageMgr& MessageMgr::Instance() {
    return rnd::util::GetPointer<MessageMgr&()>(0x1C51D0)();
  }

  bool MessageData::Get(u32 id, Message* msg) const {
    int start = 0;
    int end = res_header->num_msgs - 1;
    bool isCustom = false;
    const auto get_entry = [this](size_t idx) {
      return reinterpret_cast<const MessageResEntry*>((const u8*)res_entries + res_entry_size * idx);
    };

    const MessageResEntry* entry = nullptr;
    if (SetCustomMessage(id, &customEntry)) {
      entry = &customEntry;
      isCustom = true;
    }

    if (!isCustom) {
      start = 0;
      while (!entry && start <= end) {
        const int current_entry_idx = (start + end) / 2;
        const auto* candidate = get_entry(current_entry_idx);
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
      auto& text = msg->texts[i];
      text.reader = rnd::util::GetPointer<MessageReader*(Language)>(0x1C519C)(Language(i));
      if (res_header->languages.IsSet(Language(i))) {
#if defined ENABLE_DEBUG || defined DEBUG_PRINT
// rnd::util::Print("%s: Here's some info for text length: %u\n", __func__,
// entry->texts[res_idx].length);
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
  bool GetMessageFromId(MessageData* self, u32 id, Message* msg) {
    return self->Get(id, msg);
  }
  }

}  // namespace game
