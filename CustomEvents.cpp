#ifndef CUSTOMEVENTS
#define CUSTOMEVENTS

#include <SDL.h>

Uint32 CE_ColorChange = SDL_RegisterEvents(4);
Uint32 CE_ToolChange = CE_ColorChange + 1;
Uint32 CE_MiscAction = CE_ColorChange + 2;
Uint32 CE_SizeChange = CE_ColorChange + 3;

#endif //CustomEvents