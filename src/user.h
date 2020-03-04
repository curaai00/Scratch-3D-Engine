#pragma once 

#include "IDrawable.h"
#include "bean.h"

class User : public IDrawable
{
public:
    User(float x, float y, rgba c);

public:
    void draw(SDL_Renderer* rend) override;

    void turn(SDL_Keycode dir);
    void move(SDL_Keycode dir);

public:
    rgba color;
    Point pos;    
    int size=20;
    int speed=10;
    float ori=90;
    float oriSensitivity=3;
};