#ifndef __TWEENY_H__
#define __TWEENY_H__

#include "External/Tweeny/tweeny.h"
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Point.h"
#include "Physics.h"

enum easing2
{
    DEF,
    LINEAR,
    STEPPED,
    QUADRATIC_IN,
    QUADRATIC_OUT,
    QUADRATIC_IN_OUT,
    CUBIC_IN,
    CUBIC_OUT,
    CUBIC_IN_OUT,
    QUARTIC_IN,
    QUARTIC_OUT,
    QUARTIC_IN_OUT,
    QUINTIC_IN,
    QUINTIC_OUT,
    QUINTIC_IN_OUT,
    SINUSOIDAL_IN,
    SINUSOIDAL_OUT,
    SINUSOIDAL_IN_OUT,
    EXPONENTIAL_IN,
    EXPONENTIAL_OUT,
    EXPONENTIAL_IN_OUT,
    CIRCULAR_IN,
    CIRCULAR_OUT,
    CIRCULAR_IN_OUT,
    BOUNCE_IN,
    BOUNCE_OUT,
    BOUNCE_IN_OUT,
    ELASTIC_IN,
    ELASTIC_OUT,
    ELASTIC_IN_OUT,
    BACK_IN,
    BACK_OUT,
    BACK_IN_OUT

};
class Tween
{
public:
    
    Tween();
    Tween(float multiplier, float smoothness, bool suppressCallbacks);
    ~Tween();

    //Set the initial conditions of the tween (start, end, time(ms) and type of easing)
    void Set(int start, int finish, int time, easing2 easingMode)
    {
        //Aplly all the characteristics of the animation
        tween = tweeny::from(start).to(finish * smoothness).during(time);
        nextPos = finish;
        totalLength += nextPos;

        switch (easingMode)
        {
        case DEF:
            tween.via(tweeny::easing::def);
            break;
        case LINEAR:
            tween.via(tweeny::easing::linear);
            break;
        case STEPPED:
            tween.via(tweeny::easing::stepped);
            break;
        case QUADRATIC_IN:
            tween.via(tweeny::easing::quadraticIn);
            break;
        case QUADRATIC_OUT:
            tween.via(tweeny::easing::quadraticOut);
            break;
        case QUADRATIC_IN_OUT:
            tween.via(tweeny::easing::quadraticInOut);
            break;
        case CUBIC_IN:
            tween.via(tweeny::easing::cubicIn);
            break;
        case CUBIC_OUT:
            tween.via(tweeny::easing::cubicOut);
            break;
        case CUBIC_IN_OUT:
            tween.via(tweeny::easing::cubicInOut);
            break;
        case QUARTIC_IN:
            tween.via(tweeny::easing::quarticIn);
            break;
        case QUARTIC_OUT:
            tween.via(tweeny::easing::quarticOut);
            break;
        case QUARTIC_IN_OUT:
            tween.via(tweeny::easing::quarticInOut);
            break;
        case QUINTIC_IN:
            tween.via(tweeny::easing::quinticIn);
            break;
        case QUINTIC_OUT:
            tween.via(tweeny::easing::quinticOut);
            break;
        case QUINTIC_IN_OUT:
            tween.via(tweeny::easing::quinticInOut);
            break;
        case SINUSOIDAL_IN:
            tween.via(tweeny::easing::sinusoidalIn);
            break;
        case SINUSOIDAL_OUT:
            tween.via(tweeny::easing::sinusoidalOut);
            break;
        case SINUSOIDAL_IN_OUT:
            tween.via(tweeny::easing::sinusoidalInOut);
            break;
        case EXPONENTIAL_IN:
            tween.via(tweeny::easing::exponentialIn);
            break;
        case EXPONENTIAL_OUT:
            tween.via(tweeny::easing::exponentialOut);
            break;
        case EXPONENTIAL_IN_OUT:
            tween.via(tweeny::easing::exponentialInOut);
            break;
        case CIRCULAR_IN:
            tween.via(tweeny::easing::circularIn);
            break;
        case CIRCULAR_OUT:
            tween.via(tweeny::easing::circularOut);
            break;
        case CIRCULAR_IN_OUT:
            tween.via(tweeny::easing::circularInOut);
            break;
        case BOUNCE_IN:
            tween.via(tweeny::easing::bounceIn);
            break;
        case BOUNCE_OUT:
            tween.via(tweeny::easing::bounceOut);
            break;
        case BOUNCE_IN_OUT:
            tween.via(tweeny::easing::bounceInOut);
            break;
        case ELASTIC_IN:
            tween.via(tweeny::easing::elasticIn);
            break;
        case ELASTIC_OUT:
            tween.via(tweeny::easing::elasticOut);
            break;
        case ELASTIC_IN_OUT:
            tween.via(tweeny::easing::elasticInOut);
            break;
        case BACK_IN:
            tween.via(tweeny::easing::backIn);
            break;
        case BACK_OUT:
            tween.via(tweeny::easing::backOut);
            break;
        case BACK_IN_OUT:
            tween.via(tweeny::easing::backInOut);
            break;
        default:
            tween.via(tweeny::easing::def);
            break;
        }
    }

