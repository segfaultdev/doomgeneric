#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"

#include <arch/i586.h>
#include <nop/send.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int vide = 0;
int keyb = 0;

#define NOP_NONE      0
#define NOP_F1        256
#define NOP_F2        257
#define NOP_F3        258
#define NOP_F4        259
#define NOP_F5        260
#define NOP_F6        261
#define NOP_F7        262
#define NOP_F8        263
#define NOP_F9        264
#define NOP_F10       265
#define NOP_F11       266
#define NOP_F12       267
#define NOP_L_ALT     268
#define NOP_L_SHIFT   269
#define NOP_L_CTRL    270
#define NOP_R_ALT     271
#define NOP_R_SHIFT   272
#define NOP_R_CTRL    273
#define NOP_CAPSLOCK  274
#define NOP_NUMLOCK   275
#define NOP_SCRLOCK   276
#define NOP_ESCAPE    277
#define NOP_BACKSPACE '\b'
#define NOP_ENTER     '\n'
#define NOP_TAB       '\t'

uint8_t prev_state[256] = {0};

uint8_t get_key(uint16_t key) {
  switch (key) {
    case NOP_ENTER:
      return KEY_ENTER;
    case NOP_ESCAPE:
      return KEY_ESCAPE;
    case 'a':
      return KEY_LEFTARROW;
    case 'd':
      return KEY_RIGHTARROW;
    case 'w':
      return KEY_UPARROW;
    case 's':
      return KEY_DOWNARROW;
    case NOP_L_CTRL:
    case NOP_R_CTRL:
      return KEY_FIRE;
    case ' ':
      return KEY_USE;
    case NOP_L_SHIFT:
    case NOP_R_SHIFT:
      return KEY_RSHIFT;
  }
  
  return (uint8_t)(key);
}

void DG_Init() {
  printf("nop: initializing screen...\n");

  int term = nop_find("TERM");
  
  if (term) {
    nop_send(0, "PAUS", term, 1, 0);
  }
  
  vide = nop_find("VIDE");
  keyb = nop_find("KEYB");
}

void DG_DrawFrame() {
  nop_send(vide, "BITM", 0, DOOMGENERIC_RESX + (DOOMGENERIC_RESY << 16), (uint32_t)(DG_ScreenBuffer));
}

void DG_SleepMs(uint32_t ms) {
  int curr_ms = mtime(NULL);
  
  while (DG_GetTicksMs() - curr_ms < (int)(ms)) {
    i586_wait();
  }
}

uint32_t DG_GetTicksMs() {
  return mtime(NULL);
}

int DG_GetKey(int* pressed, unsigned char* doomKey) {
  for (int i = 0; i < 384; i++) {
    int is_used = (i >= 32 && i < 127) ||
                  (i == NOP_ENTER) ||
                  (i > NOP_F12);
    
    if (is_used) {
      int state = nop_send(keyb, "REQU", i, 0, 0);
      
      if (state != prev_state[get_key(i)]) {
        *pressed = state;
        *doomKey = get_key(i);
        
        prev_state[get_key(i)] = state;
        return 1;
      }
    }
  }
  
  return 0;
}

void DG_SetWindowTitle(const char *title) {
  i586_wait();
}
