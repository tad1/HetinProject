#pragma once
#include "GameObject.h"
#include "GenericPool.h"
#include "../Console.h"

class MonoBechaviour;

static FixedObjectPool<MonoBechaviour> MonoBechaviourPool(1000);

class MonoBechaviour : public GameObject {
	
public:
	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void PhysicsUpdate() {};
	virtual void Render() {};
	
	MonoBechaviour() {};

	virtual ~MonoBechaviour() {};

	void* operator new(size_t size) {
		MonoBechaviour* ptr = MonoBechaviourPool.create();
		Console.Log("created new MonoBechaviour object");
		return ptr;
	}
};