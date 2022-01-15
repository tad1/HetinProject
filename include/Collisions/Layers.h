#pragma once

//Layers values
#define LAYER_VALUE_ALL 255
#define LAYER_VALUE_NONE 0
#define LAYER_VALUE_WORLD 1
#define LAYER_VALUE_PLAYER 2
#define LAYER_VALUE_PLAYER_BULLETS 4
#define LAYER_VALUE_ENEMY_BULLETS 8
#define LAYER_VALUE_ENEMY 16

//Layers ids
#define LAYER_WORLD 0
#define LAYER_PLAYER 1
#define LAYER_PLAYER_BULLETS 2
#define LAYER_ENEMY_BULLETS 3
#define LAYER_ENEMY 4
#define LAYER_COUNT 5

//Layers sizes
#define LAYER_WORLD_SIZE 1
#define LAYER_PLAYER_SIZE 1
#define LAYER_PLAYER_BULLETS_SIZE 6
#define LAYER_ENEMY_BULLETS_SIZE 400
#define LAYER_ENEMY_SIZE 100


struct LayerInfo {
	int id;
	int value;
	int size;
};

const LayerInfo layersInfo[LAYER_COUNT] = {
	{LAYER_WORLD,LAYER_VALUE_WORLD,LAYER_WORLD_SIZE},
	{LAYER_PLAYER,LAYER_VALUE_PLAYER,LAYER_PLAYER_SIZE},
	{LAYER_PLAYER_BULLETS,LAYER_VALUE_PLAYER_BULLETS,LAYER_PLAYER_BULLETS_SIZE},
	{LAYER_ENEMY,LAYER_VALUE_ENEMY,LAYER_ENEMY_BULLETS_SIZE},
	{LAYER_ENEMY_BULLETS,LAYER_VALUE_ENEMY_BULLETS,LAYER_ENEMY_SIZE}
};

const int collision_matrix[LAYER_COUNT] = {
	LAYER_VALUE_ALL, //World
	LAYER_VALUE_ENEMY | LAYER_VALUE_ENEMY_BULLETS, //Player
	LAYER_VALUE_ENEMY, //Player Bullets
	LAYER_VALUE_NONE, //Enemy Bullets
	LAYER_VALUE_NONE }; //Enemy


inline bool layerInteract(int layerID, int layerValue) {
	return (collision_matrix[layerID] & layerValue) != LAYER_VALUE_NONE;
}
