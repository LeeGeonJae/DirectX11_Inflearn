#pragma once

class Scene
{
public:
	void Init();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

public:
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	inline const vector<shared_ptr<GameObject>>& GetGameObjects();

private:
	vector<shared_ptr<GameObject>> _gameObjects;
};

const vector<shared_ptr<GameObject>>& Scene::GetGameObjects()
{
	return _gameObjects;
}