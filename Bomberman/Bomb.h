#pragma once
class Bomb
{
public:
	Bomb(int flamePower, int posX, int posY) : m_flamePower(flamePower), m_posX(posX), m_posY(posY) {};
	~Bomb() = default;
	void render();
private:
	int m_flamePower = 0;
	int m_posX = 0;
	int m_posY = 0;
};

