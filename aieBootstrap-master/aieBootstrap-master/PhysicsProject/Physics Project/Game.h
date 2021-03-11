#pragma once
#include "PhysicsScene.h"
#include "Sphere.h"
#include <Gizmos.h>

#include "Input.h"
class Game
{
public:
	Game(PhysicsScene* a_physicsScene);
	~Game();

	void Init();
	void Update(float deltaTime);
	void Draw();

	glm::vec2 GetSpawnPoint() { return m_playerSpawnPoint; }
	void Reset();

	void ReachedGoal();

	void BuildMap();
	void UpdateBuildMap();

	glm::vec2 worldPos;
	Sphere* m_player;
	int m_strokes = 0;


protected:
	PhysicsScene* m_physicsScene;

	Sphere* m_endGoal;

	bool m_levelChanged = true;

	int m_activeLevel = 1;
	int m_maxLevel = 2;

	void Build_Level1();
	void Build_Level2();

	glm::vec2 m_playerSpawnPoint = glm::vec2(0);
};
