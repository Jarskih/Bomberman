#pragma once 

enum EntityType
{
	PLAYER,
	EASY_ENEMY,
	HARD_ENEMY
};

//  Base Class for all entity types
class Sprite;
class Collider;
struct SDL_Renderer;

class Entity
{
protected:
	int posX;
	int posY;
	float m_scale;
	bool m_active; // If inactive, do not update
	bool m_visible; // If inactive, do not render
	float speed_x;
	float speed_y;
	int state;
	SDL_Rect m_collider;
	EntityType m_type;
	SDL_Rect m_windowRect;
	SDL_Rect m_textureRect;
	enum states { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT, DEAD };
public:
	EntityType getType() { return m_type; };
	bool isActive() { return m_active; }
	bool isVisible() { return m_visible; }
	virtual ~Entity() {};
	SDL_Rect getCollider() { return m_collider; };
	int getPositionX() { return posX; };
	int getPositionY() { return posY; };
	virtual void render() {};
	virtual void update() = 0;
};
