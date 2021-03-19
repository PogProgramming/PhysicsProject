#include "Instance.h"
#include "Scene.h"
#include "OBJMesh.h"

#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"

#include <Texture.h>
#include <Application.h>
#include <glm/ext.hpp>

Instance::Instance(glm::mat4 a_transform, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader)
	: m_transform(a_transform), m_mesh(a_mesh), m_shader(a_shader)
{
}

Instance::Instance(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader)
	: m_mesh(a_mesh), m_shader(a_shader)
{
	m_pos = a_position;
	m_rot = a_eulerAngles;
	m_scale = a_scale;

	m_transform = MakeTransform(m_pos, m_rot, m_scale);
}

void Instance::Draw(Scene* a_scene)
{
	m_shader->bind();

	auto pvm = a_scene->GetCurrentCam()->GetProjectionMatrix(a_scene->GetWindowSize().x,
		a_scene->GetWindowSize().y) * a_scene->GetCurrentCam()->GetViewMatrix() * m_transform;
	//bind the transform
	m_shader->bindUniform("ProjectionViewModel", pvm);
	m_shader->bindUniform("CameraPosition", a_scene->GetCurrentCam()->GetPosition());
	m_shader->bindUniform("AmbientColor", a_scene->GetAmbientLight());
	m_shader->bindUniform("LightColor", a_scene->GetLight().m_color);
	m_shader->bindUniform("LightDirection", a_scene->GetLight().m_direction);
	m_shader->bindUniform("ModelMatrix", m_transform);

	int numLights = a_scene->GetNumLights();
	m_shader->bindUniform("numLights", numLights);
	m_shader->bindUniform("PointLightPosition", numLights, a_scene->GetPointLightPositions());
	m_shader->bindUniform("PointLightColor", numLights, a_scene->GetPointLightColors());

	// Draw the mesh
	m_mesh->draw();
}

glm::mat4 Instance::MakeTransform(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale)
{
	return glm::translate(glm::mat4(1), a_position)
		* glm::rotate(glm::mat4(1), glm::radians(a_eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1), glm::radians(a_eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1), glm::radians(a_eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), a_scale);
}
