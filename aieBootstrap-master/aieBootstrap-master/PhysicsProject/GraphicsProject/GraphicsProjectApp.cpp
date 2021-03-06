#include "GraphicsProjectApp.h"
#include "Gizmos.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

float angle = 0.0f;

GraphicsProjectApp::GraphicsProjectApp() {

}

GraphicsProjectApp::~GraphicsProjectApp() {

}

bool GraphicsProjectApp::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	m_light.color = { 1, 1, 1 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	m_cameras.push_back(Camera());

	return LoadShaderAndMeshLogic();
}

void GraphicsProjectApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsProjectApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	IMGUI_Logic();

	// add a transform so we can see the axis
	Gizmos::addTransform(mat4(1));

	m_cameras[currentCamera].Update(deltaTime);

	float time = getTime();
	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_UP)) {
		if(currentCamera < m_cameras.size() - 1)
			currentCamera++;
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_DOWN)) {
		if (currentCamera > 0)
			currentCamera--;
	}

	//m_bunnyTransform = glm::rotate(m_bunnyTransform, m_bunnyYRotation, glm::vec3(0, 1, 0));
	//m_dragonTransform = glm::rotate(m_dragonTransform, m_dragonYRotation, glm::vec3(0, 1, 0));
	//m_lucyTransform = glm::rotate(m_lucyTransform, m_lucyYRotation, glm::vec3(0, 1, 0));
	//m_buddhaTransform = glm::rotate(m_buddhaTransform, m_buddhaYRotation, glm::vec3(0, 1, 0));


	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

}

void GraphicsProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	glm::mat4 projectionMatrix = m_cameras[currentCamera].GetProjectionMatrix(getWindowWidth(), (float)getWindowHeight());
	glm::mat4 viewMatrix = m_cameras[currentCamera].GetViewMatrix();


	DrawShaderAndMeshes(projectionMatrix, viewMatrix);

	Gizmos::draw(projectionMatrix * viewMatrix);
}

