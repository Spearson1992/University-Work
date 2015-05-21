#include "Physics.h"
#include "Shapes.h"

namespace PhysicsEngine
{
#pragma region Pyramid Class Function Definitions
	PxConvexMesh* Pyramid::CookMesh()
			{
				PxConvexMeshDesc convexDesc;
				convexDesc.points.count     = sizeof(pyramid_verts)/sizeof(PxVec3);
				convexDesc.points.stride    = sizeof(PxVec3);
				convexDesc.points.data      = pyramid_verts;
				convexDesc.flags            = PxConvexFlag::eCOMPUTE_CONVEX;
				convexDesc.vertexLimit      = 256;

				PxDefaultMemoryOutputStream stream;

				if(!GetCooking()->cookConvexMesh(convexDesc, stream))
					throw new Exception("Pyramid::CookMesh, cooking failed.");

				PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

				return GetPhysics()->createConvexMesh(input);
			}
	void Pyramid::Create()
	{
		PxRigidDynamic* pyramid = GetPhysics()->createRigidDynamic(pose);
		pyramid->createShape(PxConvexMeshGeometry(CookMesh()), *GetDefaultMaterial());
		PxRigidBodyExt::setMassAndUpdateInertia(*pyramid, density);
		actor = pyramid;
		//actor->userData = &color; //pass color parameter to renderer
	}
	PxRigidDynamic* Pyramid::Get() 
	{
		return (PxRigidDynamic*)actor; 
	}
#pragma endregion

#pragma region Capsule Class function definitions
		void Capsule::Create()
		{
			colours = new shapeColours(1);
			PxRigidDynamic* capsule = GetPhysics()->createRigidDynamic(pose);
			shape = capsule->createShape(PxCapsuleGeometry(dimensions.x, dimensions.y), *GetDefaultMaterial());
			PxRigidBodyExt::setMassAndUpdateInertia(*capsule, density);
			colours->addColour(color);
			colours->SetShapeColour(0,0);
			actor = capsule;
			actor->userData = colours; //pass color parameter to renderer
		}

#pragma endregion

#pragma region Box Class function definitions
		void Box::Create()
		{
			colours = new shapeColours(1);
			PxRigidDynamic* box = GetPhysics()->createRigidDynamic(pose);
			shape = box->createShape(PxBoxGeometry(dimensions), *GetDefaultMaterial());
			PxRigidBodyExt::setMassAndUpdateInertia(*box, density);
			colours->addColour(color);
			colours->SetShapeColour(0,0);
			actor = box;
			actor->userData = colours; //pass color parameter to renderer
		}

		PxRigidDynamic* Box::Get() 
		{
			return (PxRigidDynamic*)actor; 
		}

		//get a single shape
		PxShape* Box::GetShape()
		{
			return shape;
		}
#pragma endregion
		
#pragma region Plane Class function definitions
		void Plane::Create()
		{
			colours = new shapeColours(1);
			PxRigidStatic* plane = PxCreatePlane(*GetPhysics(), PxPlane(normal, distance), *GetDefaultMaterial());
			actor = plane;
			colours->addColour(color);
			colours->SetShapeColour(0,0);
			actor->userData = colours; //pass color parameter to renderer
		}
#pragma endregion

}