#ifndef KEYSTATE_H
#define KEYSTATE_H

#include <3ds/types.h>
#include <3ds/services/hid.h>

typedef struct keystate_s
{
	u32 down;
	u32 held;
	u32 up;
	touchPosition touch;
} keystate_s;

inline void hidKeys(keystate_s* ks)
{
	hidScanInput();
	ks->down = hidKeysDown();
	ks->held = hidKeysHeld();
	ks->up = hidKeysUp();
	hidTouchRead(&ks->touch);
}

inline bool withinRectangle(u16 px, u16 py, s16 x, s16 y, s16 w, s16 h)
{
	return (px >= x && py >= y) && (px < x + w && py < y + h);
}

#endif // KEYSTATE_H
