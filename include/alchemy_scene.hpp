#ifndef ALCHEMY_SCENE_HPP
#define ALCHEMY_SCENE_HPP

#include "alchemy.hpp"

#define ELEMENT_SIZE 32

struct elementPosition_s
{
	s16 x;
	s16 y;
};

struct elementNode_s
{
	element_t elem;
	elementPosition_s pos;
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

void el_createNode(element_t elem);
void el_deselectNode();
void el_selectNode(u16 x, u16 y);
void el_moveSelectedNode(u16 x, u16 y);
bool el_touchNode(elementNode_s* node, u16 x, u16 y);

void el_init(elementNode_s* node);
void el_removeNode(elementNode_s* node);
void el_addNode(elementNode_s* node);
void el_pushNodeFirst(elementNode_s* node);

void el_drawNode(elementNode_s* node);
void el_drawNodes();
void el_freeNodes();

extern elementList_s elementList;
extern elementNode_s* selectedNode;

#endif // ALCHEMY_SCENE_HPP
