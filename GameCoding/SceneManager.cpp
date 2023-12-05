#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Animation.h"
#include "Animator.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics)
	: _graphics(graphics)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Init();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();

	_activeScene->FixedUpdate();
}

void SceneManager::LoadScene(wstring sceneName)
{
	_activeScene = LoadTestScene();
	Init();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();

	// TODO
	// Camera
	shared_ptr<GameObject> camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		camera->GetOrAddTransform();
		camera->AddComponent(make_shared<Camera>());
		scene->AddGameObject(camera);
	}

	// Monster
	{
		shared_ptr<GameObject> gameObject = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			gameObject->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			gameObject->AddComponent(meshRenderer);
			auto material = GGame->GetResourceManager()->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);
			auto mesh = GGame->GetResourceManager()->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);
		}
		{
			auto animator = make_shared<Animator>();
			auto anim = GGame->GetResourceManager()->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
			gameObject->AddComponent(animator);
		}
		scene->AddGameObject(gameObject);
	}

	return scene;
}