    void Set()
    {
        totalTweenings = 1;
        currentTweening = 1;
        tween = tweeny::from(0).to(0 * smoothness).during(1).via(tweeny::easing::def);
        nextPos = 0;
        totalLength += nextPos;
    }

    //Adda new animation (time in ms)
    void AddTween(int duration, int time, easing2 easingMode)
    {
        float currentPoint = tween.progress() * tween.duration();
        tween.to((duration)*smoothness).during(time);

        tween.seek((int32_t)currentPoint, false);

        switch (easingMode)
        {
        case DEF:
            tween.via(tweeny::easing::def);
            break;
        case LINEAR:
            tween.via(tweeny::easing::linear);
            break;
        case STEPPED:
            tween.via(tweeny::easing::stepped);
            break;
        case QUADRATIC_IN:
            tween.via(tweeny::easing::quadraticIn);
            break;
        case QUADRATIC_OUT:
            tween.via(tweeny::easing::quadraticOut);
            break;
        case QUADRATIC_IN_OUT:
            tween.via(tweeny::easing::quadraticInOut);
            break;
        case CUBIC_IN:
            tween.via(tweeny::easing::cubicIn);
            break;
        case CUBIC_OUT:
            tween.via(tweeny::easing::cubicOut);
            break;
        case CUBIC_IN_OUT:
            tween.via(tweeny::easing::cubicInOut);
            break;
        case QUARTIC_IN:
            tween.via(tweeny::easing::quarticIn);
            break;
        case QUARTIC_OUT:
            tween.via(tweeny::easing::quarticOut);
            break;
        case QUARTIC_IN_OUT:
            tween.via(tweeny::easing::quarticInOut);
            break;
        case QUINTIC_IN:
            tween.via(tweeny::easing::quinticIn);
            break;
        case QUINTIC_OUT:
            tween.via(tweeny::easing::quinticOut);
            break;
        case QUINTIC_IN_OUT:
            tween.via(tweeny::easing::quinticInOut);
            break;
        case SINUSOIDAL_IN:
            tween.via(tweeny::easing::sinusoidalIn);
            break;
        case SINUSOIDAL_OUT:
            tween.via(tweeny::easing::sinusoidalOut);
            break;
        case SINUSOIDAL_IN_OUT:
            tween.via(tweeny::easing::sinusoidalInOut);
            break;
        case EXPONENTIAL_IN:
            tween.via(tweeny::easing::exponentialIn);
            break;
        case EXPONENTIAL_OUT:
            tween.via(tweeny::easing::exponentialOut);
            break;
        case EXPONENTIAL_IN_OUT:
            tween.via(tweeny::easing::exponentialInOut);
            break;
        case CIRCULAR_IN:
            tween.via(tweeny::easing::circularIn);
            break;
        case CIRCULAR_OUT:
            tween.via(tweeny::easing::circularOut);
            break;
        case CIRCULAR_IN_OUT:
            tween.via(tweeny::easing::circularInOut);
            break;
        case BOUNCE_IN:
            tween.via(tweeny::easing::bounceIn);
            break;
        case BOUNCE_OUT:
            tween.via(tweeny::easing::bounceOut);
            break;
        case BOUNCE_IN_OUT:
            tween.via(tweeny::easing::bounceInOut);
            break;
        case ELASTIC_IN:
            tween.via(tweeny::easing::elasticIn);
            break;
        case ELASTIC_OUT:
            tween.via(tweeny::easing::elasticOut);
            break;
        case ELASTIC_IN_OUT:
            tween.via(tweeny::easing::elasticInOut);
            break;
        case BACK_IN:
            tween.via(tweeny::easing::backIn);
            break;
        case BACK_OUT:
            tween.via(tweeny::easing::backOut);
            break;
        case BACK_IN_OUT:
            tween.via(tweeny::easing::backInOut);
            break;
        default:
            tween.via(tweeny::easing::def);
            break;
        }
    }
    //Waits a certain amount of time(ms) before entering the next tween
    void Wait(int time)
    {
        tween.to(nextPos).during(time);
    }
    //Updates the tween in whole positions. Returns the current point of the tween
    int Step(int amount, bool suppressCallbacks)
    {
        return tween.step(amount, suppressCallbacks);
        this->suppressCallbacks = suppressCallbacks;
    }
    //Updates the tween in percentages. Returns the current point of the tween
    int Step(float amount, bool suppressCallbacks)
    {
        return tween.step(amount, suppressCallbacks);
    }
    // Returns the current point of the tween without updating it.
    float GetPoint()
    {

        return (float)tween.peek() * multiplier / smoothness;
    }
    void SetEasing(easing2 easingMode)
    {
        switch (easingMode)
        {
        case DEF:
            tween.via(tweeny::easing::def);
            break;
        case LINEAR:
            tween.via(tweeny::easing::linear);
            break;
        case STEPPED:
            tween.via(tweeny::easing::stepped);
            break;
        case QUADRATIC_IN:
            tween.via(tweeny::easing::quadraticIn);
            break;
        case QUADRATIC_OUT:
            tween.via(tweeny::easing::quadraticOut);
            break;
        case QUADRATIC_IN_OUT:
            tween.via(tweeny::easing::quadraticInOut);
            break;
        case CUBIC_IN:
            tween.via(tweeny::easing::cubicIn);
            break;
        case CUBIC_OUT:
            tween.via(tweeny::easing::cubicOut);
            break;
        case CUBIC_IN_OUT:
            tween.via(tweeny::easing::cubicInOut);
            break;
        case QUARTIC_IN:
            tween.via(tweeny::easing::quarticIn);
            break;
        case QUARTIC_OUT:
            tween.via(tweeny::easing::quarticOut);
            break;
        case QUARTIC_IN_OUT:
            tween.via(tweeny::easing::quarticInOut);
            break;
        case QUINTIC_IN:
            tween.via(tweeny::easing::quinticIn);
            break;
        case QUINTIC_OUT:
            tween.via(tweeny::easing::quinticOut);
            break;
        case QUINTIC_IN_OUT:
            tween.via(tweeny::easing::quinticInOut);
            break;
        case SINUSOIDAL_IN:
            tween.via(tweeny::easing::sinusoidalIn);
            break;
        case SINUSOIDAL_OUT:
            tween.via(tweeny::easing::sinusoidalOut);
            break;
        case SINUSOIDAL_IN_OUT:
            tween.via(tweeny::easing::sinusoidalInOut);
            break;
        case EXPONENTIAL_IN:
            tween.via(tweeny::easing::exponentialIn);
            break;
        case EXPONENTIAL_OUT:
            tween.via(tweeny::easing::exponentialOut);
            break;
        case EXPONENTIAL_IN_OUT:
            tween.via(tweeny::easing::exponentialInOut);
            break;
        case CIRCULAR_IN:
            tween.via(tweeny::easing::circularIn);
            break;
        case CIRCULAR_OUT:
            tween.via(tweeny::easing::circularOut);
            break;
        case CIRCULAR_IN_OUT:
            tween.via(tweeny::easing::circularInOut);
            break;
        case BOUNCE_IN:
            tween.via(tweeny::easing::bounceIn);
            break;
        case BOUNCE_OUT:
            tween.via(tweeny::easing::bounceOut);
            break;
        case BOUNCE_IN_OUT:
            tween.via(tweeny::easing::bounceInOut);
            break;
        case ELASTIC_IN:
            tween.via(tweeny::easing::elasticIn);
            break;
        case ELASTIC_OUT:
            tween.via(tweeny::easing::elasticOut);
            break;
        case ELASTIC_IN_OUT:
            tween.via(tweeny::easing::elasticInOut);
            break;
        case BACK_IN:
            tween.via(tweeny::easing::backIn);
            break;
        case BACK_OUT:
            tween.via(tweeny::easing::backOut);
            break;
        case BACK_IN_OUT:
            tween.via(tweeny::easing::backInOut);
            break;
        default:
            tween.via(tweeny::easing::def);
            break;
        }
    }

