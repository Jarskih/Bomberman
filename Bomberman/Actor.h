#pragma once
#include "Map.h"

class Map;

class Actor {
public:
	Actor() = default;
	virtual ~Actor();


	virtual void update(const sp<Map>& map)
	{
	}

	virtual void render(const sp<Map>& map)
	{
	}
};

