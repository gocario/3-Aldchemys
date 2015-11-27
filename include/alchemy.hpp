#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "types.h"

#include "data/element.hpp"

typedef Element::element_e element_t;

struct blendResult_s
{
	element_t first;
	element_t second;
	element_t result;
};

extern const u16 blendCount;
extern const blendResult_s blendResults[];

element_t blendResult(element_t first, element_t second);

#endif // ELEMENT_HPP
