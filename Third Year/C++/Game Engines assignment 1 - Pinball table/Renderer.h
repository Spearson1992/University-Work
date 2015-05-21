#pragma once

#include "PxPhysicsAPI.h"
#include "GLFontRenderer.h"
#include <GL/glut.h>
#include <string>

namespace VisualDebugger
{
	namespace Renderer
	{
		using namespace physx;

		///Init rendering window
		void InitWindow(const char *name, int width, int height);

		///Init renderer
		void Init();

		///Start rendering a single frame
		void Start(const PxVec3& cameraEye, const PxVec3& cameraDir);

		///Render actors
		void Render(PxRigidActor** actors, const PxU32 numActors);

		///Render debug information
		void Render(const PxRenderBuffer& data);

		///Render text
		void RenderText(const std::string& text, const physx::PxVec2& location, 
			const PxVec3& color=PxVec3(1.f,1.f,1.f), PxReal size=0.024f);

		///Finish rendering a single frame
		void Finish();

		///Set rendering detail for spheres and capsules.
		void SetRenderDetail(int value);

		///Set show shadows
		void ShowShadows(bool value);

		///Get show shadows
		bool ShowShadows();
	}
}