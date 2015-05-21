#include "Objects.h"

namespace PhysicsEngine
{

	Table::Table(PxTransform pose,	const PxVec3& _color)
			:Actor(pose,_color)
		{
			colours = new shapeColours(20);
			pinballTable = GetPhysics()->createRigidStatic(tableTransform);
			PxShape *tempShape;
			colours->addColour(PxVec3(0.1f,0.2f,0.7f));
			colours->addColour(PxVec3(0.1f,0.1f,0.2f));
			colours->addColour(PxVec3(0.0f,0.3f,0.0f));
			colours->addColour(PxVec3(0.0f,0.0f,1.0f));
			colours->addColour(PxVec3(1.0f,0.0f,0.0f));

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(5.0f,0.1f,10.0f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(pose); // table bottom
			
			colours->SetShapeColour(BOTTOM,0);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,10.0f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(5.0f,0.5f,0.0f)));//right wall
			
			colours->SetShapeColour(RIGHTWALL,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,10.0f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-5.0f,0.5f,0.0f)));//left wall
			colours->SetShapeColour(LEFTWALL,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(5.0f,0.5f,0.1f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(0.0f,0.5f,-10.0f)));//top wall
			colours->SetShapeColour(TOPWALL,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(5.0f,0.5f,0.1f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(0.0f,0.5f,10.0f)));//bottom wall
			colours->SetShapeColour(BOTTOMWALL,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,7.0f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(4.0f,0.5f,3.0f)));//Ball containment wall
			colours->SetShapeColour(CONTAINMENTWALL,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,1.5f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(4.0f,0.5f,-9.0f),PxQuat(ToRadians(45),PxVec3(0.0f,1.0f,0.0f))));//Top right diagonal
			colours->SetShapeColour(TOPRIGHTDIAG,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,1.5f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-4.0f,0.5f,-9.0f),PxQuat(ToRadians(315),PxVec3(0.0f,1.0f,0.0f))));//Top left diagonal
			colours->SetShapeColour(TOPLEFTDIAG,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,4.0f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(3.0f,0.5f,2.0f)));//right inner wall
			colours->SetShapeColour(RIGHTINNER,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,4.0f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-4.0f,0.5f,2.0f)));//left inner wall
			colours->SetShapeColour(LEFTINNER,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,1.25f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(2.15f,0.5f,6.8f),PxQuat(ToRadians(315),PxVec3(0.0f,1.0f,0.0f))));//right inner D wall
			colours->SetShapeColour(RIGHTINNERDIAG,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.1f,0.5f,1.25f)),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-3.15f,0.5f,6.8f),PxQuat(ToRadians(45),PxVec3(0.0f,1.0f,0.0f))));//left inner D wall
			colours->SetShapeColour(LEFTINNERDIAG,1);

			tempShape = pinballTable->createShape(PxCapsuleGeometry(0.5f,0.2f),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-0.5f,0.5f,-4.8f),PxQuat(ToRadians(90),PxVec3(0.0f,0.0f,1.0f))));//Middle bumper
			colours->addColour(PxVec3(0.0f,0.3f,0.0f));
			colours->SetShapeColour(MIDDLEBUMPER,2);

			tempShape = pinballTable->createShape(PxCapsuleGeometry(0.5f,0.2f),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-2.0f,0.5f,-3.3f),PxQuat(ToRadians(90),PxVec3(0.0f,0.0f,1.0f))));//Left bumper
			colours->SetShapeColour(LEFTBUMPER,2);

			tempShape = pinballTable->createShape(PxCapsuleGeometry(0.5f,0.2f),*GetDefaultMaterial());
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(1.0f,0.5f,-3.3f),PxQuat(ToRadians(90),PxVec3(0.0f,0.0f,1.0f))));//Right bumper
			colours->SetShapeColour(RIGHTBUMPER,2);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.6f,0.5f,0.1f)),*GetPhysics()->createMaterial(0.0f,0.0f,2.0f));
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-4.4f,0.5f,-2.5f),PxQuat(ToRadians(-45),PxVec3(0.0f,1.0f,0.0f))));//Left diagonal blocker
			colours->SetShapeColour(LEFTBLOCKER,1);

			tempShape = pinballTable->createShape(PxBoxGeometry(PxVec3(0.6f,0.5f,0.1f)),*GetPhysics()->createMaterial(0.0f,0.0f,2.0f));
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(3.4f,0.5f,-2.5f),PxQuat(ToRadians(45),PxVec3(0.0f,1.0f,0.0f))));//Right diagonal blocker
			colours->SetShapeColour(RIGHTBLOCKER,1);


			tempShape = pinballTable->createShape(PxCapsuleGeometry(0.5f,0.2f),*GetPhysics()->createMaterial(0.0f,0.0f,2.0f));
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(1.f,0.5f,5.8f),PxQuat(ToRadians(90),PxVec3(0.0f,0.0f,1.0f))));//Bottom right  bumper
			colours->SetShapeColour(BOTTOMRIGHTBUMPER,2);

			tempShape = pinballTable->createShape(PxCapsuleGeometry(0.5f,0.2f),*GetPhysics()->createMaterial(0.0f,0.0f,2.0f));
			if(tempShape)
				tempShape->setLocalPose(PxTransform(PxVec3(-2.f,0.5f,5.8f),PxQuat(ToRadians(90),PxVec3(0.0f,0.0f,1.0f))));//Bottomleft bumper
			colours->SetShapeColour(BOTTOMLEFTBUMPER,2);


			
			actor = pinballTable;
			actor->userData = colours;
		}

	Table::~Table()
		{
			delete colours;
		}
	void Table::Create()
	{

	}
	PxRigidStatic*  Table::GetStatic() 
		{
			return (PxRigidStatic*)actor; 
		}

	Plunger::Plunger(Scene *scene, Table *attachment, PxVec3 &dimensions = PxVec3(1.0f,1.0f,1.0f), PxReal stiffness = 1.0f, PxReal damping = 1.0f, PxTransform & pose = PxTransform(PxIdentity))
	{
		plungerTop = new Box(PxTransform(PxVec3(4.5f,9.47f,8.0f)),dimensions);
		scene->Add(*plungerTop);
		plungerForce = 80.0f;
		timeMult = 0.0f;
		DistanceJoint spring1(attachment->GetStatic(),PxTransform(PxVec3(4.5f - dimensions.x,.47f + dimensions.y,10.0f)),plungerTop->Get(),PxTransform(PxVec3(-dimensions.x,dimensions.y,2.0f)),stiffness,damping);
		DistanceJoint spring2(attachment->GetStatic(),PxTransform(PxVec3(4.5f - dimensions.x,.47f - dimensions.y,10.0f)),plungerTop->Get(),PxTransform(PxVec3(-dimensions.x,-dimensions.y,2.0f)),stiffness,damping);
		DistanceJoint spring3(attachment->GetStatic(),PxTransform(PxVec3(4.5f + dimensions.x,.47f + dimensions.y,10.0f)),plungerTop->Get(),PxTransform(PxVec3(dimensions.x,dimensions.y,2.0f)),stiffness,damping);
		DistanceJoint spring4(attachment->GetStatic(),PxTransform(PxVec3(4.5f + dimensions.x,.47f - dimensions.y,10.0f)),plungerTop->Get(),PxTransform(PxVec3(dimensions.x,-dimensions.y,2.0f)),stiffness,damping);
	}
	//Pushes the plunger down ready for ball launch
	void Plunger::PushDown(PxReal deltaTime)
	{
		if(plungerTop->Get()->getGlobalPose().p.z < (10.0f - 0.40f))
		timeMult +=deltaTime;
		plungerTop->Get()->addForce(PxVec3(0.0f,-0.2f,1.0f)*(plungerForce*2.0f*timeMult));
	}

	Flipper::Flipper(Scene *scene,
				Table *attachment,
				PxVec2 &dimensions,
				PxReal density,
				const PxTransform &pose,
				PxTransform flipperLocation,
				PxTransform jointLocation,
				PxReal lowerJointLimit,
				PxReal upperJointLimit,
				PxVec3 & colour)
		: Actor(pose,colour)
		{
			flipperBody = new Capsule(pose, dimensions, density, colour);
			scene->Add(*flipperBody);
			joint = new RevoluteJoint(attachment->GetStatic(), flipperLocation, flipperBody->Get(),jointLocation);
			joint->SetLimits(ToRadians(lowerJointLimit), ToRadians(upperJointLimit));
		}

	void Flipper::Create()
		{

		}

	void Flipper::Flip(bool isRight)
	{

		flipperBody->Get()->addForce(PxVec3(0.0f,0.0001f,0.0f));
		if(isRight)
		joint->DriveVelocity(-15.0f);
		else
		joint->DriveVelocity(15.0f);
	}

	void Flipper::ReleaseFlip(bool isRight)
	{
		flipperBody->Get()->addForce(PxVec3(0.0f,0.0001f,0.0f));
		if(isRight)
		joint->DriveVelocity(15.0f);
		else
		joint->DriveVelocity(-15.0f);
	}
}