#pragma once
#include <SDL.h>


enum colorNames{
	PRIMARY_COLOR = 0,
	SECONDARY_COLOR, 
	HEALTH_COLOR,
	CLOUD_COLOR,
	BULLET_COLOR,
	COUNT_OF_COLORS
};

const SDL_Color colors[COUNT_OF_COLORS] = {
	{0x5c,0x09, 0x1c, 0xff}, // Player & Enemies (primary) color
	{0xe5,0xdd, 0xa9, 0xff}, //Background (Secondary) color
	{0xed,0xe8,0xcc, 0xff}, //Health color
	{0xff,0xff,0xff,0xff}, //Cloud color
	{0x00,0x00,0x00,0xff} //Bullet - No modulation
};