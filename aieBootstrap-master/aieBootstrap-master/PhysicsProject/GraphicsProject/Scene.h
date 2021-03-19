#pragma once
#include <list>
#include <vector>
#include <glm/glm.hpp>

class Camera;
class Instance;

const int MAX_LIGHTS = 4;

struct Light {

	Light() {
		m_direction = glm::vec3(1);
		m_color = glm::vec3(1);
	}
	Light(glm::vec3 a_pos, glm::vec3 a_color, float a_intensity) {
		m_direction = a_pos;
		m_color = a_color * a_intensity;
	}

	glm::vec3 m_direction;
	glm::vec3 m_color;
};

class Scene
{
public:

	Scene(std::vector<Camera*> a_cameras, glm::vec2 a_windowSize, Light& a_light, glm::vec3 a_ambientLight);
	~Scene();

	void AddInstance(Instance* a_instance);
	void Draw();

	int currentCam = 0;
	Camera* GetCamera() { return m_camera; }
	Camera* GetCurrentCam() { return m_cameras[currentCam]; }
	glm::vec2 GetWindowSize() { return m_windowSize; }
	Light& GetLight() { return m_light; }
	glm::vec3 GetAmbientLight() { return m_ambientLight; }

	int GetNumLights() { return (int)m_pointLights.size(); }
	glm::vec3* GetPointLightPositions() { return &m_pointLightPositions[0]; }
	glm::vec3* GetPointLightColors() { return &m_pointLightColors[0]; }

	std::vector<Light>& GetPointLights() { return m_pointLights; }
	std::vector<Instance*> GetInstances() { return m_instances; }

	std::vector<Instance*> m_instances;
	std::vector<Camera*> m_cameras;

protected:
	Camera* m_camera;
	glm::vec2 m_windowSize;
	Light m_light;
	Light m_sunLight;
	std::vector<Light> m_pointLights;

	glm::vec3 m_ambientLight;

	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColors[MAX_LIGHTS];
};

