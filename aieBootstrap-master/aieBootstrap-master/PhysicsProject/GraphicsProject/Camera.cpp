#include "Camera.h"
#include <glm/ext.hpp>
#include <Input.h>

Camera::Camera()
{
	m_position = glm::vec3(0);
	m_phi = 0;
	m_theta = 0;
}

void Camera::Update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	//Calculates the forwards and right axes and the up axis for the camera
	glm::vec3 forward(cos(phiR) * glm::cos(thetaR), glm::sin(phiR), glm::cos(phiR) * glm::sin(thetaR));
	glm::vec3 right(-glm::sin(thetaR), 0, glm::cos(thetaR));
	glm::vec3 up(0, 1, 0);

#pragma region InputMovement
	if (input->isKeyDown(aie::INPUT_KEY_X)) {
		m_position += up * deltaTime * moveSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_Z)) {
		m_position -= up * deltaTime * moveSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_A)) {
		m_position -= right * deltaTime * moveSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_D)) {
		m_position += right * deltaTime * moveSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		m_position += forward * deltaTime * moveSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		m_position -= forward * deltaTime * moveSpeed;
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT)) {
		shifting = true;
		moveSpeed = 6.0f;
	}
	if (input->isKeyUp(aie::INPUT_KEY_LEFT_SHIFT) && shifting) {
		moveSpeed = 1.0f;
		shifting = false;
	}
#pragma endregion

#pragma region InputSettings

	// Get the current position of the mouse coordinates
	float mX = input->getMouseX();
	float mY = input->getMouseY();
	const float turnSpeed = glm::radians(180.0f) * 2.0f;

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT)) {
		m_theta += turnSpeed * (mX - m_lastMouseX) * deltaTime;
		m_phi += turnSpeed * (mY - m_lastMouseY) * deltaTime;
	}

	m_lastMouseX = mX;
	m_lastMouseY = mY;

#pragma endregion
	

}

glm::mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	glm::vec3 forward(cos(phiR) * glm::cos(thetaR), glm::sin(phiR), glm::cos(phiR) * glm::sin(thetaR));
	return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix(float a_width, float a_height)
{
	return glm::perspective(glm::pi<float>() * 0.25f,
		a_width / a_height, 0.1f, 1000.0f);
}
