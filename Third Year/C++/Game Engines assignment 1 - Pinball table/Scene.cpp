#include "Scene.h"



namespace PhysicsEngine
{
	void MyScene::SetVisualisation()
			{
				px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
				px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
				px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
				px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
				px_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_LIN_VELOCITY, 1.0f);
			}

		void MyScene::CustomInit() 
			{
				//print to the console when a new game is called
				//helpful for distinguishing metrics
				cout << "---------------------NEW GAME----------------"<< endl;
				//elapsed time during the life
				lifeTime = 0;

				/// score gain during that life
				ballScore = 0;

				SetVisualisation();			


				///Initialise and set the customised event callback
				my_callback = new MySimulationEventCallback();
				px_scene->setSimulationEventCallback(my_callback);


				PinballTable = new Table();
				PinballTable->Create();
				Add(*PinballTable);
				// coefficient of restitution obatained from here: http://hypertextbook.com/facts/2006/restitution.shtml
				ball = new Ball(PxTransform(PxVec3(4.5f,9.5f,7.5f)),0.2f,0.5f, PxVec3(0.3f),CreateMaterial(0.0f,0.0f,0.597f),true,true,false,false);
				ball->Create();
				Add(*ball);

				multiBalls =  vector<Ball*>(3);
				multiBalls.at(0) = new Ball(PxTransform(PxVec3(4.5f,9.5f,7.5f)),0.2f,0.5f, PxVec3(0.3f),CreateMaterial(0.0f,0.0f,0.597f),false,false,false,false);
				multiBalls.at(0)->Create();
				multiBalls.at(1) = new Ball(PxTransform(PxVec3(4.5f,9.5f,7.5f)),0.2f,0.5f, PxVec3(0.3f),CreateMaterial(0.0f,0.0f,0.597f),false,false,false,false);
				multiBalls.at(1)->Create();
				multiBalls.at(2) = new Ball(PxTransform(PxVec3(4.5f,9.5f,7.5f)),0.2f,0.5f, PxVec3(0.3f),CreateMaterial(0.0f,0.0f,0.597f),false,false,false,false);
				multiBalls.at(2)->Create();
				

				plunger = new Plunger(this,PinballTable, PxVec3(0.40f,0.40f,0.1f),80.0f,3.0f,PxTransform(PxVec3(4.5f,9.47f,8.0f),PxQuat(0.122173048f,PxVec3(1.0f,0.0f,0.0f))));
				leftFlipper = new Flipper(this,
											PinballTable,
											PxVec2(.2f,.5f),
											1.0f,
											tableTransform,
											PxTransform(PxVec3(-2.25f,0.5f,7.8f),PxQuat(PxPi/2,PxVec3(0.f,0.f,1.f))),
											PxTransform(PxVec3(-0.7f,0.0f,0.0f),PxQuat(ToRadians(90),PxVec3(0.0f,1.0f,0.0f))),
											60.0f,
											100.0f,
											PxVec3(0.5f,0.5f,0.0f));
				leftFlipper->Create();

				rightFlipper = new Flipper(this,
											PinballTable,
											PxVec2(.2f,.5f),
											1.0f,
											tableTransform,
											PxTransform(PxVec3(1.25f,0.5f,7.8f),PxQuat(PxPi/2,PxVec3(0.f,0.f,1.f))),
											PxTransform(PxVec3(0.7f,0.0f,0.0f),PxQuat(ToRadians(90),PxVec3(0.0f,1.0f,0.0f))),
											80.0f,
											120.0f,
											PxVec3(0.5f,0.5f,0.0f));
				rightFlipper->Create();


				//out of bounds trigger
				bottomBound = new Box(PxTransform(PxVec3(-0.5f,9.7f,9.6f),PxQuat(ToRadians(7),PhysicsEngine::PxVec3(1.0f,0.0f,0.0f))),PxVec3(4.5f,0.5f,0.1f),1.0f,PxVec3(0.12f,0.34f,0.45f));
				bottomBound->Create();
				Add(*bottomBound);
				bottomBound->Get()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
				bottomBound->GetShape()->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
				bottomBound->GetShape()->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

				//Ball launch trigger. used for detecting multiball launch
				launchTrigger = new Box(PxTransform(PxVec3(4.5f,11.0f,-4.6f),PxQuat(ToRadians(7),PhysicsEngine::PxVec3(1.0f,0.0f,0.0f))),PxVec3(0.4f,0.5f,0.1f),1.0f,PxVec3(0.12f,0.34f,0.45f));
				launchTrigger->Create();
				Add(*launchTrigger);
				launchTrigger->Get()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
				launchTrigger->GetShape()->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
				launchTrigger->GetShape()->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);


				//Create transform for positioning bumper trigger correctly
				PxQuat tempQuat = PxQuat(ToRadians(7),PhysicsEngine::PxVec3(1.0f,0.0f,0.0f)) * PxQuat(ToRadians(90),PhysicsEngine::PxVec3(0.0f,0.0f,1.0f));
				tempQuat.normalize();		

				//Create triggers
				middleBumperTrigger = new Capsule(PxTransform(PxVec3(-0.5f,11.0f,-4.8f),tempQuat),PxVec2(0.6f,0.3f),1.0f,PxVec3(0.12f,0.34f,0.45f));
				middleBumperTrigger->Create();
				Add(*middleBumperTrigger);
				middleBumperTrigger->Get()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
				middleBumperTrigger->GetShape()->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
				middleBumperTrigger->GetShape()->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

				leftBumperTrigger = new Capsule(PxTransform(PxVec3(-2.0f,11.0f,-3.3f),tempQuat),PxVec2(0.6f,0.3f),1.0f,PxVec3(0.12f,0.34f,0.45f));
				leftBumperTrigger->Create();
				Add(*leftBumperTrigger);
				leftBumperTrigger->Get()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
				leftBumperTrigger->GetShape()->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
				leftBumperTrigger->GetShape()->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

				rightBumperTrigger = new Capsule(PxTransform(PxVec3(1.0f,11.0f,-3.3f),tempQuat),PxVec2(0.6f,0.3f),1.0f,PxVec3(0.12f,0.34f,0.45f));
				rightBumperTrigger->Create();
				Add(*rightBumperTrigger);
				rightBumperTrigger->Get()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
				rightBumperTrigger->GetShape()->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
				rightBumperTrigger->GetShape()->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

			}

			// Resets the ball 
		void MyScene::RecreateBall()
		{
			cout << "Ball Life Time: " << lifeTime << endl;
			cout << "Ball score: " << ballScore << endl;
			ball->Get()->setGlobalPose(PxTransform(PxVec3(4.5f,9.5f,7.5f)));
			ball->Get()->setLinearVelocity(PxVec3(0.0f,0.0f,0.0f));
			lifeTime = 0;
			ballScore = 0;
		}
		//used to detect end of multiball and ball out of bounds to call RecreaetBall()
		void MyScene::CustomUpdate() 
			{
				
				if(my_callback->ballOutOfBounds && !my_callback->multiBallActive)
				{
					ball->SetResetStatus(true);
					my_callback->ballOutOfBounds = false;
				}
				
			}
		//resets multiball when multiball is activated
		void MyScene::ResetMultiBall(Ball &actor)
			{
				actor.Get()->setGlobalPose(PxTransform(PxVec3(4.5f,9.5f,7.5f)));
				actor.SetSceneStatus(true);
				actor.SetResetStatus(false);
				actor.SetLaunchStatus(false);
				px_scene->addActor(*actor.Get());
			}
		//remove multiball from scene
		void MyScene::RemoveMultiBall(Ball &actor)
			{
				px_scene->removeActor(*actor.Get());
				actor.SetSceneStatus(false);
			}
}