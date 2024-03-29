#pragma once
#include "Math.h"

const float radianConst = 180.0 / M_PI;

template <class T>
inline T clamp(T value, T min, T max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

float lerp(float a, float b, float t) {
	float delta = b - a;
	return a + (delta * t);
}

int sign(int x) {
	return (x > 0) - (x < 0);
}

int sign(float x) {
	return (x > 0) - (x < 0);
}