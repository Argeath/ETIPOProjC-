#pragma once

#define _USE_MATH_DEFINES

#define MAP_WIDTH		30
#define MAP_HEIGHT		30

#define MAX_WIDTH		30
#define MAX_HEIGHT		30

#define PLANT_CHANCE	5

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <exception>
#include <iostream>
#include <windows.h>
#include "pdcurses/curses.h"

#include "Vector2.h"
#include "text.h"
#include "InterruptActionException.h"

#include "DialogBox.h"
#include "BaseGame.h"
#include "Window.h"

#include "Organism.h"

#include "Animal.h"
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

