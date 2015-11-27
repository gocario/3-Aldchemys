#ifndef ALCHEMY_SCENE_HPP
#define ALCHEMY_SCENE_HPP

#include <sf2d.h>

#include "keystate.h"

#include "alchemy.hpp"

#define ROW_TILE_COUNT 25
#define TILE_SIZE 32
#define ELEMENT_SIZE 32

struct elementNode_s
{
	element_t elem;
	s16 x;
	s16 y;
	// The previous layer (to draw before)
	elementNode_s* prev;
	// The next layer (to draw after)
	elementNode_s* next;
};

struct elementList_s
{
	u16 count;
	// The first layer to display
	elementNode_s* first;
	// The last layer to display
	elementNode_s* last;
};

elementNode_s* el_createNode(element_t elem);
bool el_isNodeSelected();
void el_deselectNode();
void el_selectNode(u16 x, u16 y);
void el_moveSelectedNode(u16 x, u16 y);
bool el_isNodeTouched(elementNode_s* node, u16 x, u16 y);
void el_tryBlend();

void el_init();
void el_init(element_t elem);
void el_init(elementNode_s* node);
void el_removeNode(elementNode_s* node);
void el_addNode(elementNode_s* node);
void el_pushNodeFirst(elementNode_s* node);

void el_drawNode(elementNode_s* node);
void el_drawNodes();
void el_freeNode(elementNode_s* node);
void el_freeNodes();

void el_initialize();
void el_destroy();
void el_drawTopScreen();
void el_drawBottomScreen();
void el_updateInput(keystate_s ks);

extern elementList_s elementList;
extern elementNode_s* selectedNode;

extern sf2d_texture* workBackground;
extern sf2d_texture* elemTiles;

#endif // ALCHEMY_SCENE_HPP
