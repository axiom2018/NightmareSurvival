// Enemies.h
#pragma once
#include "WalletManagementParticipants.h"
#include "WalletManagementParticipantType.h"

// Enemy system uses factory pattern.

class Enemies : public WalletManagementParticipants
{
protected:
    enum class Life
    {
        Alive,
        Dead,
    };
    
public:
    static Enemies *GetEnemy(int type);
    static int GetMaxEnemies();
    virtual void Init(int width, int height) = 0;
    virtual void Draw() = 0;
    virtual void Move() = 0;
    virtual int GetX() = 0;
    virtual int GetY() = 0;
    virtual int GetHealth() const = 0;
    virtual void DecreaseHealth(int amount) = 0;
    virtual bool IsAlive() = 0;
    virtual int AwardMoney() = 0;
    virtual ~Enemies() {}
};