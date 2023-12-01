#pragma once

class Graphics;
class GameObject;

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd;

	shared_ptr<Pipeline> _pipeline;
	shared_ptr<Graphics> _graphics;
	
	shared_ptr<GameObject> _gameObject;

private:
};

