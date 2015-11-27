#include <sf2d.h>
#include <stdio.h>

#include "keystate.h"
#include "alchemy_scene.hpp"

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

	el_initialize();

	consoleClear();

	// elementNode_s* node = NULL;
	keystate_s ks;
	while(aptMainLoop())
	{
		hidKeys(&ks);

		// Draw the top screen
		// sf2d_start_frame(GFX_TOP, GFX_LEFT);
		// el_drawTopScreen();
		// sf2d_end_frame();
		
		// printf("\x1B[0;0HElement List: %p\n", &elementList);
		// 	printf("     %-2u          <%9p %9p>\n", elementList.count, elementList.first, elementList.last);
		// printf("\n");
		// node = elementList.last;
		// for (u16 i = 0; i < elementList.count && node; i++)
		// {
		// 	printf("   > %9p: <%9p %9p>\n", node, node->next, node->prev);
		// 	node = node->prev;
		// }

		// printf("\x1B[0;0HSelected Node: %10p\n", selectedNode);


		// Draw the bottom screen
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			el_drawBottomScreen();
		sf2d_end_frame();

		// Swap the buffers
		sf2d_swapbuffers();

		el_updateInput(ks);

		// Exit the loop
		if (ks.down & KEY_START) break;
	}
	
	el_destroy();

	// Stop sf2dlib
	sf2d_fini();

	return 0;
}
