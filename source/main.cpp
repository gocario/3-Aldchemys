#include <sf2d.h>
#include <stdio.h>

#include "keystate.h"
#include "alchemy_scene.hpp"

int main(int argc, char **argv)
{
	// Start sf2dlib
	sf2d_init();

	// Initialize console on top screen
	consoleInit(GFX_TOP, NULL);

	printf("Sizeof report:\n");
	printf(" > elementNode: %i\n", sizeof(elementNode_s));
	printf(" > elementList: %i\n", sizeof(elementList_s));

	el_init();
	el_createNode(Element::DoubleRainbow);
	el_createNode(Element::Horse);

	consoleClear();

	// elementNode_s* node = NULL;
	keystate_s ks;
	while(aptMainLoop())
	{
		hidKeys(&ks);

		// Draw the top screen
		// sf2d_start_frame(GFX_TOP, GFX_LEFT);
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
			el_drawNodes();
		sf2d_end_frame();

		// Swap the buffers
		sf2d_swapbuffers();


		// Exit the loop
		if (ks.down & KEY_START) break;

		if (ks.down & KEY_X)
		{
			el_createNode(Element::Fire);
		}

		{
			if (ks.down & KEY_TOUCH)
			{
				el_selectNode(ks.touch.px, ks.touch.py);
			}
			
			if (ks.held & KEY_TOUCH)
			{
				if (el_isNodeSelected())
				{
					el_moveSelectedNode(ks.touch.px, ks.touch.py);
				}
			}

			if (ks.up & KEY_TOUCH)
			{
				if (el_isNodeSelected())
				{
					el_deselectNode();
				}
			}
		}
	}
	
	el_freeNodes();

	// Stop sf2dlib
	sf2d_fini();

	return 0;
}
