#pragma once

class IDamageable {
	virtual void onDamage(float value) = 0;
	virtual ~IDamageable() {};
};