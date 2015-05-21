#include "PhysicsEngine.h"
#include "Externals.h"

namespace PhysicsEngine
{
	using namespace physx;
	using namespace std;

	//default error and allocator callbacks
	PxDefaultErrorCallback gDefaultErrorCallback;
	PxDefaultAllocator gDefaultAllocatorCallback;

	//PhysX objects
	PxFoundation* foundation = 0;
	debugger::comm::PvdConnection* vd_connection = 0;
	PxPhysics* physics = 0;
	PxCooking* cooking = 0;
	PxMaterial* default_material = 0;

	///PhysX functions
	void PxInit()
	{
		//foundation
		if (!foundation)
			foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);

		if(!foundation)
			throw new Exception("PhysicsEngine::PxInit, Could not create the PhysX SDK foundation.");

		//physics
		if (!physics)
			physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale());

		if(!physics)
			throw new Exception("PhysicsEngine::PxInit, Could not initialise the PhysX SDK.");

		if (!cooking)
			cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));

		if(!cooking)
			throw new Exception("PhysicsEngine::PxInit, Could not initialise the cooking component.");

		//visual debugger
		if (!vd_connection)
			vd_connection = PxVisualDebuggerExt::createConnection(physics->getPvdConnectionManager(), 
			"localhost", 5425, 100, PxVisualDebuggerExt::getAllConnectionFlags());

		if (!default_material)
			default_material = physics->createMaterial(0.0f, 0.0f, 0.597f);
	}

	void PxRelease()
	{
		if (default_material)
			default_material->release();
		if (vd_connection)
			vd_connection->release();
		if (cooking)
			cooking->release();
		if (physics)
			physics->release();
		if (foundation)
			foundation->release();
	}

	PxPhysics* GetPhysics() 
	{ 
		return physics; 
	}

	PxCooking* GetCooking()
	{
		return cooking;
	}

	PxMaterial* GetDefaultMaterial() 
	{ 
		return default_material; 
	}

	PxMaterial* CreateMaterial(PxReal sf, PxReal df, PxReal cr) 
	{
		return physics->createMaterial(sf, df, cr); 
	}

	///Actor methods
	Actor::Actor(const PxTransform& _pose, const PxVec3& _color)
		: pose(_pose), color(_color)
	{
	}

	PxActor* Actor::Get()
	{
		return actor;
	}

	///Scene methods
	void Scene::Init()
	{
		//scene
		PxSceneDesc sceneDesc(GetPhysics()->getTolerancesScale());

		if(!sceneDesc.cpuDispatcher)
		{
			PxDefaultCpuDispatcher* mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
			sceneDesc.cpuDispatcher = mCpuDispatcher;
		}

		if(!sceneDesc.filterShader)
			sceneDesc.filterShader = PxDefaultSimulationFilterShader;

		px_scene = GetPhysics()->createScene(sceneDesc);

		if (!px_scene)
			throw new Exception("PhysicsEngine::Scene::Init, Could not initialise the scene.");

		//default gravity
		px_scene->setGravity(PxVec3(0.0f, -9.81f, 0.0f));

		gameLogic = new Game::GameLogic();

		CustomInit();

		pause = false;

		selected_actor = 0;

		SelectNextActor();
	}

	void Scene::Update(PxReal dt)
	{
		if (pause)
			return;

		CustomUpdate();

		px_scene->simulate(dt);
		px_scene->fetchResults(true);
		if(gameLogic->IsGameOver())
		{
			scene->Reset();
		}
	}

	void Scene::Add(Actor& actor)
	{
		actor.Create();
		px_scene->addActor(*actor.Get());
	}

	PxScene* Scene::Get() 
	{ 
		return px_scene; 
	}

	void Scene::Reset()
	{
		px_scene->release();
		Init();
	}

	void Scene::Pause(bool value)
	{
		pause = value;
	}

	bool Scene::Pause() 
	{ 
		return pause;
	}

	PxRigidDynamic* Scene::GetSelectedActor()
	{
		return selected_actor;
	}

	void Scene::SelectNextActor()
	{
		PxU32 nbActors = px_scene->getNbActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
		if(nbActors)
		{
			std::vector<PxRigidDynamic*> actors(nbActors);
			px_scene->getActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC, (PxActor**)&actors[0], nbActors);
			if (selected_actor)
			{
				for (unsigned int i = 0; i < actors.size(); i++)
					if (selected_actor == actors[i])
					{
						//restore the original color
						//*((PxVec3*)selected_actor->userData) = sactor_color_orig;
						//select the next actor
						selected_actor = actors[(i+1)%actors.size()];
						break;
					}
			}
			else
			{
				selected_actor = actors[0];
			}
			//store the original colour and adjust brightness of the selected actor
			//sactor_color_orig = *((PxVec3*)selected_actor->userData);
			//*((PxVec3*)selected_actor->userData) += PxVec3(.2f,.2f,.2f);
		}
		else
			selected_actor = 0;
	}

	std::vector<PxRigidActor*> Scene::GetAllActors()
	{
		PxU32 nbActors = px_scene->getNbActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC | PxActorTypeSelectionFlag::eRIGID_STATIC);
		std::vector<PxRigidActor*> actors(nbActors);
		if(nbActors)
			px_scene->getActors(PxActorTypeSelectionFlag::eRIGID_DYNAMIC | PxActorTypeSelectionFlag::eRIGID_STATIC, (PxActor**)&actors[0], nbActors);
		return actors;
	}
}
