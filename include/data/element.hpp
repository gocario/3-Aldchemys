#ifndef DATA__ELEMENT__HPP
#define DATA__ELEMENT__HPP

#include "types.h"

namespace Element
{
	enum element_e
	{
		None = 0,

		Air,
		Earth,
		Fire,
		Water,
		Pressure,
		Dust,
		Energy,
		Rain,
		Lava,
		Mud,
		Steam,
		Sea,

		Count,
	};
}

extern const char* elementNames[];
extern const u32 elementColors[];

#endif // DATA__ELEMENT__HPP
