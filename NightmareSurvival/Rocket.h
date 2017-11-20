// Rocket.h
#pragma once
#include "Entities.h"
#include "Definitions.h"

class Rocket : public Entities
{
private:
    char m_bullet;
    Directions m_direction;
    int m_x;
    int m_y;
public:
    Rocket();
    virtual void Draw() const override { std::cout << m_bullet; }
    virtual void Update() override;
    virtual int GetId() const override { return ROCKET; }
    virtual void SetX(int x) override { m_x = x; }
    virtual void SetY(int y) override { m_y = y; }
    virtual int GetX() const override { return m_x; }
    virtual int GetY() const override { return m_y; }
    virtual void SetDirection(Directions direction) override { m_direction = direction; }
    virtual Directions GetDirection() const override { return m_direction; }
    virtual int GetBulletDamage() const override { return ROCKET_DAMAGE; }
};

