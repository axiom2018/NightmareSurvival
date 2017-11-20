// HealthManager.h
#pragma once

// Note: In areas of the code such as Player.cpp and all of the enemies, health related code can be managed and delegated in this interface.

class HealthManager
{
    int m_health;
public:
    HealthManager(int initialHealth);
    int GetHealth() const;
    void SetHealth(int health);
    bool DamageHealth(int damage);
};