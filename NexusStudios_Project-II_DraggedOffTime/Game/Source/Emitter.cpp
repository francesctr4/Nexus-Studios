#include "Emitter.h"
#include "App.h"
#include <time.h>

Emitter::Emitter(fPoint pos, EmitterData data)
{
	srand(time(NULL));

	// Particles size and movement
	this->angleRange = data.angleRange;
	this->startSpeed = data.startSpeed;
	this->endSpeed = data.endSpeed;
	this->startSize = data.startSize;
	this->endSize = data.endSize;
	this->pos = pos;
	this->rotSpeed = data.rotSpeed;

	// Particle emission calculations
	this->emitNumber = data.emitNumber;
	this->emitVariance = data.emitVariance;
	this->maxParticleLife = data.maxParticleLife;
	maxParticlesPerFrame = data.emitNumber + data.emitVariance;

	// Pool size calculations
	poolSize = maxParticlesPerFrame * (maxParticleLife + 1);
	emitterPool = new ParticlePool(this);

	// Color and render properties
	this->textureRect = data.textureRect;
	this->startColor = data.startColor;
	this->endColor = data.endColor;
	this->blendMode = data.blendMode;
	timeStep = 1.0f / (float)maxParticleLife;

	// Emission properties
	active = true;
	lifetime = data.lifetime;

	// Random control parameters
	rotSpeedRand = data.rotSpeedRand;
	startSpeedRand = data.startSpeedRand;
	endSpeedRand = data.endSpeedRand;
	emitVarianceRand = data.emitVarianceRand;
	lifeRand = data.lifeRand;
	startSizeRand = data.startSizeRand;
	endSizeRand = data.endSizeRand;

	// Vortex control parameters
	vortexSensitive = data.vortexSensitive;

	if (this->lifetime != -1.0f && this->lifetime > 0.0f)
		lifeTimer.Start();
}

Emitter::~Emitter()
{
	delete emitterPool;
	emitterPool = nullptr;
}

void Emitter::Update(float dt)
{
	if (active)
	{
		// Particle generation from pool

		emissionRate = (int)(emitNumber + emitVariance * RangeRandomNum(emitVarianceRand.x, emitVarianceRand.y));

		for (int i = 1; i <= emissionRate; i++)
		{
			float tmpStartSpeed = startSpeed * RangeRandomNum(startSpeedRand.x, startSpeedRand.y);
			float tmpEndSpeed = endSpeed * RangeRandomNum(endSpeedRand.x, endSpeedRand.y);
			float randAngle = RangeRandomNum(angleRange.x, angleRange.y);
			float randStart = startSize * RangeRandomNum(startSizeRand.x, startSizeRand.y);
			float randEnd = startSize * RangeRandomNum(startSizeRand.x, startSizeRand.y);
			float randRadius = RangeRandomNum(randStart, randEnd);
			double randRotSpeed = rotSpeed * RangeRandomNum(rotSpeedRand.x, rotSpeedRand.y);

			emitterPool->Generate(pos, tmpStartSpeed, tmpEndSpeed, randAngle, randRotSpeed, randRadius, endSize, maxParticleLife, textureRect, startColor, endColor, blendMode, vortexSensitive);
			timeStep += timeStep;
		}
	}

	// Emission timing calculations

	if (stopTime > 0.0f && !active)
	{
		emissionTime = 0.0f;
		if (stopTimer.ReadMs() >= stopTime)
		{
			active = true;
			stopTime = 0.0f;
		}
	}

	if (emissionTime > 0.0f)
	{
		stopTime = 0.0f;
		if (emissionTimer.ReadMs() >= emissionTime)
		{
			active = false;
			emissionTime = 0.0f;
		}
	}

	if (lifetime > 0.0f)
	{
		if (lifeTimer.ReadMs() >= lifetime)
		{
			active = false;
			lifetime = 0.0f;
		}
	}
}

bool Emitter::Draw(float dt)
{
	bool ret = true;
	// Updating particles in the pool
	/* NOTE: if lifetime is 0 and last particles have been updated
	then the emitter is automatically destroyed */
	if (emitterPool->Update(dt) == ParticleState::PARTICLE_DEAD && lifetime == 0.0f)
		app->particleSystem->RemoveEmitter(this);
	else if (emitterPool->Update(dt) == ParticleState::PARTICLE_ALIVE_NOT_DRAWN)
		ret = false;

	return ret;

}

float Emitter::RangeRandomNum(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;

	return min + r;
}

int Emitter::GetPoolSize() const
{
	return poolSize;
}

void Emitter::StartEmission(double timer)
{
	if (!active)
	{
		active = true;
		emissionTime = timer;
		emissionTimer.Start();
	}
}

void Emitter::StopEmission(double timer)
{
	if (active)
	{
		active = false;
		stopTime = timer;
		stopTimer.Start();
	}
}

void Emitter::MoveEmitter(fPoint newPos)
{
	pos = newPos;
}

fPoint Emitter::GetEmitterPos() const
{
	return pos;
}

void Emitter::VortexSensitive(bool sensitive)
{
	vortexSensitive = sensitive;
}