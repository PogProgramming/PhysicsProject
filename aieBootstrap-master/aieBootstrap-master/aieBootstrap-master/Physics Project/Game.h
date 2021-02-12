#pragma once
#include "PhysicsScene.h"

class Game
{
public:
	Game(PhysicsScene* a_physicsScene);
	~Game();

	void Init();
	void Update(float deltaTime);
	void Draw();
	
	void BuildMap();

protected:
	PhysicsScene* m_physicsScene;

	void Build_Level1();
};

