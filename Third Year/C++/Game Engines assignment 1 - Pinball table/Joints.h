#ifndef Joints_H
#define Joints_H
#include "PhysicsEngine.h"
namespace PhysicsEngine
{
	class DistanceJoint
	{
	public:
		DistanceJoint(PxRigidActor* actor0, PxTransform& localFrame0, PxRigidActor* actor1, PxTransform& localFrame1, PxReal stiffness=1.f, PxReal damping=1.f)
		{
			PxDistanceJoint* joint = PxDistanceJointCreate(*GetPhysics(), actor0, localFrame0, actor1, localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
			joint->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
			joint->setStiffness(stiffness);
			joint->setDamping(damping);
			joint->setConstraintFlag(PxConstraintFlag::eCOLLISION_ENABLED,true);
		}
	};
	class RevoluteJoint
	{
		PxRevoluteJoint* joint;
	public:
		RevoluteJoint(PxRigidActor* actor0, PxTransform& localFrame0, PxRigidActor* actor1, PxTransform& localFrame1);

		void DriveVelocity(PxReal value);

		PxReal DriveVelocity();

		void SetLimits(PxReal lower, PxReal upper);
	};
}


#endif