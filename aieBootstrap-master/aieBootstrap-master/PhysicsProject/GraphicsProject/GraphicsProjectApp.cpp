#include "GraphicsProjectApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include "Scene.h"
#include "Instance.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

float angle = 0.0f;

GraphicsProjectApp::GraphicsProjectApp() : m_ambientLight(), m_projectionMatrix(), m_quadTransform(), m_viewMatrix()
{

}

GraphicsProjectApp::~GraphicsProjectApp() {

}

bool GraphicsProjectApp::startup() {

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	Light light;
	light.m_color = { 1, 1, 1 };
	light.m_direction = { 1, -1, 1 };

	return LoadShaderAndMeshLogic(light);
}

void GraphicsProjectApp::shutdown() {

	Gizmos::destroy();
	delete m_scene;
}

void GraphicsProjectApp::update(float deltaTime) {

	aie::Input* input = aie::Input::getInstance();

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

	// Stop updating other than active camera
	if (m_scene->currentCam == 0)
		m_scene->GetCurrentCam()->Update(deltaTime);

	float time = getTime();
	m_scene->GetLight().m_direction = glm::normalize(glm::vec3(glm::cos(time * m_directionalRotSpeed), glm::sin(time * m_directionalRotSpeed), 0)) + m_directionalLightPos;

	//Gizmo directional light
	Gizmos::addSphere(m_directionalOrbitRadius * m_scene->GetLight().m_direction, 0.25, 8, 8, glm::vec4(m_scene->GetLight().m_color, 1));

	//gizmo for point light 1
	Gizmos::addSphere(m_scene->GetPointLightPositions()[0], 0.25, 8, 8, glm::vec4(m_scene->GetPointLights()[0].m_color, 1));
	//gizmo for point light 2
	Gizmos::addSphere(m_scene->GetPointLightPositions()[1], 0.25, 8, 8, glm::vec4(m_scene->GetPointLights()[1].m_color, 1));

	//if (input->wasKeyPressed(aie::INPUT_KEY_UP)) {
	//	if (currentCamera < m_cameras.size() - 1)
	//		currentCamera++;
	//}

	//if (input->wasKeyPressed(aie::INPUT_KEY_DOWN)) {
	//	if (currentCamera > 0)
	//		currentCamera--;
	//}

	// quit if we press escape
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

}

void GraphicsProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	glm::mat4 projectionMatrix = m_scene->GetCurrentCam()->GetProjectionMatrix(getWindowWidth(), (float)getWindowHeight());

	glm::mat4 viewMatrix = m_scene->GetCurrentCam()->GetViewMatrix();

	// DrawShaderAndMeshes(projectionMatrix, viewMatrix);
	m_scene->Draw();

	Gizmos::draw(projectionMatrix * viewMatrix);
}