bool GraphicsProjectApp::LoadShaderAndMeshLogic()
{


#pragma region FlatBunny
	m_bunnyShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	// Load the fragment shader from a file
	m_bunnyShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	if (!m_bunnyShader.link()) {
		printf("Bunny Shader had an error: %s\n", m_bunnyShader.getLastError());
		return false;
	}

	if (m_bunnyMesh.load("./stanford/bunny.obj") == false) {
		printf("Bunny mesh failed!\n");
		return false;
	}

	m_bunnyTransform = {
		0.2f, 0, 0, 0,
		0, 0.2f, 0, 0,
		0, 0, 0.2f, 0,
		0, 0, 0, 1
	};

	m_bunnyTransform = glm::translate(m_bunnyTransform, glm::vec3(1, 0, 1) * 20.0f);
#pragma endregion
#pragma region Phong Shader
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if (m_phongShader.link() == false) {
		printf("Phong Shader had an error: %s\n", m_phongShader.getLastError());
		return false;
	}

#pragma endregion

#pragma region Texture Shader
	m_textureShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_textureShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	if (m_textureShader.link() == false) {
		printf("Textured Shader had an error: %s\n", m_textureShader.getLastError());
		return false;
	}
#pragma endregion

#pragma region NormalMapTexture Shader
	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalMap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalMap.frag");
	if (m_normalMapShader.link() == false) {
		printf("NormalMapTexture Shader had an error: %s\n", m_normalMapShader.getLastError());
		return false;
	}

#pragma endregion
#pragma region Quad
	m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	// Load the fragment shader from a file
	m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	if (!m_simpleShader.link()) {
		printf("Simple shader had an error: %s\n", m_simpleShader.getLastError());
		return false;
	}

	Mesh::Vertex vertices[4];
	vertices[0].position = { -0.5, 0.f, 0.5f, 1.f };
	vertices[1].position = { 0.5, 0.f, 0.5f, 1.f };
	vertices[2].position = { -0.5, 0.f, -0.5f, 1.f };
	vertices[3].position = { 0.5, 0.f, -0.5f, 1.f };

	unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

	m_quadMesh.InitialiseQuad();

	// We will make the quad 10 units by 10 units
	m_quadTransform = {
		10, 0, 0, 0,
		0, 10, 0, 0,
		0, 0, 10, 0,
		0, 0, 0, 1
	};

	m_quadTransform = glm::rotate(m_quadTransform, angle, glm::vec3(1));
#pragma endregion
#pragma region GridLogic
	if (m_gridTexture.load("./textures/numbered_grid.tga") == false) {
		printf("Failed to load: numbered_grid.tga\n");
		return false;
	}
#pragma endregion

//#pragma region SpearLogic
//	if (m_spearTexture.load("./stanford/soulspear_normal.tga") == false) {
//		printf("Failed to load: soulspear_normal.tga\n");
//		return false;
//	}
//#pragma endregion
//
//
//#pragma region ManLogic
//	if (m_manTexture.load("./stanford/ironman/M-COC_iOS_HERO_Tony_Stark_Iron_Man_Mark_VII_Body_N.tga") == false) {
//		printf("Failed to load: man_normal.png\n");
//		return false;
//	}
//#pragma endregion

#pragma region Dragon
	if (m_dragonMesh.load("./stanford/dragon.obj") == false) {
		printf("Dragon mesh failed!\n");
		return false;
	}

	m_dragonTransform = {
		0.2f, 0, 0, 0,
		0, 0.2f, 0, 0,
		0, 0, 0.2f, 0,
		0, 0, 0, 1
	};

	m_dragonTransform = glm::translate(m_dragonTransform, glm::vec3(-1, 0, -1) * 20.0f);
#pragma endregion

#pragma region Lucy
	if (m_lucyMesh.load("./stanford/lucy.obj") == false) {
		printf("Lucy mesh failed!\n");
		return false;
	}

	m_lucyTransform = {
		0.2f, 0, 0, 0,
		0, 0.2f, 0, 0,
		0, 0, 0.2f, 0,
		0, 0, 0, 1
	};

	m_lucyTransform = glm::translate(m_lucyTransform, glm::vec3(1, 0, -1) * 20.0f);

#pragma endregion

#pragma region Buddha
	if (m_buddhaMesh.load("./stanford/buddha.obj") == false) {
		printf("Buddha mesh failed!\n");
		return false;
	}

	m_buddhaTransform = {
		0.2f, 0, 0, 0,
		0, 0.2f, 0, 0,
		0, 0, 0.2f, 0,
		0, 0, 0, 1
	};

	

	m_buddhaTransform = glm::translate(m_buddhaTransform, glm::vec3(-1, 0, 1) * 20.0f);

#pragma endregion

#pragma region Spear
	if (m_spearMesh.load("./stanford/soulspear.obj", true, true) == false) {
		printf("Spear mesh failed!\n");
		return false;
	}

	m_spearTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	m_spearTransform = glm::translate(m_spearTransform, glm::vec3(-1, 0, 1) * 5.0f);
#pragma endregion

#pragma region Man
	if (m_manMesh.load("./stanford/ironman/gascanis.obj", true, true) == false) {
		printf("Cuppah mesh failed!\n");
		return false;
	}

	m_manTransform = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//m_manTransform = glm::translate(m_manTransform, glm::vec3(-1, 0, 1) * 20.0f);
#pragma endregion

	return true;

}

