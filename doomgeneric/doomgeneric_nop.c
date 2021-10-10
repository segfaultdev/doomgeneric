#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"

void DG_Init() {
  // DOOMGENERIC_RESX
  // DOOMGENERIC_RESY
}

void DG_DrawFrame() {
  // DG_ScreenBuffer
}

void DG_SleepMs(uint32_t ms) {
  // TODO
}

uint32_t DG_GetTicksMs() {
  return 0;
}

int DG_GetKey(int* pressed, unsigned char* doomKey) {
  // TODO: return 1 someday?
  return 0;
}

void DG_SetWindowTitle(const char *title) {
  // TODO
}
