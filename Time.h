#pragma once
#include "SDL.h"

class Time_ {
private:
	int lastTick;
	int cycleTime = 0;

	float deltaTime_;
	float time_;
	float unscaledDeltaTime_;
	float unscaledTime_;
	
	float fixedDeltaTime_;
	float fixedUnscaledDeltaTime_;
	float fixedTime_;
	float fixedUnscaledTime_;

	float maximumDeltaTime_;
	float timeScale_;

public:

	//readonly
	const float& deltaTime;
	const float& time;
	const float& unscaledDeltaTime;
	const float& unscaledTime;

	const float& fixedDeltaTime;
	const float& fixedUnscaledDeltaTime;
	const float& fixedTime;
	const float& fixedUnscaledTime;

	const float& maximumDeltaTime;
	const float& timeScale;
	//readonly

	void setTimeScale(float newTimeScale) {
		timeScale_ = newTimeScale;
		fixedDeltaTime_ = timeScale_ * fixedUnscaledDeltaTime;
	}

	void calculateDelta() {
		int currentTick = SDL_GetTicks();
		cycleTime = currentTick - lastTick; //delta in miliseconds
		lastTick = currentTick;

		unscaledDeltaTime_ = cycleTime * 0.001; //convert to float;


		if (unscaledDeltaTime_ > maximumDeltaTime_)
			unscaledDeltaTime_ = maximumDeltaTime_;
		deltaTime_ = unscaledDeltaTime_ * timeScale_;
		unscaledTime_ += unscaledDeltaTime_;
		time_ += deltaTime_;
		
	}

	void calculateFixedTime() {
		fixedUnscaledTime_ += fixedUnscaledDeltaTime_;
		fixedTime_ += timeScale_ * unscaledDeltaTime_;
	}

	Time_() :
		deltaTime_(0.0f),
		time_(0.0f),
		unscaledDeltaTime_(0.01f),//100 pyhics update per seconds
		unscaledTime_(0.0f),

		fixedDeltaTime_(0.01f),
		fixedUnscaledDeltaTime_(0.01f), //100 pyhics update per seconds
		fixedTime_(0.0f),
		fixedUnscaledTime_(0.0f),

		maximumDeltaTime_(0.1f),
		timeScale_(1.0f),


		deltaTime(deltaTime_),
		time(time_),
		unscaledDeltaTime(unscaledDeltaTime_),
		unscaledTime(unscaledTime_),

		fixedDeltaTime(fixedDeltaTime_),
		fixedUnscaledDeltaTime(fixedUnscaledDeltaTime_),
		fixedTime(fixedTime_),
		fixedUnscaledTime(fixedUnscaledTime_),

		maximumDeltaTime(maximumDeltaTime_),
		timeScale(timeScale_)
	
	{
		
		timeScale_ = 1.0f; //1 second per second
		maximumDeltaTime_ = 0.1f; //0,1s
		lastTick = SDL_GetTicks();



		//init references
		



	}
} Time;