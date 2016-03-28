#pragma once

/*

TILESET SOURCE: http://opengameart.org/content/lpc-tile-atlas

*/

enum EVENT_KEY {
	NONE, LEFT, RIGHT, UP, DOWN, SPECIAL
};

#define _USE_MATH_DEFINES
#define DEBUG_MODE

#define TETRIS_WIDTH	20
#define TETRIS_HEIGHT	20
#define FIELD_SIZE		32
#define PADDING_BOTTOM	100
#define SCREEN_WIDTH	TETRIS_WIDTH * FIELD_SIZE
#define SCREEN_HEIGHT	TETRIS_HEIGHT * FIELD_SIZE + PADDING_BOTTOM

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <list>
#include <exception>
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