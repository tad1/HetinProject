#pragma once

#include <stdio.h>
#include <assert.h>
#include "../libs/Copyable.h"
#include "../HotMemory.h"
#include "../include/CollisionSystem.h"

bool copyableTest() {
	//test1
	Copyable<int> a = { 5 };
	Copyable<int> b = { 5 };

	assert(a == b);

	b = Copyable<int>{ 6 };
	a = b;
	assert(a.value == 6);

	CopyableString<20> str1 = { "asdf" };
	CopyableString<20> str2 = { "asdf" };
	assert(str1 == str2);
	str2 = "feijfejief";
	str1 = str2;
	assert(str1 == CopyableString<20> {"feijfejief"});

	printf("Copyable, and Copyable string passed!\n");
	return true;
}
bool HotMemoryTest() {
	HotMemory.Use<int>();
	int size = HotMemory.size;
	assert(HotMemory.inUse == true);
	//Input Output Test
	HotMemory.Put(5);
	HotMemory.Put(1);
	HotMemory.Put(-35);
	int* elementsPointer = (int*)HotMemory.elements;
	assert(elementsPointer[0] == 5);
	assert(elementsPointer[1] == 1);
	assert(elementsPointer[2] == -35);

	//Lock test
	assert(HotMemory.Use<CopyableString<20>>() == false);
	assert(HotMemory.size == size);
	HotMemory.Free();
	assert(HotMemory.inUse == false);
	HotMemory.Use<CopyableString<100>>();
	assert(HotMemory.count == 0);
	//Overflow test
	/*CopyableString<100> string;
	string = "asdf";
	for (int i = 0; i < 1024; i++) {
		HotMemory.Put<CopyableString<100>>(string);
	}
	assert(HotMemory.count == HotMemory.size);*/
	HotMemory.Free();
	Console.Log("Hot Memory Test passed");
	return true;
}

bool CollisionsTest() {
	//Simple Collisions test
	Collider a, b, c, d;

#pragma region Circle_and_Circle
	setCircleCollider(a, 10, 10, 5);
	setCircleCollider(b, 12, 10, 2);

	//Circle in Circle 
	assert(a.circle.flag == CIRCLE_FLAG);
	assert(b.circle.flag == CIRCLE_FLAG);
	assert(ColliderManager.isColliding(a, b) == true);

	b.circle.y = 17;
	assert(ColliderManager.isColliding(a, b) == false);


#pragma endregion


#pragma region Circle_and_AABB
	setCircleCollider(a, -5, 5, 5);
	setRectCollider(b, -7, 3, 5, 5);
	assert(ColliderManager.isColliding(a, b) == true);
	setCircleCollider(a, -9, 1, 5);
	assert(ColliderManager.isColliding(a, b) == true);
	setCircleCollider(a, -12, -3, 5);
	assert(ColliderManager.isColliding(a, b) == false);
#pragma endregion

#pragma region AABB_and_AABB
	setRectCollider(a, 100, 5, 10, 10);
	setRectCollider(b, 97.4f, 3.5f, 3.0f, 1.0f);
	assert(ColliderManager.isColliding(a, b) == false);
	b.rect.h = 3.0f;
	assert(ColliderManager.isColliding(a, b) == true);

#pragma endregion

	//ColliderManager Test
	setCircleCollider(a, 10, 10, 5);
	setCircleCollider(b, 12, 12, 2);
	setCircleCollider(c, 13, 11, 2);

	ColliderComponent enemy(a, LAYER_ENEMY);
	ColliderComponent bullet(b, LAYER_PLAYER_BULLETS);
	ColliderComponent enemyBullet(c, LAYER_ENEMY_BULLETS);	enemy.name = "enemy";

	enemy.name = "enemy";
	bullet.name = "Player's bullet";
	enemyBullet.name = "Enemy's bullet";

	ColliderManager.checkCollisions(LAYER_PLAYER_BULLETS);

	ColliderManager.Return(enemy.collider, LAYER_ENEMY);
	ColliderManager.Return(bullet.collider, LAYER_PLAYER_BULLETS);
	ColliderManager.Return(enemyBullet.collider, LAYER_ENEMY_BULLETS);
	enemy.collider = nullptr;
	bullet.collider = nullptr;
	enemyBullet.collider = nullptr;

	Console.Log("Collision test passed");
	return true;
}

bool TextureManagerTest() {

	

	return true;
}

bool testAll() {
	copyableTest();
	HotMemoryTest();
	CollisionsTest();
	return true;

}