// Boss.h
#pragma once
#include "Enemies.h"

class Boss : public Enemies
{
    class EnemyAlgorithms *m_pSpawnPoint;
    class EnemyAlgorithms *m_pCalculateMove;
    class HealthManager *m_pHealthManager;
    int var;
    char m_symbol;
    Life m_life;
    int m_x;
    int m_y;
    int m_speed;
    WalletManagementParticipantTypes m_participantType;
    int m_damage;
public:
    Boss();
    virtual void Init() override;
    virtual void Draw() override;
    virtual void Move() override;
    virtual int GetX() override { return m_x; }
    virtual int GetY() override { return m_y; }
    virtual void DecreaseHealth(int amount) override;
    virtual bool IsAlive() override;
    virtual int AwardMoney() override;
    virtual WalletManagementParticipantTypes GetType() const override;
    ~Boss();
};