#include "State.h"

void State::changeScene()
{
	switch (scene)
	{
	case MENU:
		scene = LEVEL_INTRO;
		break;
	case LEVEL_INTRO:
		scene = LEVEL;
		break;
	case LEVEL:
		break;
	case DEFEAT:
		scene = MENU;
		break;
	}
}
