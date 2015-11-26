#include "alchemy_scene.hpp"

#include <sf2d.h>
#include <stdio.h>

elementList_s elementList;
elementNode_s* selectedNode = NULL;

void el_createNode(element_t elem)
{
	elementNode_s* node = new elementNode_s;
	node->elem = elem;
	node->pos = {0,0};
	el_addNode(node);
}


void el_deselectNode()
{
	selectedNode = NULL;
}


void el_selectNode(u16 x, u16 y)
{
	printf("Searching for: {%3u,%3u}", x, y);
	elementNode_s* node;

	node = elementList.first;
	while (node)
	{
		if (el_touchNode(node, x, y))
		{
			printf(" found {%3i,%3i}\n", node->pos.x, node->pos.y);
			selectedNode = node;
			el_pushNodeFirst(node);
			break;
		}
		node = node->next;
	}
	if (!selectedNode)
	{
		printf("                \n");
	}
}


void el_moveSelectedNode(u16 x, u16 y)
{
	selectedNode->pos.x = x - (ELEMENT_SIZE / 2);
	selectedNode->pos.y = y - (ELEMENT_SIZE / 2);
}


bool el_touchNode(elementNode_s* node, u16 x, u16 y)
{
	return (x >= node->pos.x && x < node->pos.x + ELEMENT_SIZE &&
			y >= node->pos.y && y < node->pos.y + ELEMENT_SIZE);
}



void el_init(elementNode_s* node)
{
	el_freeNodes();
	node->next = NULL;
	node->prev = NULL;
	elementList.first = node;
	elementList.last = node;
	elementList.count = 1;
}


void el_removeNode(elementNode_s* node)
{
	printf("Removing %9p", node);
	
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
	printf(" OK\n");
}


void el_addNode(elementNode_s* node)
{
	printf("Adding %9p", node);
	node->prev = NULL;
	node->next = elementList.first;
	elementList.first->prev = node;
	elementList.first = node;
	elementList.count++;
	printf(" OK\n");
}


void el_pushNodeFirst(elementNode_s* node)
{
	if (node != elementList.first)
	{
		el_removeNode(node);
		el_addNode(node);
	}
}



void el_drawNode(elementNode_s* node)
{
	sf2d_draw_rectangle(node->pos.x, node->pos.y, 32, 32, elementColors[node->elem]);
}


void el_drawNodes()
{
	elementNode_s* node;

	node = elementList.last;
	while (node)
	{
		el_drawNode(node);
		node = node->prev;
	}
}


void el_freeNode(elementNode_s* node)
{
	el_removeNode(node);
	delete node;
}

void el_freeNodes()
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
}
