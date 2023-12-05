#include "pch.h"
#include "Game.h"

#include "MonoBehaviour.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"

unique_ptr<Game> GGame = make_unique<Game>();

Game::Game()
	: _hwnd(nullptr)
{
}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);
	_pipeline = make_shared <Pipeline>(_graphics->GetDeviceContext());

	_input = make_shared<InputManager>();
	_input->Init(hwnd);
	_time = make_shared<TimeManager>();
	_time->Init();
	_resource = make_shared<ResourceManager>(_graphics->GetDevice());
	_resource->Init();
	_render = make_shared<RenderManager>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_render->Init();

	_scene = make_shared<SceneManager>(_graphics);
	//_scene->Init();

	GGame->GetSceneManager()->LoadScene(L"Test");
}

void Game::Update()
{
	_input->Update();
	_time->Update();
	_scene->Update();
}

void Game::Render()
{
	_render->Update(_graphics);
}
