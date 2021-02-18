#pragma once
#include "PhysicsScene.h"
#include "Sphere.h"

class Game
{
public:
	Game(PhysicsScene* a_physicsScene);
	~Game();

	void Init();
	void Update(float deltaTime);
	void Draw();

	void Reset();

	void ReachedGoal();
	
	void BuildMap();

	glm::vec2 worldPos;
	Sphere* m_player;
	int m_strokes = 0;

protected:
	PhysicsScene* m_physicsScene;
	

	Sphere* m_endGoal;

	bool m_levelChanged = true;

	int m_activeLevel = 1;
	void Build_Level1();
	void Build_Level2();

};

