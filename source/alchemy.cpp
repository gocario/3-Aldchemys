#include "alchemy.hpp"

#include "data/element.hpp"

using namespace Element;

const alchemyResult_s alchemyResults[] =
{
	{ Air, Air, Pressure },
	{ Air, Earth, Dust },
	{ Air, Fire, Energy },
	{ Air, Water, Rain },
	{ Earth, Earth, Pressure },
	{ Earth, Fire, Lava },
	{ Earth, Water, Mud },
	{ Fire, Water, Steam },
	{ Water, Water, Sea },
	// { , ,  },
};
