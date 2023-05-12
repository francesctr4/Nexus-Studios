	#include "Tweening.h"


	Tween::Tween()
	{
		smoothness = 5;
		multiplier = 0.01;
		suppressCallbacks = false;

		nextPos = 0;
		totalLength = 0;
		accumDuration = 0;
	}

	Tween::Tween(float multiplier, float smoothness, bool suppressCallbacks) : accumDuration(0), totalLength(0), nextPos(0)
	{
		this->smoothness = multiplier;
		this->multiplier = multiplier;
		this->suppressCallbacks = suppressCallbacks;
	}


	Tween::~Tween()
	{
	}