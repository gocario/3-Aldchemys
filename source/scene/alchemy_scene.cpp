#include "alchemy_scene.hpp"
#include "data/images.hpp"

#include <stdio.h>
#include <string.h>

elementList_s elementList;
elementNode_s* selectedNode = NULL;

u16 discoveredElementCount = 0;
bool discoveredElements[Element::Count-1];
element_t elementDiscoveries[Element::Count-2];

sf2d_texture* workBackground = NULL;
sf2d_texture* elemTiles = NULL;


// ------------------------------------
elementNode_s* el_createNode(element_t elem)
// ------------------------------------
{
	elementNode_s* node = new elementNode_s;
	node->elem = elem;
	node->x = 0;
	node->y = 0;
	node->next = NULL;
	node->prev = NULL;
	el_addNode(node);
#ifdef DEBUG_PRINT
	printf("%s created\n", elementNames[node->elem]);
#endif
	return node;
}


// ------------------------------------
bool el_isNodeSelected()
// ------------------------------------
{
	return selectedNode;
}


// ------------------------------------
void el_deselectNode()
// ------------------------------------
{
	elementNode_s* node;

	u16 x = selectedNode->x + ELEMENT_SIZE / 2;
	u16 y = selectedNode->y + ELEMENT_SIZE / 2;

#ifdef DEBUG_PRINT
	printf("Searching for: {%3u,%3u}-\n", x, y);
#endif
	node = selectedNode->next;
	while (node)
	{
		if (el_isNodeTouched(node, x, y))
		{
#ifdef DEBUG_PRINT
			printf("%s selected\n", elementNames[node->elem]);
#endif
			element_t elem = blendResult(selectedNode->elem, node->elem);
			if (elem != Element::None)
			{
				x = node->x;
				y = node->y;
				el_freeNode(node);
				el_freeNode(selectedNode);

				el_discoverElement(elem);
				node = el_createNode(elem);
				node->x = x;
				node->y = y;

				node = NULL;
				selectedNode = NULL;
			}

			break;
		}
		node = node->next;
	}
#ifdef DEBUG_PRINT
	if (node)
		printf("No node found\n");
#endif

	selectedNode = NULL;
}


// ------------------------------------
void el_selectNode(u16 x, u16 y)
// ------------------------------------
{
	elementNode_s* node;

#ifdef DEBUG_PRINT
	printf("Searching for: {%3u,%3u}+\n", x, y);
#endif
	node = elementList.first;
	while (node)
	{
		if (el_isNodeTouched(node, x, y))
		{
			// printf(" found {%3i,%3i}\n", node->x, node->y);
			selectedNode = node;
			el_pushNodeFirst(node);
#ifdef DEBUG_PRINT
			printf("%s selected\n", elementNames[node->elem]);
#endif
			break;
		}
		node = node->next;
	}
#ifdef DEBUG_PRINT
	if (!selectedNode)
		printf("No node found\n");
#endif
}


// ------------------------------------
void el_moveSelectedNode(u16 x, u16 y)
// ------------------------------------
{
	selectedNode->x = x - (ELEMENT_SIZE / 2);
	selectedNode->y = y - (ELEMENT_SIZE / 2);
}


// ------------------------------------
bool el_isNodeTouched(elementNode_s* node, u16 x, u16 y)
// ------------------------------------
{
	return (x >= node->x && x < node->x + ELEMENT_SIZE &&
			y >= node->y && y < node->y + ELEMENT_SIZE);
}



// ------------------------------------
void el_init()
// ------------------------------------
{
	el_freeNodes();
	el_resetDiscoveredElements();
}


// ------------------------------------
void el_init(element_t elem)
// ------------------------------------
{
	el_init();
	el_createNode(elem);
	// elementList.last = elementList.first;
}

// ------------------------------------
void el_init(elementNode_s* node)
// ------------------------------------
{
	el_init();
	el_addNode(node);
	// elementList.last = elementList.first;
}


