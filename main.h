#pragma once

enum EVENT_KEY {
	NONE, LEFT, RIGHT, UP, DOWN, SPECIAL
};

#define _USE_MATH_DEFINES
#define DEBUG_MODE

#define MAP_WIDTH		20
#define MAP_HEIGHT		20
#define FIELD_SIZE		32
#define PADDING_BOTTOM	100
#define GAME_WIDTH		MAP_WIDTH * FIELD_SIZE
#define GAME_HEIGHT		MAP_HEIGHT * FIELD_SIZE
#define SCREEN_WIDTH	GAME_WIDTH
#define SCREEN_HEIGHT	GAME_HEIGHT + PADDING_BOTTOM

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <list>
#include <exception>
#include <iostream>
#include "Vector2.h"
#include "text.h"
#include "ResourceNotLoadedException.h"
#include "SDL.h"

#ifdef DEBUG_MODE
#include "Debug.h"
#endif

#include "Color.h"
#include "DialogBox.h"
#include "ResourceManager.h"
#include "BaseGame.h"
#include "Window.h"

#include "Organism.h"
#include "Wolf.h"
#include "World.h"