bool GraphicsProjectApp::LoadShaderAndMeshLogic(Light a_light)
{

#pragma region Phong Shader
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if (m_phongShader.link() == false) {
		printf("Phong Shader had an error: %s\n", m_phongShader.getLastError());
		return false;
	}

#pragma endregion

#pragma region Texture Shader
	//m_textureShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	//m_textureShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	//if (m_textureShader.link() == false) {
	//	printf("Textured Shader had an error: %s\n", m_textureShader.getLastError());
	//	return false;
	//}
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
	//m_simpleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");

	//// Load the fragment shader from a file
	//m_simpleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	//if (!m_simpleShader.link()) {
	//	printf("Simple shader had an error: %s\n", m_simpleShader.getLastError());
	//	return false;
	//}

	//Mesh::Vertex vertices[4];
	//vertices[0].position = { -0.5, 0.f, 0.5f, 1.f };
	//vertices[1].position = { 0.5, 0.f, 0.5f, 1.f };
	//vertices[2].position = { -0.5, 0.f, -0.5f, 1.f };
	//vertices[3].position = { 0.5, 0.f, -0.5f, 1.f };

	//unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

	//m_quadMesh.InitialiseQuad();

	//// We will make the quad 10 units by 10 units
	//m_quadTransform = {
	//	10, 0, 0, 0,
	//	0, 10, 0, 0,
	//	0, 0, 10, 0,
	//	0, 0, 0, 1
	//};

	//m_quadTransform = glm::rotate(m_quadTransform, angle, glm::vec3(1));
#pragma endregion

#pragma region GridLogic
	//if (m_gridTexture.load("./textures/numbered_grid.tga") == false) {
	//	printf("Failed to load: numbered_grid.tga\n");
	//	return false;
	//}
#pragma endregion

#pragma region Dragon
	if (m_dragonMesh.load("./stanford/dragon.obj") == false) {
		printf("Dragon mesh failed!\n");
		return false;
	}
#pragma endregion

#pragma region Lucy
	if (m_lucyMesh.load("./stanford/lucy.obj") == false) {
		printf("Lucy mesh failed!\n");
		return false;
	}

#pragma endregion

#pragma region Buddha
	if (m_buddhaMesh.load("./stanford/buddha.obj") == false) {
		printf("Buddha mesh failed!\n");
		return false;
	}
#pragma endregion

#pragma region Spear
	if (m_spearMesh.load("./stanford/soulspear.obj", true, true) == false) {
		printf("Spear mesh failed!\n");
		return false;
	}
#pragma endregion

#pragma region GasCan
	if (m_canMesh.load("./stanford/ironman/gascanis.obj", true, true) == false) {
		printf("Cuppah mesh failed!\n");
		return false;
	}
#pragma endregion

#pragma region Add Instances
	m_cameras.push_back(new Camera(glm::vec3(-5, 0, 0))); // dynamic
	m_cameras.push_back(new Camera(glm::vec3(0, 0, 0)));  //static 
	m_cameras.push_back(new Camera(glm::vec3(5, 0, 0)));  //static 
	m_cameras.push_back(new Camera(glm::vec3(0, 10, 0))); //static 

	m_scene = new Scene(m_cameras, glm::vec2(getWindowWidth(), getWindowHeight()), a_light, glm::vec3(0.25f));

	// Add meshes
	m_scene->AddInstance(new Instance(glm::vec3(5, 0, 5), glm::vec3(0, 30, 0), glm::vec3(0.1f), &m_canMesh, &m_normalMapShader));
	m_scene->AddInstance(new Instance(glm::vec3(0, 0, 5), glm::vec3(0, 30, 0), glm::vec3(1), &m_dragonMesh, &m_phongShader));
	m_scene->AddInstance(new Instance(glm::vec3(0, 0, 0), glm::vec3(0, 30, 0), glm::vec3(1), &m_spearMesh, &m_normalMapShader));

	// Add lights
	m_scene->GetPointLights().push_back(Light(vec3(5, 3, 0), vec3(1, 0, 0), 50));
	m_scene->GetPointLights().push_back(Light(vec3(-5, 3, 0), vec3(0, 1, 0), 50));


#pragma endregion
	return true;

}

void GraphicsProjectApp::IMGUI_Logic()
{
	ImGui::Begin("Scene Directional Light Settings");
	ImGui::DragFloat3("Light Color", &m_scene->GetLight().m_color[0], 0.1f, 0.0f, 2.0f);
	ImGui::DragFloat("Light Rotation Speed", &m_directionalRotSpeed, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Orbit Radius", &m_directionalOrbitRadius, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat3("Light Position", &m_directionalLightPos[0], 0.1f, -50.0f, 50.0f);
	ImGui::End();

	ImGui::Begin("Man Transform");
	ImGui::DragFloat3("Position", &m_scene->GetInstances()[0]->m_transform[3][0], 0.1f, -40.0f, 40.0f);
	ImGui::End();

	ImGui::Begin("Dragon Transform");
	ImGui::DragFloat3("Position", &m_scene->GetInstances()[1]->m_transform[3][0], 0.1f, -40.0f, 40.0f);
	ImGui::End();

	ImGui::Begin("Spear Transform");
	ImGui::DragFloat3("Position", &m_scene->GetInstances()[2]->m_transform[3][0], 0.1f, -40.0f, 40.0f);
	ImGui::End();

	//ImGui::Begin("Green Light");
	//ImGui::DragFloat3("Position", &m_scene->GetPointLightPositions(), 0.1f, -40.0f, 40.0f);
	//ImGui::End();


}


