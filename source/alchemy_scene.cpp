#include "alchemy_scene.hpp"
#include "data/images.hpp"

#include <stdio.h>

elementList_s elementList;
elementNode_s* selectedNode = NULL;
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

				node = el_createNode(elem);
				node->x = x;
				node->y = y;

				node = NULL;
				selectedNode = NULL;
				// Place the break here to continue propagation
			}
			// Place the break here to stop propagation
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

	if (!elemTiles)
	{
		elemTiles = sf2d_create_texture_mem_RGBA8(ImageManager::elemTiles_img.pixel_data, ImageManager::elemTiles_img.width, ImageManager::elemTiles_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	}
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

	if (elemTiles) sf2d_free_texture(elemTiles);
}
