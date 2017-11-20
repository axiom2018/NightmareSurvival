// HealthManager.cpp
#include "HealthManager.h"

// Save health upon pointer declaration of this class.
HealthManager::HealthManager(int initialHealth) :
    m_health(initialHealth)
{

}

// Referenced in Player.cpp.
int HealthManager::GetHealth() const
{
    return m_health;
}

// Referenced in FirstAidStrategy.cpp.
void HealthManager::SetHealth(int health)
{
    m_health = health;
}

// Apply damage.
bool HealthManager::DamageHealth(int damage)
{
    // Step 1. Calculate remaining health.
    int remainder = m_health - damage;

    // Step 2. If no health remains, return true, entity is now dead.
    if (remainder <= 0)
    {
        m_health = 0;
        return true;
    }

    // Step 3. If Step 2 didn't return, apply regular damage.
    m_health -= damage;

    // Step 4. Return.
    return false;
}
