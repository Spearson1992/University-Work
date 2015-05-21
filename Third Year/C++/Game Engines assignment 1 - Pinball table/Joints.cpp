#include "Joints.h"
namespace PhysicsEngine
{
	RevoluteJoint::RevoluteJoint(PxRigidActor* actor0, PxTransform& localFrame0, PxRigidActor* actor1, PxTransform& localFrame1)
			{
				joint = PxRevoluteJointCreate(*GetPhysics(), actor0, localFrame0, actor1, localFrame1);
				joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
				joint->setConstraintFlag(PxConstraintFlag::eCOLLISION_ENABLED,true);
			}

			void RevoluteJoint::DriveVelocity(PxReal value)
			{
				joint->setDriveVelocity(value);
				joint->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
			}

			PxReal RevoluteJoint::DriveVelocity()
			{
				return joint->getDriveVelocity();
			}

			void RevoluteJoint::SetLimits(PxReal lower, PxReal upper)
			{
				joint->setLimit(PxJointAngularLimitPair(lower, upper));
				joint->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
			}
}