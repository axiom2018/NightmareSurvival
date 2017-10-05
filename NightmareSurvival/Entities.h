// Entities.h
#pragma once
#include <iostream>
#include "Directions.h"
#include <vector>

class Entities
{
private:
    Directions direction;
public:
    virtual void Draw() const {};
    virtual char GetChar() { return 0; };
    virtual ~Entities() {}

    virtual void Init() {}
    virtual void Update() {};
    virtual int GetId() const { return 0; };
    virtual int GetX() const { return 0; };
    virtual int GetY() const { return 0; };
    virtual void SetX(int x) {}
    virtual void SetY(int y) {}
    virtual void SetDirection(Directions direction) {};
    virtual Directions GetDirection() const { return direction; };
    virtual void EnemyCollision() {}
    virtual int GetBulletDamage() const { return 0; }
};