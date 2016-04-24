#pragma once

#define _USE_MATH_DEFINES

#define MAP_WIDTH		40
#define MAP_HEIGHT		40

#define MAX_WIDTH		30
#define MAX_HEIGHT		30

#define LOG_LINES		 5

#define PLANT_CHANCE	10
#define ANIMAL_MAX_CHILD 2

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <exception>
#include <iostream>
#include <windows.h>
#include "pdcurses/curses.h"

#include "Vector2.h"
#include "text.h"
#include "Logs.h"
#include "InterruptActionException.h"

#define MAP_SIZE V2(MAP_WIDTH, MAP_HEIGHT)

#include "DialogBox.h"
#include "BaseGame.h"
#include "Window.h"

#include "Organism.h"

#include "Animal.h"
#include "Player.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Antelope.h"
#include "Fox.h"

#include "Plant.h"
#include "Grass.h"
#include "Guarana.h"
#include "Wolfberry.h"
#include "SowThistle.h"

#include "World.h"

