#include "alchemy_scene.hpp"
#include "data/images.hpp"

#include <stdio.h>
#include <string.h>

#include "fs.h"

u8 savebuffer[SAVE_SIZE];

elementList_s elementList;
elementNode_s* selectedNode = NULL;

s16 libraryOffset = 0;
u16 discoveredElementCount = 0;
bool discoveredElements[Element::Count-1];
element_t elementDiscoveries[Element::Count-2];

sf2d_texture* workspaceBackground = NULL;
sf2d_texture* libraryBackground = NULL;
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
	printf("Searching at: {%3u,%3u}- ", x, y);
#endif
	node = selectedNode->next;
	while (node)
	{
		if (el_isNodeTouched(node, x, y))
		{
#ifdef DEBUG_PRINT
			printf("%s found\n", elementNames[node->elem]);
#endif
			element_t elem = blendResult(selectedNode->elem, node->elem);
			if (elem != Element::None)
			{
				x = node->x;
				y = node->y;
				el_freeNode(node);
				el_freeNode(selectedNode);
				selectedNode = NULL;

				el_discoverElement(elem);
				node = el_createNode(elem);
				node->x = x;
				node->y = y;
			}

			break;
		}
		node = node->next;
	}
#ifdef DEBUG_PRINT
	if (!node)
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
	printf("Searching at: {%3u,%3u}+ ", x, y);
