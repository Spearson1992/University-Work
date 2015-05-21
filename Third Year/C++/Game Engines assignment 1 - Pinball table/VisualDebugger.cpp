#include "VisualDebugger.h"
#include <vector>
#include "Extras\Camera.h"
#include "Extras\Renderer.h"
#include "Extras\HUD.h"
#include "Externals.h"
#include <string>
#include <sstream>



namespace VisualDebugger
{
	using namespace physx;

	enum RenderMode
	{
		DEBUG,
		NORMAL,
		BOTH
	};

	enum HUDState
	{
		GAMEINFO = 0,
		HELP = 1,
		PAUSE = 2
	};

	//function declarations
	void KeyHold();
	void KeySpecial(int key, int x, int y);
	void KeyRelease(unsigned char key, int x, int y);
	void KeyPress(unsigned char key, int x, int y);

	void motionCallback(int x, int y);
	void mouseCallback(int button, int state, int x, int y);
	void exitCallback(void);

	void RenderScene();
	void ToggleRenderMode();
	void HUDInit();

	///simulation objects
	Camera* camera;
	PxReal delta_time = 1.f/60.f;
	PxReal gForceStrength = 20;
	RenderMode render_mode = NORMAL;
	const int MAX_KEYS = 256;
	bool key_state[MAX_KEYS];
	bool hud_show = true;
	HUD hud;

	//Init the debugger
	void Init(const char *window_name, int width, int height)
	{
		///Init PhysX
		PhysicsEngine::PxInit();
		scene = new PhysicsEngine::MyScene();
		scene->Init();
		

		///Init renderer
		Renderer::SetRenderDetail(40);
		Renderer::InitWindow(window_name, width, height);
		Renderer::Init();

		camera = new Camera(PxVec3(0.0f, 20.0f, 15.0f), PxVec3(0.f,-1.f,-1.f), 5.f);

		//initialise HUD
		HUDInit();

		///Assign callbacks
		//render
		glutDisplayFunc(RenderScene);

		//keyboard
		glutKeyboardFunc(KeyPress);
		glutSpecialFunc(KeySpecial);
		glutKeyboardUpFunc(KeyRelease);

		//mouse
		glutMouseFunc(mouseCallback);
		glutMotionFunc(motionCallback);

		//exit
		atexit(exitCallback);

		//init motion callback
		motionCallback(0,0);
	}

