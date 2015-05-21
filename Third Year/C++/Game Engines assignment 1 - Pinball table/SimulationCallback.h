#ifndef SimulationCallback_H
#define SimulationCallback_H

#include "PhysicsEngine.h"
#include "VisualDebugger.h"

namespace PhysicsEngine
{
	class MySimulationEventCallback : public PxSimulationEventCallback
		{
		
		public:
			//an example variable that will be checked in the main simulation loop
			bool ballOutOfBounds;
			bool multiBallActive;

			MySimulationEventCallback() : ballOutOfBounds(false), multiBallActive(false){}

			///Method called when the contact with the trigger object is detected.
			virtual void onTrigger(PxTriggerPair* pairs, PxU32 count);

			///Other types of events
			virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) {}
			virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
			virtual void onWake(PxActor **actors, PxU32 count) {}
			virtual void onSleep(PxActor **actors, PxU32 count) {}
			void CheckMainBall(PxTriggerPair* pairs, PxU32 i);
			void OutOfPlayCheck(PxTriggerPair* pairs, PxU32 i);
			void CheckMultiBalls(PxTriggerPair* pairs, PxU32 i);
			void MultiBallLaunchCheck(PxTriggerPair* pairs, PxU32 i);
		};
}
#endif