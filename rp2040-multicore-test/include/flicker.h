#ifndef FLICKER_H
#define FLICKER_H

#include "Arduino.h"


double prng()
{
    uint32_t tail = ((time_us_64()*time_us_64())%1000000);
    return tail/1000000.0;
}

class Flicker
{
private:
    float s=0, v=0, a=0;
    float s_max=255, s_min=0,  v_max=10, v_min=-10, a_max=2, a_min=-2;
public:
    Flicker();
    ~Flicker();

    float update();
    float getVal();
};


Flicker::Flicker()
{
}


float Flicker::getVal()
{
    return this->s;
}


float Flicker::update()
{
    float ra = (prng() - 0.5)/10;
    this->a += ra;
    if(this->a > this->a_max) this->a=this->a_max;
    if(this->a < this->a_min) this->a=this->a_min;
    this->v = this->v + this->a;
    if(this->v > this->v_max)
    {
        this->v=this->v_max;
        this->a = -this->a;
    }
    if(this->v < this->v_min){
        this->v=this->v_min;
        this->a = -this->a;
    } 
    this->s = this->s + this->v;
    if(this->s > this->s_max) this->s=this->s_max;
    if(this->s < this->s_min) this->s=this->s_min;
    return ra;
}


Flicker::~Flicker()
{
}


#endif // FLICKER_H