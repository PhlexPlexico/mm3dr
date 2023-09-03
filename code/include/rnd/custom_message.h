#ifndef _RND_CUSTOM_MESSAGE_H_
#define _RND_CUSTOM_MESSAGE_H_

#include "common/utils.h"

#define MAX_MSG_SIZE 512

void CustomMessage_Init(void);

typedef struct {
  char data[MAX_MSG_SIZE];
  u16 size;
} CustomMessage;

/*----- Custom Message Declarations -----*/
extern CustomMessage iceTrapMsg;
extern CustomMessage kokiriSwordMsg;
/*----- Custom Message Declarations -----*/

#endif
