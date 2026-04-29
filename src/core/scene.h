#pragma once

class Scene
{
public:
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void shutdown() = 0;

	virtual ~Scene() = default;
};
