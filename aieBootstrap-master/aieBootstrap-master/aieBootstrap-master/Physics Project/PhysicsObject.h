#pragma once
#include <glm/glm.hpp>

// This is a pure abstract class. It will be used as a base for the derived classes.

enum class ShapeType {
	JOINT = -1,
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
public:
	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep) = 0;

	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};

	virtual bool IsInside(glm::vec2 a_point) = 0;

	ShapeType GetShapeID() { return ShapeType(m_shapeID); }

	bool IsKinematic() { return m_isKinematic; }
	bool SetKinematic(bool a_state) { return m_isKinematic = a_state; }
	float GetElasticity() { return m_elasticity; }

	// Keep to 1 for realism
	float SetElasticity(float a_new) { return m_elasticity = a_new; }

	float SetRotation(float a_rotate) { return m_rotation = a_rotate; }

	void SetActive(bool _set) { m_active = _set; }
	void SetVisible(bool _set) { m_visible = _set; }
	bool IsActive() { return m_active; }
	bool IsVisible() { return m_visible; }

	void SetProtectionFromDelete(bool _set) { m_protectedFromDelete = _set; }
	bool IsProtectedFromDelete() { return m_protectedFromDelete; }
protected:
	ShapeType m_shapeID = ShapeType::SHAPE_COUNT;

	float m_rotation;
	bool m_isKinematic;
	float m_elasticity;

	bool m_active = true;
	bool m_visible = true;

	bool m_protectedFromDelete = false;

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
};
