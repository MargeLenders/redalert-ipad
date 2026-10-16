#pragma once

#include <windows.h>

bool MacSDL_SetMode(int width, int height);
bool MacSDL_SetFullscreen(bool enabled);
bool MacSDL_GetFullscreen(void);
void MacSDL_Shutdown(void);
void MacSDL_SetPalette(PALETTEENTRY const *entries, int count);
void MacSDL_Present8(unsigned char const *pixels, int width, int height, int pitch);
void MacSDL_PumpEvents(void);
bool MacSDL_QuitRequested(void);
bool MacSDL_TouchCursorHidden(void);
int MacSDL_ConsumeMobilePointerDrag(int *x, int *y);
void MacSDL_StartTextInput(void);
void MacSDL_StopTextInput(void);
bool MacSDL_IsTextInputActive(void);
void MacSDL_SetTextInputRect(int x, int y, int w, int h);
void MacSDL_SetInGame(bool in_game);
bool MacSDL_IsInGame(void);