#endif
	node = elementList.first;
	while (node)
	{
		if (el_isNodeTouched(node, x, y))
		{
#ifdef DEBUG_PRINT
			printf("%s found\n", elementNames[node->elem]);
#endif
			selectedNode = node;
			el_pushNodeFirst(node);

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
void el_destroySelectedNode()
// ------------------------------------
{
	el_freeNode(selectedNode);
	selectedNode = NULL;
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
	return withinRectangle(x, y, node->x, node->y, ELEMENT_SIZE, ELEMENT_SIZE);
	// return (x >= node->x && x < node->x + ELEMENT_SIZE &&
	// 		y >= node->y && y < node->y + ELEMENT_SIZE);
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
element_t el_selectedLibraryElement(u16 x, u16 y)
// ------------------------------------
{
	u32 ii = (y + libraryOffset) / ELEMENT_SIZE;
	return elementDiscoveries[ii];
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
	u16 i = 0;
	// for (; i < Element::None+1; i++)
	// 	discoveredElements[i] = true;
	// for (; i < Element::Air+1; i++)
	// 	discoveredElements[i] = true;
	for (; i < Element::Count-2; i++)
		discoveredElements[i] = false;

	el_discoverBasicElements();
}


// ------------------------------------
void el_discoverBasicElements()
// ------------------------------------
{
	u16 i = 0;
	for(; i < Element::None+1; i++)
		discoveredElements[i] = true;
	for (; i < Element::Air+1; i++)
		discoveredElements[i] = true;
	discoveredElementCount = Element::Air;

	el_updateDiscoveries();
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
void el_drawSelectedNode()
// ------------------------------------
{
	if (selectedNode)
	{
		sf2d_draw_texture_part_scale(elemTiles, 152, 72, (selectedNode->elem % ROW_TILE_COUNT) * TILE_SIZE, (selectedNode->elem / ROW_TILE_COUNT) * TILE_SIZE, TILE_SIZE, TILE_SIZE, 3.0f, 3.0f);
	}
}


// ------------------------------------
void el_drawElement(element_t elem, s16 x, s16 y)
// ------------------------------------
{
	sf2d_draw_texture_part(elemTiles, x, y, (elem % ROW_TILE_COUNT) * TILE_SIZE, (elem / ROW_TILE_COUNT) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}


// ------------------------------------
void el_drawLibrary()
// ------------------------------------
{
	sf2d_draw_texture(libraryBackground, 256, 0);

	u16 index;
	for (u16 i = 0; i < 8; i++)
	{
		index = i + (libraryOffset) / ELEMENT_SIZE;

		if (index >= 0 && index < discoveredElementCount)
		{
			el_drawElement(elementDiscoveries[index], 272, index * TILE_SIZE - libraryOffset);
		}
	}
}


// ------------------------------------
void el_drawNode(elementNode_s* node)
// ------------------------------------
{
	el_drawElement(node->elem, node->x, node->y);
	// sf2d_draw_texture_part(elemTiles, node->x, node->y, (node->elem % ROW_TILE_COUNT) * TILE_SIZE, (node->elem / ROW_TILE_COUNT) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}


// ------------------------------------
void el_drawNodes()
// ------------------------------------
{
	sf2d_draw_texture(workspaceBackground, 0, 0);
	
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
void el_readSavefile()
// ------------------------------------
{
	u32 bytesRead;
	u8* savedata = savebuffer;
	char path[] = "/alambic.sav";
	if (FS_ReadFile(path, savedata, &sdmcArchive, &sdmcHandle, &bytesRead, SAVE_SIZE))
		printf("Save file not found!\n");
	else
		printf("%lu bytes read\n", bytesRead);
}


// ------------------------------------
void el_writeSavefile()
// ------------------------------------
{
	u32 bytesWritten;
	u8* savedata = savebuffer;
	char path[] = "/alambic.sav";
	FS_WriteFile(path, savedata, &sdmcArchive, &sdmcHandle, &bytesWritten, SAVE_SIZE);
	printf("%lu bytes written\n", bytesWritten);
}


// ------------------------------------
void el_readSavedata()
// ------------------------------------
{
	u8* savedata = savebuffer;
	u16 offset = 0;
	u16 i;

	// Version
	offset = VERSION_OFFSET;
	// u32 version = *(u32*)(savedata + offset);

	// Discoveries
	offset = DISCOVERIES_OFFSET;
	u16 count = Element::Count-1;
	for (u16 b = 0; b < count; b++)
		discoveredElements[b] = ((savedata[offset + b/8] >> (b % 8)) & 0x1) == 1;

	// Workspace
	offset = WORKSPACE_OFFSET;
	element_t elem;
	elementNode_s* node;
	for (i = 0; i < WORKSPACE_SIZE; i += 2+2+2)
	{
		elem = (element_t) (*(u16*)(savedata + offset + i + 0));
		if (elem == Element::None) break;

		node = el_createNode(elem);
		node->x = *(s16*)(savedata + offset + i + 2);
		node->y = *(s16*)(savedata + offset + i + 4);
		printf("%s { %2i, %2i }\n", elementNames[node->elem], node->x, node->y);
	}
}



// ------------------------------------
void el_writeSavedata()
// ------------------------------------
{
	u8* savedata = savebuffer;
	u16 offset = 0;
	u16 i;

	// Version
	offset = VERSION_OFFSET;
	*(u32*)(savedata + offset) = VERSION;

	// Discoveries
	offset = DISCOVERIES_OFFSET;
	u16 count = Element::Count-1;
	for (u16 b = 0; b < count; b += 8)
		*(u8*)(savedata + offset + b/8) = 0;
	for (u16 b = 0; b < count; b++)
		*(u8*)(savedata + offset + b/8) |= (discoveredElements[b] ? 1 : 0) << (b % 8);

	// Workspace
	offset = WORKSPACE_OFFSET;
	elementNode_s* node = elementList.first;
	for (i = 0; i < WORKSPACE_SIZE && node; i += 2+2+2)
	{
		// printf("{ %s, %2i, %2i }\n", elementNames[node->elem], node->x, node->y);
		*(u16*)(savedata + offset + i + 0) = (u16) node->elem;
		*(s16*)(savedata + offset + i + 2) = node->x;
		*(s16*)(savedata + offset + i + 4) = node->y;
		printf("{ %s, %2i, %2i }\n", elementNames[*(u16*)(savedata + offset + i + 0)], *(s16*)(savedata + offset + i + 2), *(s16*)(savedata + offset + i + 4));
		node = node->next;
	}
	for (; i < WORKSPACE_SIZE; i++)
	{
		*(u8*)(savedata + offset + i) = 0x00;
	}

	// Padding
	offset = PADDING_OFFSET;
	for(i = 0; i < PADDING_SIZE; i++)
	{
		*(u8*)(savedata + offset + i) = 0x00;
	}
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
	el_init();

	FS_FilesysInit();
	el_readSavefile();
	el_readSavedata();

	el_discoverBasicElements();
	el_discoveredElementCount();
	el_updateDiscoveries();

	if (!elemTiles) elemTiles = sf2d_create_texture_mem_RGBA8(ImageManager::elemTiles_img.pixel_data, ImageManager::elemTiles_img.width, ImageManager::elemTiles_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	if (!workspaceBackground) workspaceBackground = sf2d_create_texture_mem_RGBA8(ImageManager::workspaceBackground_img.pixel_data, ImageManager::workspaceBackground_img.width, ImageManager::workspaceBackground_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	if (!libraryBackground) libraryBackground = sf2d_create_texture_mem_RGBA8(ImageManager::libraryBackground_img.pixel_data, ImageManager::libraryBackground_img.width, ImageManager::libraryBackground_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	
	// el_createNode(Element::DoubleRainbow);
	// el_createNode(Element::Horse);
	// el_createNode(Element::Fire);
	// el_createNode(Element::Water);
	// el_createNode(Element::Lava);
	// el_createNode(Element::Water);
	// el_createNode(Element::Fire);
	// el_createNode(Element::Earth);
	// el_createNode(Element::Earth);
	// el_createNode(Element::Earth);
	// el_createNode(Element::Earth);

	printf("Scene initialized!\n");
}


// ------------------------------------
void AlchemyScene::destroy()
// ------------------------------------
{
	el_writeSavedata();
	el_writeSavefile();
	FS_FilesysExit();

	el_freeNodes();

	if (elemTiles) sf2d_free_texture(elemTiles);
	if (workspaceBackground) sf2d_free_texture(workspaceBackground);
	if (libraryBackground) sf2d_free_texture(libraryBackground);

	printf("Scene destroyed!\n");
}


// ------------------------------------
void AlchemyScene::drawTopScreen()
// ------------------------------------
{
	el_drawSelectedNode();
}


// ------------------------------------
void AlchemyScene::drawBottomScreen()
// ------------------------------------
{
	// Library
	el_drawLibrary();

	// Workspace
	el_drawNodes();
}

// ------------------------------------
void AlchemyScene::updateInput(const keystate_s& ks)
// ------------------------------------
{
	{
		if (ks.held & KEY_UP)
		{
			libraryOffset += 8;
			if (libraryOffset >= discoveredElementCount * ELEMENT_SIZE - 240) libraryOffset = discoveredElementCount * ELEMENT_SIZE - 240;
		}

		if (ks.held & KEY_DOWN)
		{
			libraryOffset -= 8;
			if (libraryOffset < 0) libraryOffset = 0;
		}
	}

	if (ks.down & (KEY_L | KEY_X))
	{
		if (selectedNode)
		{
			elementNode_s* node = el_createNode(selectedNode->elem);
			node->x = selectedNode->x;
			node->y = selectedNode->y;
			el_pushNodeFirst(selectedNode);
		}
	}

	if (ks.down & KEY_A)
	{
		el_discoverElement(Element::Steam);
		el_discoverElement(Element::Hurricane);
		el_discoverElement(Element::Aquarium);
		el_discoverElement(Element::Time);
		el_discoverElement(Element::Campfire);
		el_discoverElement(Element::Greenhouse);
		el_discoverElement(Element::Swamp);
		el_discoverElement(Element::SteamEngine);
		el_discoverElement(Element::Cow);
	}

	if (ks.down & KEY_B)
	{
		// consoleClear();
	}

	if (ks.down & KEY_X)
	{

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
			// In the workspace
			if (withinRectangle(ks.touch.px, ks.touch.py, 0, 0, 256, 240))
			{
				el_selectNode(ks.touch.px, ks.touch.py);
			}
			if (withinRectangle(ks.touch.px, ks.touch.py, 256, 0, 64, 240))
			{
				element_t elem = el_selectedLibraryElement(ks.touch.px, ks.touch.py);
				printf("%s\n", elementNames[elem]);
				if (elem != Element::None && elem < Element::Count)
					selectedNode = el_createNode(elem);
			}

			originalTouch = ks.touch;
			currentTouch = ks.touch;
		}
		
		if (ks.held & KEY_TOUCH)
		{
			if (el_isNodeSelected())
			{
				el_moveSelectedNode(ks.touch.px, ks.touch.py);
			}

			currentTouch = ks.touch;
		}

		if (ks.up & KEY_TOUCH)
		{
			// In the workspace
			if (withinRectangle(currentTouch.px, currentTouch.py, 0, 0, 256, 240))
			{
				if (el_isNodeSelected())
				{
					el_deselectNode();
				}
			}

			// In the library
			if (withinRectangle(currentTouch.px, currentTouch.py, 256, 0, 64, 240))
			{
				if (el_isNodeSelected())
				{
					el_destroySelectedNode();
				}
			}

			originalTouch = { 0, 0 };
			currentTouch = { 0, 0 };
		}
	}
}