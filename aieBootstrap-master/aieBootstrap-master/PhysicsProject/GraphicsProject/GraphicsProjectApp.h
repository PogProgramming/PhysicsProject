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
	std::vector<Camera> m_cameras;

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
	glm::mat4 m_bunnyTransform;

	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;

	aie::OBJMesh m_lucyMesh;
	glm::mat4 m_lucyTransform;

	aie::OBJMesh m_buddhaMesh;
	glm::mat4 m_buddhaTransform;

	aie::OBJMesh m_spearMesh;
	glm::mat4 m_spearTransform;
	aie::Texture m_spearTexture;

	aie::OBJMesh m_manMesh;
	glm::mat4 m_manTransform;
	aie::Texture m_manTexture;

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