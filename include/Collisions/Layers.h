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


struct LayerInfo {
	int id;
	int value;
	int size;
};

const LayerInfo layersInfo[LAYER_COUNT] = {
	{LAYER_WORLD,LAYER_VALUE_WORLD,1},
	{1,2,1},
	{2,4,30},
	{3,8,400},
	{4,16,100}
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
