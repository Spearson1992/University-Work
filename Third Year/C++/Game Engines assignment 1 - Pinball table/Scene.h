#ifndef Scene_H
#define Scene_H
#include "Shapes.h"
#include "Joints.h"
#include "Objects.h"
#include "SimulationCallback.h"




namespace PhysicsEngine
{
//Forward declaration
class MyScene;
class MySimulationEventCallback;


using namespace std;

class MyScene : public Scene
		{
			MySimulationEventCallback* my_callback;

		public:
			Plunger *plunger;
			Flipper *leftFlipper;
			Flipper *rightFlipper;
			Table* PinballTable;
			Ball* ball;

			//Metric collection variables
			PxReal lifeTime;
			int ballScore;

			//multiball vector
			std::vector<Ball*> multiBalls;


			//Trigger Shapes
			Box *bottomBound;
			Box *launchTrigger;
			Capsule *middleBumperTrigger;
			Capsule *leftBumperTrigger;
			Capsule *rightBumperTrigger;

			///A custom scene class
			void SetVisualisation();

			//Custom scene initialisation
			virtual void CustomInit();

			//Custom udpate function
			virtual void CustomUpdate();

			void RecreateBall();

			/// An example use of key release handling
			void ExampleKeyReleaseHandler()
			{
				cerr << "I am realeased!" << endl;
			}

			/// An example use of key presse handling
			void ExampleKeyPressHandler()
			{
				cerr << "I am pressed!" << endl;
			}

			const MySimulationEventCallback* GetCallback()
			{
				return my_callback;
			}
			void ResetMultiBall(Ball &actor);
			void RemoveMultiBall(Ball &actor);
			
		};
	
}

#endif // !Scene_H


