#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include "OBJMesh.h"
#include "Input.h"
#include "Camera.h"
#include <vector>
#include "Scene.h"

class GraphicsProjectApp : public aie::Application {
public:

	GraphicsProjectApp();
	virtual ~GraphicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	std::vector<Camera*> m_cameras;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	aie::Texture m_gridTexture;

	// === SHADER =======
	aie::ShaderProgram m_simpleShader;
	aie::ShaderProgram m_bunnyShader;
	aie::ShaderProgram m_phongShader;
	aie::ShaderProgram m_textureShader;
	aie::ShaderProgram m_normalMapShader;
	// ==================
	// Basic Plane
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	aie::OBJMesh m_bunnyMesh;

	aie::OBJMesh m_dragonMesh;

	aie::OBJMesh m_lucyMesh;

	aie::OBJMesh m_buddhaMesh;

	aie::OBJMesh m_spearMesh;

	aie::OBJMesh m_canMesh;

	//struct Light {
	//	glm::vec3 direction;
	//	glm::vec3 color;
	//};

	//Light m_dynamicLight;

	float m_directionalRotSpeed = 2;
	float m_directionalOrbitRadius = 1;
	glm::vec3 m_directionalLightPos = glm::vec3(0);

	glm::vec3 m_camPosition = glm::vec3(15);

	Scene* m_scene;

	glm::vec3 m_ambientLight;

public:
	bool LoadShaderAndMeshLogic(Light a_light);
	//void DrawShaderAndMeshes(glm::mat4, glm::mat4);
	void IMGUI_Logic();

protected:
	float m_camMovementSpeed = 10.0f;
};