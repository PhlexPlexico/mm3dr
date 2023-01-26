/*
 * This file is a modified version of a file originally written by RicBent
 * for the program Magikoopa.
 */

#include <3ds/svc.h>
#include "newcodeinfo.h"

Result svcOpenProcess_mine(Handle* process, u32 processId);
Result svcGetProcessId_mine(u32* out, Handle handle);
void svcBreak_mine(UserBreakType breakReason);
Result svcControlProcessMemory_mine(Handle process, u32 addr0, u32 addr1, u32 size, u32 type, u32 perm);

void loader_main(void) __attribute__((section(".loader")));
Handle getCurrentProcessHandle(void) __attribute__((section(".loader")));

void loader_main(void) {
  Result res;

  u32 address = NEWCODE_OFFSET;
  u32 neededMemory = (NEWCODE_SIZE + 0xFFF) & ~0xFFF;  // rounding up

  res = svcControlProcessMemory_mine(getCurrentProcessHandle(), address, address, neededMemory, 6, 7);

  if (res < 0)
    svcBreak_mine(USERBREAK_ASSERT);

  // Hacky solution to be able to edit gDrawItemTable, which is normally in RO data
  res = svcControlProcessMemory_mine(getCurrentProcessHandle(), 0x4D8000, 0x4D8000, 0x1000, MEMOP_PROT,
                                     MEMPERM_READ | MEMPERM_WRITE);

  if (res < 0)
    svcBreak_mine(USERBREAK_ASSERT);
}

Handle getCurrentProcessHandle(void) {
  Handle handle = 0;
  u32 currentPid = 0;
  Result res;

  svcGetProcessId_mine(&currentPid, 0xffff8001);
  res = svcOpenProcess_mine(&handle, currentPid);

  if (res != 0)
    return 0;

  return handle;
}