// ------------------------------------
void el_removeNode(elementNode_s* node)
// ------------------------------------
{
#ifdef DEBUG_PRINT
	// printf("Removing %9p", node);
#endif
	// If not the last
	if (node->next)
		node->next->prev = node->prev;
	else
		elementList.last = node->prev;
	// If not the first
	if (node->prev)
		node->prev->next = node->next;
	else
		elementList.first = node->next;
	node->next = NULL;
	node->prev = NULL;
	elementList.count--;
#ifdef DEBUG_PRINT
	// printf(" OK\n");
#endif
}


// ------------------------------------
void el_addNode(elementNode_s* node)
// ------------------------------------
{
#ifdef DEBUG_PRINT
	// printf("Adding %9p", node);
#endif
	node->prev = NULL;
	node->next = elementList.first;
	if (elementList.first)
		elementList.first->prev = node;
	if (!elementList.last)
		elementList.last = node;
	elementList.first = node;
	elementList.count++;
#ifdef DEBUG_PRINT
	// printf(" OK\n");
#endif
}


// ------------------------------------
void el_pushNodeFirst(elementNode_s* node)
// ------------------------------------
{
	if (node != elementList.first)
	{
		el_removeNode(node);
		el_addNode(node);
	}
}



// ------------------------------------
void el_discoverElement(element_t elem)
// ------------------------------------
{
#ifdef DEBUG_PRINT
	printf("%s discovered\n", elementNames[elem]);
#endif
	if (!discoveredElements[elem])
	{
		discoveredElementCount++;
		discoveredElements[elem] = true;
		el_updateDiscoveries();
	}
}


// ------------------------------------
bool el_isElementDiscovered(element_t elem)
// ------------------------------------
{
	return discoveredElements[elem];
}

// ------------------------------------
u16 el_discoveredElementCount()
// ------------------------------------
{
	discoveredElementCount = 0;

	u16 count = Element::Count-2;
	for (u16 i = 1; i < count; i++)
	{
		if (discoveredElements[i])
		{
			discoveredElementCount++;
		}
	}
	
	return discoveredElementCount;
}


// ------------------------------------
void el_resetDiscoveredElements()
// ------------------------------------
{
#ifdef DEBUG_PRINT
	printf("Discovered elements resetted\n");
#endif
	u16 count = Element::Count-2;
	u16 i = 0;
	for (; i < Element::None+1; i++)
	{
		discoveredElements[i] = true;
	}
	for (; i < Element::Air+1; i++)
	{
		discoveredElements[i] = true;
	}
	for (; i < count; i++)
	{
		discoveredElements[i] = false;
	}
	discoveredElementCount = Element::Air;
}


// ------------------------------------
void el_emptyDiscoveries()
// ------------------------------------
{
	u16 count = Element::Count-2;
	for (u16 i = 0; i < count; i++)
	{
		elementDiscoveries[i] = Element::None;
	}
}


// ------------------------------------
void el_fillDiscoveries()
// ------------------------------------
{
	const char* actualWord;
	const char* minWord = "\x01";
	const char* maxWord = "\x7F";
	u16 count = Element::Count-1;

	element_t elem = Element::None;
	u16 i, j;
	for (i = 0; i < discoveredElementCount; i++)
	{
		for (j = 1; j < count; j++)
		{
			if (discoveredElements[j])
			{
				actualWord = elementNames[j];

				// printf("New actualWord: %s", actualWord);
				// printf("  %2i %2i\n", strcmp(actualWord, minWord), strcmp(actualWord, maxWord));

				if ((strcmp(actualWord, minWord) > 0) && (strcmp(actualWord, maxWord) < 0))
				{
					maxWord = actualWord;
					elem = (element_t) j;
					// printf("New maxWord: %s (%s)\n", maxWord, elementNames[elem]);
				}
			}
		}

		// svcSleepThread(1000000000L);
		// printf("\n");

		minWord = maxWord;
		maxWord = "\x7F";

		elementDiscoveries[i] = elem;
	}

	if (discoveredElementCount < count)
	{
		elementDiscoveries[i] = Element::None;
	}
}


