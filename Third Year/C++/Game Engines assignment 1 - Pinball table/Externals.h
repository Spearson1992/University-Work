#ifndef Externals_H
#define External_H


#include "Scene.h"
#include "GameLogic.h"

//Declare these as externals due to them  being needed across the project
extern  PhysicsEngine::MyScene* scene;
extern Game::GameLogic *gameLogic;

#endif