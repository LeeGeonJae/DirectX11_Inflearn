#include "pch.h"
#include "Game.h"

#include "MonoBehaviour.h"
#include "GameObject.h"
#include "Camera.h"

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

	_gameObject = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_gameObject->GetOrAddTransform();
	}

	_camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
	}
}

void Game::Update()
{
	_gameObject->Update();
	_camera->Update();
}

void Game::Render()
{
	_graphics->RenderBegin();

	{
		_gameObject->Render(_pipeline);
	}

	_graphics->RenderEnd();
}