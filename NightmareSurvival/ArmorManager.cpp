// ArmorManager.cpp
#include "ArmorManager.h"

// Set armor to 0 through constructor. Player does not begin game with armor.
ArmorManager::ArmorManager() :
    m_armor(0)
{

}

int ArmorManager::GetArmor() const
{
    return m_armor;
}

// Referenced in ArmorStrategy.cpp.
void ArmorManager::SetArmor(int armor)
{
    m_armor += armor; // Test first.
}

// Referenced in Player.cpp.
bool ArmorManager::DamageArmor(int damage)
{
    // Step 1. If armor was 0 to begin with, exit function
    if (m_armor <= 0)
        return false;

    // Step 2. If we haven't returned in step 1, apply armor damage.
    m_armor -= damage;
    return true;
}
