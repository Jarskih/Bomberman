#include "State.h"
#include "Musicplayer.h"

void State::changeScene(int newScene)
{
	m_scene = newScene;
}

void State::sceneTransition(sp<GUIArrow> &arrow)
{
	switch (m_scene)
	{
	case MENU:
		if (arrow->getPosition() == 0)
		{
			changeScene(LEVEL_INTRO);
		}
		break;
	case LEVEL_INTRO:
		changeScene(LEVEL);
		break;
	case LEVEL:
		break;
	case DEFEAT:
		if (arrow->getPosition() == 0)
		{
			changeScene(LEVEL_INTRO);
		}
		else if (arrow->getPosition() == 1)
		{
			changeScene(MENU);
		}

		break;
	default:
		break;
	}
}

void State::toggleDebug()
{
	if (m_debug)
	{
		m_debug = false;
	}
	else
	{
		m_debug = true;
	}
}

void State::goToMenu()
{
	changeScene(State::MENU);
	MusicPlayer::StopMusic();
}

void State::nextLevel()
{
	m_level++;
	m_enemies += 2;
}

void State::incrementScore(int addedScore)
{
	m_score += addedScore;
}

void State::incrementLives()
{
	m_lives += 1;
}

void State::decrementLives()
{
	m_lives--;
}
