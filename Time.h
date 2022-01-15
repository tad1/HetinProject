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

#pragma region ReadOnly


	/// <summary>
	/// Scaled duration of frame
	/// </summary>
	const float& deltaTime;
	/// <summary>
	/// Scaled game time from the start
	/// </summary>
	const float& time;
	/// <summary>
	/// Real time duration of frame
	/// </summary>
	const float& unscaledDeltaTime;
	/// <summary>
	/// Real game time from the start
	/// </summary>
	const float& unscaledTime;

	/// <summary>
	/// Scaled timestep between physics update
	/// </summary>
	const float& fixedDeltaTime;
	/// <summary>
	/// Real time timestep between physics update
	/// </summary>
	const float& fixedUnscaledDeltaTime;
	/// <summary>
	/// Scaled game time of physics 
	/// </summary>
	const float& fixedTime;
	/// <summary>
	/// Real game time of physics
	/// </summary>
	const float& fixedUnscaledTime;

	/// <summary>
	/// Maximum duration of frame, to prevent big time jump
	/// </summary>
	const float& maximumDeltaTime;

	/// <summary>
	/// Scale of time represented in seconds per seconds.
	/// You can set it to negative, to rewind time
	/// </summary>
	const float& timeScale;
#pragma endregion

	/// <summary>
	/// Set scale of time represented in seconds per seconds.
	/// You can set it to negative, to rewind time
	/// </summary>
	/// <param name="newTimeScale"></param>
	void setTimeScale(float newTimeScale) {
		timeScale_ = newTimeScale;
		fixedDeltaTime_ = timeScale_ * fixedUnscaledDeltaTime;
	}

	/// <summary>
	/// Calculate delta time, and time based on previous call
	/// </summary>
	void calculateDelta() {
		int currentTick = SDL_GetTicks();
		cycleTime = currentTick - lastTick; //delta in miliseconds
		lastTick = currentTick;

		unscaledDeltaTime_ = cycleTime * 0.001; //convert to seconds;


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
		unscaledDeltaTime_(0.01f),//100 physics update per seconds
		unscaledTime_(0.0f),

		fixedDeltaTime_(0.01f),
		fixedUnscaledDeltaTime_(0.01f), //100 physics update per seconds
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


	}
};

static Time_ Time;