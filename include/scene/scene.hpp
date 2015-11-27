#ifndef SCENE_HPP
#define SCENE_HPP

#include "keystate.h"

class Scene
{
	public:
		virtual ~Scene();
	
		virtual void initialize();
		virtual void destroy();
		virtual void drawTopScreen();
		virtual void drawBottomScreen();
		virtual void updateInput(const keystate_s& ks);

	protected:
		Scene();
};

#endif // SCENE_HPP
