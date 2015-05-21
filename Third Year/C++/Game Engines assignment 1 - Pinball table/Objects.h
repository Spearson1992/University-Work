#ifndef Objects_H
#define Objects_H


#include "PhysicsEngine.h"
#include "Joints.h"
#include "Utilities.h"
#include "Shapes.h"
namespace PhysicsEngine
{
	class Table : public Actor
	{
		PxRigidStatic *pinballTable;
		shapeColours *colours;
		

	public:
		Table(PxTransform pose=PxTransform(PxIdentity),	const PxVec3& _color=PxVec3(.2f,0.1f,0.2f));
		~Table();
		void Create();
		PxRigidStatic* GetStatic();
		inline shapeColours* const GetShapeColours()
		{
			return colours;
		}
	};

	class Plunger
	{
		Box *plungerTop;
		PxReal plungerForce;
		PxReal timeMult;
	public:
		Plunger(Scene *scene, Table *attachment, PxVec3 &dimensions, PxReal stiffness , PxReal damping, PxTransform & pose);
		void PushDown(PxReal deltaTime);
		void Create()
		{

		}
		void ClearForce()
		{
			timeMult = 0;
		}
	};

	

	class Flipper : public Actor
	{
		PxRigidDynamic *flipper;
		Capsule *flipperBody;
		RevoluteJoint *joint;
	public:
		Flipper(Scene *scene,
				Table *attachment,
				PxVec2 &dimensions = PxVec2(1.0f,1.0f),
				PxReal density = 1.0f,
				const PxTransform &pose = PxTransform(PxIdentity),
				PxTransform flipperLocation = PxTransform(PxVec3(0.0f)),
				PxTransform jointLocation  = PxTransform(PxVec3(0.0f)),
				PxReal lowerJointLimit = 0.0f,
				PxReal upperJointLimit = 360.0f,
				PxVec3 & colour = PxVec3(0.0f,0.5f,0.0f));
		void Create();

		void Flip(bool isRight);

		void ReleaseFlip(bool Isright);


	};

	class Ball : public Actor
	{
		bool inPlay;
		bool inScene;
		bool needsReset;
		bool launched;
		PxReal radius;
		PxReal density;
		PxMaterial* material;
		shapeColours *colours;
		PxShape* shape;

		public:
			Ball(PxTransform pose=PxTransform(PxIdentity), PxReal _radius=.5f, PxReal _density=1.f,
			const PxVec3& _color=PxVec3(.9f,0.f,0.f), PxMaterial *_mat = CreateMaterial(0.0,0.0,0.0), bool _inPlay = false,
			bool _inScene = false, bool _needsReset = false,bool _launched = false) 
			: Actor(pose, _color), radius(_radius), density(_density), material(_mat), inPlay(_inPlay),
			inScene(_inScene), needsReset(_needsReset), launched(_launched)
			{
				
			};
			~Ball()
			{
				delete colours;
			}
			virtual void Create()
			{
				colours = new shapeColours(1);
				PxRigidDynamic* sphere = GetPhysics()->createRigidDynamic(pose);
				shape = sphere->createShape(PxSphereGeometry(radius), *material);
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

			//Returns whether the ball is in play or not
			bool IsInPlay()
			{
				return inPlay;
			}

			//Used for removing and adding a ball to play
			//Also sets needsReset flag to true if inPLay is set to false
			//And reset flag to false if inPlay is true
			void SetInPlayStatus(bool _inPlay)
			{
				inPlay = _inPlay;
			}

			//returns true if ball is still in play
			bool GetInPlayStatus()
			{
				return inPlay;
			}

			void SetSceneStatus(bool _inScene)
			{
				inScene = _inScene;
			}

			bool GetSceneStatus()
			{
				return inScene;
			}

			void SetResetStatus(bool _needsReset)
			{
				needsReset = _needsReset;
			}

			bool GetResetStatus()
			{
				return needsReset;
			}

			void SetLaunchStatus(bool _launched)
			{
				launched = _launched;
			}

			bool GetLaunchedStatus()
			{
				return launched;
			}
	};

}



#endif