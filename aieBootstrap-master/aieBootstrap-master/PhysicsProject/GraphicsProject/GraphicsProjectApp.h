#pragma once

#include "Application.h"
#include "Mesh.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include "OBJMesh.h"
#include "Input.h"
#include "Camera.h"
#include <vector>

class GraphicsProjectApp : public aie::Application {
public:

	GraphicsProjectApp();
	virtual ~GraphicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	int currentCamera = 0;
	const int maxCameras = 1;
	std::vector<Camera> m_cameras;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	// === SHADER =======
	aie::ShaderProgram m_simpleShader;
	aie::ShaderProgram m_bunnyShader;
	aie::ShaderProgram m_phongShader;
	// ==================
	// Basic Plane
	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
	float m_bunnyYRotation = 0.0f;
	glm::vec3 m_bunnyPosition = { 0, 0, 0 };

	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;
	float m_dragonYRotation = 0.0f;
	glm::vec3 m_dragonPosition = { 0, 0, 0 };

	aie::OBJMesh m_lucyMesh;
	glm::mat4 m_lucyTransform;
	float m_lucyYRotation = 0.0f;
	glm::vec3 m_lucyPosition = { 0, 0, 0 };

	aie::OBJMesh m_buddhaMesh;
	glm::mat4 m_buddhaTransform;
	float m_buddhaYRotation = 0.0f;
	glm::vec3 m_buddhaPosition = { 0, 0, 0 };

	struct Light {
		glm::vec3 direction;
		glm::vec3 color;
	};

	Light m_light;
	glm::vec3 m_ambientLight;

public:
	bool LoadShaderAndMeshLogic();
	void DrawShaderAndMeshes(glm::mat4, glm::mat4);
	void IMGUI_Logic();

	float Rotation(glm::mat4 &mat, float rot, glm::vec3 axis);

protected:
	float m_camMovementSpeed = 10.0f;
};