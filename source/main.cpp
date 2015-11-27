#include <sf2d.h>
#include <stdio.h>

#include "keystate.h"
#include "scene/alchemy_scene.hpp"

int main(int argc, char **argv)
{
	// Start sf2dlib
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0xF5, 0xF2, 0xEF, 0xFF));

	// Initialize console on top screen
	consoleInit(GFX_TOP, NULL);

	printf("Sizeof report:\n");
	printf(" > elementNode: %i\n", sizeof(elementNode_s));
	printf(" > elementList: %i\n", sizeof(elementList_s));

	AlchemyScene scene;
	scene.initialize();

	// consoleClear();

	keystate_s ks;
	while(aptMainLoop())
	{
		hidKeys(&ks);

		// Draw the top screen
		// sf2d_start_frame(GFX_TOP, GFX_LEFT);
		// 	scene.drawTopScreen();
		// sf2d_end_frame();
		
		// Draw the bottom screen
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			scene.drawBottomScreen();
		sf2d_end_frame();

		// Swap the buffers
		sf2d_swapbuffers();

		scene.updateInput(ks);

		// Exit the loop
		if (ks.down & KEY_START) break;
	}
	
	scene.destroy();

	// Stop sf2dlib
	sf2d_fini();

	return 0;
}