    //Go to a certain point of the tween while interpolating
    int GoTo(int point, bool suppressCallbacks)
    {
        return tween.seek(point, suppressCallbacks);

    }

    //Go to a certain percentage of the tween with interpolation
    int GoTo(float point, bool suppressCallbacks)
    {
        return tween.seek(point, suppressCallbacks);
    }

    //Go to a certain point of the tween while NOT interpolating
    int JumpTo(int tweenPos, bool suppressCallbacks)
    {
        return tween.jump(tweenPos, suppressCallbacks);
    }

    void Foward()
    {
        tween.forward();
    }

    void Backward()
    {
        tween.backward();
    }

    float Progress()
    {
        return tween.progress();
    }

    uint32_t TotalDuration()
    {

        return tween.duration();
    }

    int Direction()
    {
        return tween.direction();
    }


    tweeny::tween<int> Main() const
    {
        return tween;
    }

public:
    float multiplier;
    float smoothness;
    bool suppressCallbacks;
private:
    tweeny::tween<int> tween;
    int nextPos;
    int totalLength;
    int accumDuration;
    int totalTweenings;
    int currentTweening;
 
//public:
//     void crear_Animation(SDL_Texture* textura, b2Vec2 position, b2Vec2 distancia, bool condicional)
//     {
//         Step(1, false);
//         
//        if(condicional)
//         {
//             Foward();
//         }
//        else
//         {
//             Backward();
//         }
//
//         
//         int offset = 0;
//         int point = 0;
//         point = GetPoint();
//         
//         app->render->DrawTexture(textura,position.x + point * (offset + distancia.x), position.y + point * (offset + distancia.y));
//     }
};
#endif
