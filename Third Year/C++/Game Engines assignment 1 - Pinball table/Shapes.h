#ifndef Shapes_H
#define Shapes_H
#include "PhysicsEngine.h"
#include "Utilities.h"
namespace PhysicsEngine
{
	

class Box : public Actor
	{
		PxVec3 dimensions;
		PxReal density;
		PxShape* shape;
		shapeColours *colours;

	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Box(PxTransform pose=PxTransform(PxIdentity), PxVec3 _dimensions=PxVec3(.5f,.5f,.5f), PxReal _density=1.f,
			const PxVec3& _color=PxVec3(.9f,0.f,0.f)) 
			: Actor(pose, _color), dimensions(_dimensions), density(_density)
		{ 
		}
		~Box()
		{
			delete colours;
		}

		virtual void Create();

		PxRigidDynamic* Get() ;
		

		//get a single shape
		PxShape* GetShape();
	};

	class Plane : public Actor
	{
		PxVec3 normal;
		PxReal distance;
		shapeColours *colours;

	public:
		//A plane with default paramters: XZ plane centred at (0,0,0)
		Plane(PxVec3 _normal=PxVec3(0.f, 1.f, 0.f), PxReal _distance=0.f,
			const PxVec3& color=PxVec3(.5f,.5f,.5f)) 
			: Actor(PxTransform(PxIdentity), color), normal(_normal), distance(_distance)
		{
		}
		~Plane()
		{
			delete colours;
		}

		virtual void Create();
	};
	class Sphere : public Actor
	{
		PxReal radius;
		PxReal density;
		PxMaterial* mat;
		shapeColours *colours;
		PxShape* shape;

	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Sphere(PxTransform pose=PxTransform(PxIdentity), PxReal _radius=.5f, PxReal _density=1.f,
			const PxVec3& _color=PxVec3(.9f,0.f,0.f), PxMaterial *_mat = CreateMaterial(0.0,0.0,0.0) ) 
			: Actor(pose, _color), radius(_radius), density(_density), mat(_mat)
		{ 
		}
		~Sphere()
		{
			delete colours;
		}
		virtual void Create()
		{
			colours = new shapeColours(1);
			PxRigidDynamic* sphere = GetPhysics()->createRigidDynamic(pose);
			shape = sphere->createShape(PxSphereGeometry(radius), *mat);
			PxRigidBodyExt::setMassAndUpdateInertia(*sphere, density);
			colours->addColour(color);
			colours->SetShapeColour(0,0);
			actor = sphere;
			actor->userData = colours; //pass color parameter to renderer
		}

		PxRigidDynamic* Get() 
		{
			return (PxRigidDynamic*)actor; 
		}

		PxActor* GetActor()
		{
			return actor;
		}

		PxShape* GetShape()
		{
			return shape;
		}
	};

	class Capsule : public Actor
	{
		PxVec2 dimensions;
		PxReal density;
		PxShape* shape;
		shapeColours *colours;
	public:
		
	//A capsule with default dimensions of 1 x1 
		Capsule(PxTransform pose=PxTransform(PxIdentity), PxVec2 _dimensions=PxVec2(1.f,1.f), PxReal _density=1.f,
			const PxVec3& _color=PxVec3(.9f,0.f,0.f)) 
			: Actor(pose, _color), dimensions(_dimensions), density(_density)
		{
		}
		~Capsule()
		{
			delete colours;
		}

		virtual void Create();
		PxRigidDynamic* Get() 
		{
			return (PxRigidDynamic*)actor; 
		}

		PxShape* GetShape()
		{
			return shape;
		}
	};
}
#endif