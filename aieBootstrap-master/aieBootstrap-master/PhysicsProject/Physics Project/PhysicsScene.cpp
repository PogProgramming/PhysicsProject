
#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <list>
#include "Rigidbody.h"
#include <iostream>
#include "Sphere.h"
#include "Plane.h"
#include "Input.h"
#include "Box.h"


// Function pointer array for handling our collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] = {
	PhysicsScene::Plane2Plane,
	PhysicsScene::Plane2Sphere,
	PhysicsScene::Plane2Box,

	PhysicsScene::Sphere2Plane,
	PhysicsScene::Sphere2Sphere,
	PhysicsScene::Sphere2Box,

	PhysicsScene::Box2Plane,
	PhysicsScene::Box2Sphere,
	PhysicsScene::Box2Box
};

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors) {
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor, bool a_forceDelete)
{
	if (!a_actor->IsProtectedFromDelete() || a_forceDelete == true) {
		auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);

		if (it != m_actors.end()) {
			m_actors.erase(it);
		}
	}
}

void PhysicsScene::Update(float dt)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep) {
		for (auto pActor : m_actors) {
			if(pActor->IsActive()) pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		CheckForCollision();
	}
}

void PhysicsScene::Draw()
{
	if (m_actors.size() > 0) {
		for (auto pActor : m_actors) {
			if(pActor->IsVisible()) pActor->MakeGizmo();
		}
	}
}

void PhysicsScene::DebugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		std::cout << count << " : ";
		pActor->Debug();
		count++;
	}
}

void PhysicsScene::CheckForCollision()
{
	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* objOuter = m_actors[outer];
			PhysicsObject* objInner = m_actors[inner];
			int shapeID_out = (int)objOuter->GetShapeID();
			int shapeID_in = (int)objInner->GetShapeID();

			// this will check to ensure we do not include the joints
			if (shapeID_in >= 0 && shapeID_out >= 0)
			{
				// Uses our function pointers (fn)
				int functionIndex = (shapeID_out * (int)ShapeType::SHAPE_COUNT) + shapeID_in;
				fn collisionFunctionPtr = collisionFunctionArray[functionIndex];
				if (collisionFunctionPtr != nullptr)
				{
					// Check if the collision occurs
					collisionFunctionPtr(objOuter, objInner);
				}
			}
		}
	}
}

void PhysicsScene::ApplyContactForces(Rigidbody* a_actor1, Rigidbody* a_actor2, glm::vec2 a_collisionNorm, float a_pen)
{
	if ((a_actor1 && a_actor1->IsTrigger()) || (a_actor2 && a_actor2->IsTrigger()))
	{
		return;
	}

	float body2Mass = a_actor2 ? a_actor2->GetMass() : INT_MAX;
	float body1Factor = body2Mass / (a_actor1->GetMass() + body2Mass);

	if (a_actor1 != nullptr)
	{
		a_actor1->SetPosition(a_actor1->GetPosition() - body1Factor * a_collisionNorm * a_pen);
	}

	if (a_actor2)
	{
		a_actor2->SetPosition(a_actor2->GetPosition() + (1 - body1Factor) * a_collisionNorm * a_pen);
	}
}

bool PhysicsScene::Plane2Plane(PhysicsObject*, PhysicsObject*)
{
	return false;
}

bool PhysicsScene::Plane2Sphere(PhysicsObject* objPlane, PhysicsObject* objSphere)
{
	return Sphere2Plane(objSphere, objPlane);
}

bool PhysicsScene::Plane2Box(PhysicsObject* objPlane, PhysicsObject* objBox)
{
	Plane* plane = dynamic_cast<Plane*>(objPlane);
	Box* box = dynamic_cast<Box*>(objBox);

	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;

		// Get a representative point on the plane
		glm::vec2 planeOrigin = plane->GetNormal() * plane->GetDistance();

		// Check all the corners for a collision with the plane
		for (float x = -box->GetExtents().x; x < box->GetWidth(); x += box->GetWidth())
		{
			for (float y = -box->GetExtents().y; y < box->GetWidth(); y += box->GetWidth())
			{
				// Get the position of the corners in world space
				glm::vec2 p = box->GetPosition() + x * box->GetLocalX() + y * box->GetLocalY();
				float distFromPlane = glm::dot(p - planeOrigin, plane->GetNormal());

				// this is the total velocity of the points in world space
				glm::vec2 displacement = x * box->GetLocalX() + y * box->GetLocalY();
				glm::vec2 pointVelocity = box->GetVelocity() + box->GetAngularVelocity() *
					glm::vec2(-displacement.y, displacement.x);

				// this is the amount of the point velocity into the plane
				float velocityIntoPlane = glm::dot(pointVelocity, plane->GetNormal());

				// Moving further in, we need to resolve the collision
				if (distFromPlane < 0 && velocityIntoPlane <= 0)
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}
		// If we hit it will normally result as one or two corners touching a plane...
		if (numContacts > 0)
		{
			plane->ResolveCollision(box, contact / (float)numContacts);
			return true;
		}
	}

	return false;
}

