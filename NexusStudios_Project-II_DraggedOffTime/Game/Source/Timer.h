#pragma once

#include "Defs.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	uint32 ReadSec() const;
	float ReadMSec() const;

private:
	uint32 startTime;
};