// ------------------------------------
void el_updateDiscoveries()
// ------------------------------------
{
	el_emptyDiscoveries();
	el_fillDiscoveries();
}



// ------------------------------------
void el_drawNode(elementNode_s* node)
// ------------------------------------
{
	//sf2d_draw_rectangle(node->x, node->y, 32, 32, RGBA8(0xFF, 0xFF, 0xFF, 0xFF)/*elementColors[node->elem]*/);
	sf2d_draw_texture_part(elemTiles, node->x, node->y, (node->elem % ROW_TILE_COUNT) * TILE_SIZE, (node->elem / ROW_TILE_COUNT) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}


// ------------------------------------
void el_drawNodes()
// ------------------------------------
{
	sf2d_draw_texture(workBackground, 0, 0);
	
	elementNode_s* node;

	node = elementList.last;
	while (node)
	{
		el_drawNode(node);
		node = node->prev;
	}
}


// ------------------------------------
void el_freeNode(elementNode_s* node)
// ------------------------------------
{
#ifdef DEBUG_PRINT
	printf("%s deleted\n", elementNames[node->elem]);
#endif
	el_removeNode(node);
	delete node;
}


// ------------------------------------
void el_freeNodes()
// ------------------------------------
{
	elementNode_s* node;
	elementNode_s* prevNode;

	node = elementList.last;
	while (node)
	{
		prevNode = node->prev;
		el_freeNode(node);
		node = prevNode;
	}

	elementList.first = NULL;
	elementList.last = NULL;
	elementList.count = 0;
}



// ------------------------------------
AlchemyScene::AlchemyScene() : Scene() { }
// ------------------------------------


// ------------------------------------
AlchemyScene::~AlchemyScene() { }
// ------------------------------------


// ------------------------------------
void AlchemyScene::initialize()
// ------------------------------------
{
	printf("Scene initialized!\n");

	el_init();

	if (!elemTiles) elemTiles = sf2d_create_texture_mem_RGBA8(ImageManager::elemTiles_img.pixel_data, ImageManager::elemTiles_img.width, ImageManager::elemTiles_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	if (!workBackground) workBackground = sf2d_create_texture_mem_RGBA8(ImageManager::workBackground_img.pixel_data, ImageManager::workBackground_img.width, ImageManager::workBackground_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	
	el_createNode(Element::DoubleRainbow);
	el_createNode(Element::Horse);
	el_createNode(Element::Fire);
	el_createNode(Element::Water);
	el_createNode(Element::Lava);
	el_createNode(Element::Water);
	el_createNode(Element::Fire);
	el_createNode(Element::Earth);
	el_createNode(Element::Earth);
	el_createNode(Element::Earth);
	el_createNode(Element::Earth);
}


// ------------------------------------
void AlchemyScene::destroy()
// ------------------------------------
{
	printf("Scene destroyed!\n");

	el_freeNodes();

	if (elemTiles) sf2d_free_texture(elemTiles);
	if (workBackground) sf2d_free_texture(workBackground);
}


// ------------------------------------
void AlchemyScene::drawTopScreen()
// ------------------------------------
{
	// Empty
}


// ------------------------------------
void AlchemyScene::drawBottomScreen()
// ------------------------------------
{
	el_drawNodes();
}

// ------------------------------------
void AlchemyScene::updateInput(const keystate_s& ks)
// ------------------------------------
{
	if (ks.down & KEY_A)
	{
		el_discoverElement(Element::Steam);
	}

	if (ks.down & KEY_B)
	{
		consoleClear();
	}

	if (ks.down & KEY_X)
	{
		el_resetDiscoveredElements();
	}

	if (ks.down & KEY_Y)
	{
		el_updateDiscoveries();
		printf("Discovered elements:\n");
		for (u16 i = 0; i < discoveredElementCount; i++)
		{
			printf("%s ", elementNames[elementDiscoveries[i]]);
		}
		printf("\n");
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