#pragma once

class Graphics;
class Pipeline;
class GameObject;

class SceneManager;
class InputManager;
class TimeManager;
class ResourceManager;

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

	inline shared_ptr<SceneManager> GetSceneManager();
	inline shared_ptr<InputManager> GetInputManager();
	inline shared_ptr<TimeManager> GetTimeManager();
	inline shared_ptr<ResourceManager> GetResourceManager();

	inline shared_ptr<Pipeline> GetPipeline();

private:
	HWND _hwnd;

	shared_ptr<Pipeline> _pipeline;
	shared_ptr<Graphics> _graphics;

private:
	shared_ptr<SceneManager> _scene;
	shared_ptr<InputManager> _input;
	shared_ptr<TimeManager> _time;
	shared_ptr<ResourceManager> _resource;
};

shared_ptr<SceneManager> Game::GetSceneManager()
{
	return _scene;
}
shared_ptr<InputManager> Game::GetInputManager()
{
	return _input;
}
shared_ptr<TimeManager> Game::GetTimeManager()
{
	return _time;
}
shared_ptr<ResourceManager> Game::GetResourceManager()
{
	return _resource;
}

shared_ptr<Pipeline> Game::GetPipeline()
{
	return _pipeline;
}

extern unique_ptr<Game> GGame;