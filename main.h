#pragma once

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
#include <fstream>
#include <windows.h>
#include "pdcurses/curses.h"

#include "io.h"
#include "Vector2.h"
#include "text.h"
#include "Logs.h"
#include "InterruptActionException.h"
#include "LoadingMapException.h"

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