	void HUDInit()
	{
		//initialise HUD
		//add an empty screen
		hud.AddLine(GAMEINFO, "Lives: 3");
		hud.AddLine(GAMEINFO, "Score: 0");
		//add a help screen
		hud.AddLine(HELP, " Simulation");
		hud.AddLine(HELP, "    F9 - select next actor");
		hud.AddLine(HELP, "    F10 - pause");
		hud.AddLine(HELP, "    F12 - reset");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, " Display");
		hud.AddLine(HELP, "    F5 - help on/off");
		hud.AddLine(HELP, "    F6 - shadows on/off");
		hud.AddLine(HELP, "    F7 - render mode");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, " Camera");
		hud.AddLine(HELP, "    W,S,A,D,Q,Z - forward,backward,left,right,up,down");
		hud.AddLine(HELP, "    mouse + click - change orientation");
		hud.AddLine(HELP, "    F8 - reset view");
		hud.AddLine(HELP, "");
		hud.AddLine(HELP, " Force (applied to the selected actor)");
		hud.AddLine(HELP, "    I,K,J,L,U,M - forward,backward,left,right,up,down");
		//add a pause screen
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "");
		hud.AddLine(PAUSE, "   Simulation paused. Press F10 to continue.");
	}

	//Start the main loop
	void Start()
	{ 
		glutMainLoop(); 
	}

	//Render the scene and perform a single simulation step
	void RenderScene()
	{
		//handle pressed keys
		KeyHold();

		//start rendering
		Renderer::Start(camera->getEye(), camera->getDir());

		if ((render_mode == DEBUG) || (render_mode == BOTH))
		{
			Renderer::Render(scene->Get()->getRenderBuffer());
		}

		if ((render_mode == NORMAL) || (render_mode == BOTH))
		{
			std::vector<PxRigidActor*> actors = scene->GetAllActors();
			if (actors.size())
				Renderer::Render(&actors[0], (PxU32)actors.size());
		}

		//adjust the HUD state
		if (hud_show)
		{
			if (scene->Pause())
				hud.ActiveScreen(PAUSE);
			else
				hud.ActiveScreen(GAMEINFO);
		}
		else
			hud.ActiveScreen(HELP);
		hud.Clear(GAMEINFO);
		stringstream lives;
		stringstream score;
		lives << "Lives: " << gameLogic->GetLives();
		score << "Score: " << gameLogic->GetScore();

		hud.AddLine(GAMEINFO, lives.str());
		hud.AddLine(GAMEINFO, score.str());
		//render HUD
		hud.Render();

		//finish rendering
		Renderer::Finish();

		//perform a single simulation step
		scene->Update(delta_time);
		scene->lifeTime += delta_time;
		if(scene->ball->GetResetStatus())
		{
			scene->RecreateBall();
			scene->ball->SetResetStatus(false);
		}
		for(unsigned int i = 0; i < scene->multiBalls.size(); i++)
		{
			if(scene->multiBalls.at(i)->GetResetStatus())
			{
				scene->ResetMultiBall(*scene->multiBalls.at(i));			
			}

			if(!scene->multiBalls.at(i)->GetInPlayStatus() 
				&& scene->multiBalls.at(i)->GetSceneStatus()
				&& scene->multiBalls.at(i)->GetLaunchedStatus())
			{
				scene->RemoveMultiBall(*scene->multiBalls.at(i));
			}

		}
		
	}

	//user defined keyboard handlers
	void UserKeyPress(int key)
	{
		switch (toupper(key))
		{
		case 47:
				scene->rightFlipper->Flip(true);
				break;
		case 92:
				scene->leftFlipper->Flip(false);
				break;
		default:
			break;
		}
	}

	void UserKeyRelease(int key)
	{
		switch (toupper(key))
		{
		case 32:
			scene->plunger->ClearForce();
				break;
		case 47:
			scene->rightFlipper->ReleaseFlip(true);
			break;
		case 92:
			scene->leftFlipper->ReleaseFlip(false);
			break;
		default:
			break;
		}
	}

	void UserKeyHold(int key)
	{
		switch(toupper(key))
		{
			case 32:
				scene->plunger->PushDown(delta_time);
				break;
			default:
				break;
		}
	}

	//handle camera control keys
	void CameraInput(int key)
	{
		//switch (toupper(key))
		//{
		/*case 'W':
			camera->MoveForward(delta_time);
			break;
		case 'S':
			camera->MoveBackward(delta_time);
			break;
		case 'A':
			camera->MoveLeft(delta_time);
			break;
		case 'D':
			camera->MoveRight(delta_time);
			break;
		case 'Q':
			camera->MoveUp(delta_time);
			break;
		case 'Z':
			camera->MoveDown(delta_time);
			break;
		default:
			break;*/
		//}
	}

	//handle force control keys
	void ForceInput(int key)
	{
		//if (!scene->GetSelectedActor())
		//	return;

		//switch (toupper(key))
		//{
		//	// Force controls on the selected actor
		//case 'I': //forward
		//	scene->GetSelectedActor()->addForce(PxVec3(0,0,-1)*gForceStrength);
		//	break;
		//case 'K': //backward
		//	scene->GetSelectedActor()->addForce(PxVec3(0,0,1)*gForceStrength);
		//	break;
		//case 'J': //left
		//	scene->GetSelectedActor()->addForce(PxVec3(-1,0,0)*gForceStrength);
		//	break;
		//case 'L': //right
		//	scene->GetSelectedActor()->addForce(PxVec3(1,0,0)*gForceStrength);
		//	break;
		//case 'U': //up
		//	scene->GetSelectedActor()->addForce(PxVec3(0,1,0)*gForceStrength);
		//	break;
		//case 'M': //down
		//	scene->GetSelectedActor()->addForce(PxVec3(0,-1,0)*gForceStrength);
		//	break;
		//default:
		//	break;
		//}
	}

	///handle special keys
	void KeySpecial(int key, int x, int y)
	{
		//simulation control
		switch (key)
		{
			//display control
		case GLUT_KEY_F5:
			//hud on/off
			hud_show = !hud_show;
			break;
		case GLUT_KEY_F6:
			//shadows on/off
			Renderer::ShowShadows(!Renderer::ShowShadows());
			break;
		case GLUT_KEY_F7:
			//toggle render mode
			ToggleRenderMode();
			break;
		case GLUT_KEY_F8:
			//reset camera view
			camera->Reset();
			
			break;

			//simulation control
		case GLUT_KEY_F9:
			//select next actor
			scene->SelectNextActor();
			break;
		case GLUT_KEY_F10:
			//toggle scene pause
			scene->Pause(!scene->Pause());
			break;
		case GLUT_KEY_F12:
			//resect scene
			scene->Reset();
			break;
		default:
			break;
		}
	}

	//handle single key presses
	void KeyPress(unsigned char key, int x, int y)
	{
		//do it only once
		if (key_state[key] == true)
			return;

		key_state[key] = true;

		//exit
		if (key == 27)
			exit(0);

		UserKeyPress(key);
	}

	//handle key release
	void KeyRelease(unsigned char key, int x, int y)
	{
		key_state[key] = false;
		UserKeyRelease(key);
	}

	//handle holded keys
	void KeyHold()
	{
		for (int i = 0; i < MAX_KEYS; i++)
		{
			if (key_state[i]) // if key down
			{
				CameraInput(i);
				ForceInput(i);
				UserKeyHold(i);
			}
		}
	}

	///mouse handling
	int mMouseX = 0;
	int mMouseY = 0;

	void motionCallback(int x, int y)
	{
		int dx = mMouseX - x;
		int dy = mMouseY - y;

		camera->Motion(dx, dy, delta_time);

		mMouseX = x;
		mMouseY = y;
	}

	void mouseCallback(int button, int state, int x, int y)
	{
		mMouseX = x;
		mMouseY = y;
	}

	void ToggleRenderMode()
	{
		if (render_mode == NORMAL)
			render_mode = DEBUG;
		else if (render_mode == DEBUG)
			render_mode = BOTH;
		else if (render_mode == BOTH)
			render_mode = NORMAL;
	}

	///exit callback
	void exitCallback(void)
	{
		delete camera;
		delete scene;
		delete gameLogic;
		PhysicsEngine::PxRelease();
	}
}
