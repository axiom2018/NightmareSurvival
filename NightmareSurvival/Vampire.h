// Vampire.h
#pragma once
#include "Enemies.h"

class Vampire : public Enemies
{
    class EnemyAlgorithms *m_pSpawnPoint;
    class EnemyAlgorithms *m_pCalculateMove;
    int m_windowWidth;
    int m_windowHeight;
    char m_symbol;
    Life m_life;
    int m_health;
    int m_x;
    int m_y;
    int m_speed;
    // int m_value;
    WalletManagementParticipantTypes m_participantType;
    int m_damage;
public:
    Vampire();
    virtual void Init(int width, int height) override;
    virtual void Draw() override;
    virtual void Move() override;
    virtual int GetX() override { return m_x; }
    virtual int GetY() override { return m_y; }
    virtual int GetHealth() const override { return m_health; }
    virtual void DecreaseHealth(int amount) override;
    virtual bool IsAlive() override;
    virtual int AwardMoney() override;
    virtual WalletManagementParticipantTypes GetType() const override { return m_participantType; }
    ~Vampire();
};