void GraphicsProjectApp::DrawShaderAndMeshes(glm::mat4 a_projectionMatrix, glm::mat4 a_viewMatrix)
{
	auto pvm = a_projectionMatrix * a_viewMatrix * glm::mat4(0);

#pragma region Quad
	// Bind the shader
	m_textureShader.bind();

	// Bind the transform of the mesh
	pvm = a_projectionMatrix * a_viewMatrix * m_quadTransform; // PVM PROJECTION VIEW MATRIX
	m_textureShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the texture to a location of your choice (0)
	m_textureShader.bindUniform("diffuseTexture", 0);

	// Bind the texture to the specificed location
	m_gridTexture.bind(0);

	m_quadMesh.Draw();
#pragma endregion

#pragma region FlatBunny
	m_bunnyShader.bind();
	pvm = a_projectionMatrix * a_viewMatrix * m_bunnyTransform;
	m_bunnyShader.bindUniform("ProjectionViewModel", pvm);
	m_bunnyShader.bindUniform("MeshFlatColor", glm::vec4(0, 1, 0, 1));

	// Draw bunny mesh
	//m_bunnyMesh.draw();
#pragma endregion

#pragma region Phong Shader
	// Bind the shader
	m_phongShader.bind();

	// Bind the camera position
	m_phongShader.bindUniform("CameraPosition", vec3(glm::inverse(m_viewMatrix)[3]));
	
	// Bind its light
	m_phongShader.bindUniform("AmbientColor", m_ambientLight);
	m_phongShader.bindUniform("LightColor", m_light.color);
	m_phongShader.bindUniform("LightingDirection", m_light.direction);

	// Bind the PVM
	pvm = a_projectionMatrix * a_viewMatrix * m_bunnyTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// BInd the lighting transforms
	m_phongShader.bindUniform("ModelMatrix", m_bunnyTransform);

	m_bunnyMesh.draw();

#pragma endregion


#pragma region Dragon
	// Bind the PVM
	pvm = a_projectionMatrix * a_viewMatrix * m_dragonTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// BInd the lighting transforms
	m_phongShader.bindUniform("ModelMatrix", m_dragonTransform);

	m_dragonMesh.draw();
#pragma endregion

#pragma region Lucy
	// Bind the PVM
	pvm = a_projectionMatrix * a_viewMatrix * m_lucyTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// BInd the lighting transforms
	m_phongShader.bindUniform("ModelMatrix", m_lucyTransform);

	m_lucyMesh.draw();
#pragma endregion

#pragma region Buddha
	// Bind the PVM
	pvm = a_projectionMatrix * a_viewMatrix * m_buddhaTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// BInd the lighting transforms
	m_phongShader.bindUniform("ModelMatrix", m_buddhaTransform);

	m_buddhaMesh.draw();
#pragma endregion

#pragma region Spear
	m_normalMapShader.bind();
	// Bind the PVM
	pvm = a_projectionMatrix * a_viewMatrix * m_spearTransform;
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
	m_normalMapShader.bindUniform("CameraPosition", m_cameras[currentCamera].GetPosition());
	m_normalMapShader.bindUniform("AmbientColor", m_ambientLight);
	m_normalMapShader.bindUniform("LightColor", m_light.color);
	m_normalMapShader.bindUniform("LightingDirection", m_light.direction);

	// Bind the texture to a location of your choice (0)
	m_normalMapShader.bindUniform("ModelMatrix", m_spearTransform);

	//// Bind the texture to the specificed location
	//m_spearTexture.bind(0);

	m_spearMesh.draw();
#pragma endregion

#pragma region Man
	m_normalMapShader.bind();
	// Bind the PVM
	pvm = a_projectionMatrix * a_viewMatrix * m_manTransform;
	m_normalMapShader.bindUniform("ProjectionViewModel", pvm);
	m_normalMapShader.bindUniform("CameraPosition", m_cameras[currentCamera].GetPosition());
	m_normalMapShader.bindUniform("AmbientColor", m_ambientLight);
	m_normalMapShader.bindUniform("LightColor", m_light.color);
	m_normalMapShader.bindUniform("LightingDirection", m_light.direction);

	// Bind the texture to a location of your choice (0)
	m_normalMapShader.bindUniform("ModelMatrix", m_manTransform);

	//// Bind the texture to the specificed location
	//m_spearTexture.bind(0);

	m_manMesh.draw();
#pragma endregion
}

void GraphicsProjectApp::IMGUI_Logic()
{
	ImGui::Begin("Scene Light Settings");
	ImGui::DragFloat3("Sunlight Direction", &m_light.direction[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("Sunlight Color", &m_light.color[0], 0.1f, 0.0f, 2.0f);
	ImGui::End();

	ImGui::Begin("Dragon Transform");
	ImGui::DragFloat3("Position", &m_dragonTransform[3][0], 0.1f, -40.0f, 40.0f);

	ImGui::End();

	ImGui::Begin("Bunny Transform");
	ImGui::DragFloat3("Position", &m_bunnyTransform[3][0], 0.1f, -40.0f, 40.0f);

	ImGui::End();

	ImGui::Begin("Lucy Transform");
	ImGui::DragFloat3("Position", &m_lucyTransform[3][0], 0.1f, -40.0f, 40.0f);

	ImGui::End();

	ImGui::Begin("Buddha Transform");
	ImGui::DragFloat3("Position", &m_buddhaTransform[3][0], 0.1f, -40.0f, 40.0f);

	ImGui::End();

	ImGui::Begin("Spear Transform");
	ImGui::DragFloat3("Position", &m_spearTransform[3][0], 0.1f, -40.0f, 40.0f);

	ImGui::End();

	ImGui::Begin("Man Transform");
	ImGui::DragFloat3("Position", &m_manTransform[3][0], 0.1f, -40.0f, 40.0f);

	ImGui::End();
}

float GraphicsProjectApp::Rotation(glm::mat4 &mat, float rot, glm::vec3 axis)
{
	mat = glm::rotate(mat, rot, axis);
	return rot;
}