bool PhysicsScene::Sphere2Plane(PhysicsObject* objSphere, PhysicsObject* objPlane)
{
	Sphere* sphere = dynamic_cast<Sphere*>(objSphere);
	Plane* plane = dynamic_cast<Plane*>(objPlane);

	// If they have a value continue below
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), collisionNormal) - plane->GetDistance();
		float intersection = sphere->GetRadius() - sphereToPlane;
		float velocityOutOfPlane = glm::dot(sphere->GetVelocity(), collisionNormal);
		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			glm::vec2 contact = sphere->GetPosition() + (collisionNormal * -sphere->GetRadius());
			plane->ResolveCollision(sphere, contact);
			return true;
		}
	}

	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject* objSphere, PhysicsObject* otherObjSphere)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(objSphere);
	Sphere* sphere2 = dynamic_cast<Sphere*>(otherObjSphere);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float dist = glm::distance(sphere1->GetPosition(), sphere2->GetPosition());

		float penetration = sphere1->GetRadius() + sphere2->GetRadius() - dist;

		if (penetration > 0)
		{
			sphere1->ResolveCollision(sphere2, 0.5f * (sphere1->GetPosition() + sphere2->GetPosition()), nullptr, penetration);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::Sphere2Box(PhysicsObject* objSphere, PhysicsObject* objBox)
{
	Sphere* sphere = dynamic_cast<Sphere*>(objSphere);
	Box* box = dynamic_cast<Box*>(objBox);

	if (box != nullptr && sphere != nullptr)
	{
		// Transform the circle into the box's coordinate space
		glm::vec2 circlePosWorld = sphere->GetPosition() - box->GetPosition();
		glm::vec2 circlePosBox = glm::vec2(glm::dot(circlePosWorld, box->GetLocalX()),
			glm::dot(circlePosWorld, box->GetLocalY()));

		// Find the closest point to the circle's centre on the box
		// by clamping the coordinates in the box-space to the box's extents
		glm::vec2 closestPointOnTheBox = circlePosBox;
		glm::vec2 extents = box->GetExtents();
		if (closestPointOnTheBox.x < -extents.x) closestPointOnTheBox.x = -extents.x;
		if (closestPointOnTheBox.x > extents.x) closestPointOnTheBox.x = extents.x;

		if (closestPointOnTheBox.y < -extents.y) closestPointOnTheBox.y = -extents.y;
		if (closestPointOnTheBox.y > extents.y) closestPointOnTheBox.y = extents.y;

		glm::vec2 closestPointOnBoxWorld = box->GetPosition() + closestPointOnTheBox.x * box->GetLocalX()
			+ closestPointOnTheBox.y * box->GetLocalY();

		glm::vec2 circleToBox = sphere->GetPosition() - closestPointOnBoxWorld;

		float penetration = sphere->GetRadius() - glm::length(circleToBox);
		if (penetration > 0)
		{
			glm::vec2 direction = glm::normalize(circleToBox);
			glm::vec2 contact = closestPointOnBoxWorld;
			box->ResolveCollision(sphere, contact, &direction, penetration);
		}
	}

	return false;
}

bool PhysicsScene::Box2Plane(PhysicsObject* objBox, PhysicsObject* objPlane)
{
	return Plane2Box(objPlane, objBox);
}

bool PhysicsScene::Box2Sphere(PhysicsObject* objBox, PhysicsObject* objSphere)
{
	return Sphere2Box(objSphere, objBox);
}

bool PhysicsScene::Box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec2 norm(0, 0);
		glm::vec2 contact(0, 0);
		float pen = 0;
		int numContacts = 0;
		box1->CheckBoxCorners(*box2, contact, numContacts, pen, norm);
		if (box2->CheckBoxCorners(*box1, contact, numContacts, pen, norm))
		{
			norm = -norm;
		}
		if (pen > 0)
		{
			box1->ResolveCollision(box2, contact / float(numContacts), &norm, pen);
		}
		return true;
	}
	return false;
}