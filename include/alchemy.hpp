#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "types.h"

#include "data/element.hpp"

typedef Element::element_e element_t;

struct alchemyResult_s
{
	element_t first;
	element_t second;
	element_t result;
};

extern const alchemyResult_s alchemyResults[];

#endif // ELEMENT_HPP
