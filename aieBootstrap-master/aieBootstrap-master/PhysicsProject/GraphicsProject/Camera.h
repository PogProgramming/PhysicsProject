#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	~Camera() {}

	void Update(float deltaTime);
	glm::vec3 GetPosition() { return m_position; }

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float a_width, float a_height);


private:
	float m_theta; // in degrees
	float m_phi; // in degrees
	glm::vec3 m_position;

	float m_lastMouseX, m_lastMouseY;
};

