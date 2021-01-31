#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<box2d/box2d.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Im old 4 this"

#define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 3.0f

enum GameState 
{
    MENU,
    GAME,
    GAMEOVER,
    END
}gameState;