#pragma once

class SceneManager; // forward declaration

class Scene
{
protected:
	SceneManager* sceneManager_ = nullptr;

public:
	void SetSceneManager(SceneManager* manager) { sceneManager_ = manager; }

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Shutdown() = 0;

	virtual ~Scene() = default;
};
