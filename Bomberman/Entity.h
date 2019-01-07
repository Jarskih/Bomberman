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
	int m_pos_x = 0;
	int m_pos_y = 0;
	float m_scale = 0;
	bool m_is_alive = true; // If inactive, do not update
	bool m_visible = true; // If inactive, do not render
	float m_speed_x = 0;
	float m_speed_y = 0;
	int m_state = 0;
	SDL_Rect m_collider = {};
	EntityType m_type;
	SDL_Rect m_windowRect = {};
	SDL_Rect m_textureRect = {};
	enum States { IDLE_UP, IDLE_DOWN, IDLE_LEFT, IDLE_RIGHT, DOWN, UP, LEFT, RIGHT, DEAD };
public:
	EntityType getType() const;;
	bool isAlive() const;
	bool isVisible() const;
	virtual ~Entity() = default;;
	SDL_Rect getCollider() const;;
	int getPositionX() const;;
	int getPositionY() const;;
	virtual void render() {};
	virtual void update() = 0;
};

inline EntityType Entity::getType() const
{
	return m_type;
}

inline bool Entity::isAlive() const
{
	return m_is_alive;
}

inline bool Entity::isVisible() const
{
	return m_visible;
}

inline SDL_Rect Entity::getCollider() const
{
	return m_collider;
}

inline int Entity::getPositionX() const
{
	return m_pos_x;
}

inline int Entity::getPositionY() const
{
	return m_pos_y;
}
