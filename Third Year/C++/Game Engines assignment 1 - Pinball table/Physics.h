#pragma once

#include "PhysicsEngine.h"

namespace PhysicsEngine
{
	using namespace std;
	

	static const PxVec3 pyramid_verts[] = {PxVec3(0,1,0),PxVec3(1,0,0),PxVec3(-1,0,0),PxVec3(0,0,1),PxVec3(0,0,-1)};

	///The Pyramid class demonstrating convex meshes
	class Pyramid : public Actor
	{
		PxReal density;

	public:
		//constructor
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal _density=1.f,
			const PxVec3& _color=PxVec3(.9f,0.f,0.f))
			: Actor(pose, _color), density(_density)
		{
		}

		//mesh cooking (preparation)
		PxConvexMesh* CookMesh();

		virtual void Create();

		PxRigidDynamic* Get() ;
	};

}
