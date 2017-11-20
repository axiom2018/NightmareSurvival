// Vampire.cpp
#include "Vampire.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"

Vampire::Vampire() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_pHealthManager(nullptr),
    m_symbol('%'),
    m_life(Life::Alive),
    m_x(0),
    m_y(0),
    m_speed(VAMPIRE_SPEED),
    m_damage(VAMPIRE_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
{
    // Step 1. Init spawn point.
    m_pSpawnPoint = new Spawn;

    // Step 2. Init calculate move.
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);

    // Step 3. Init health manager.
    m_pHealthManager = new HealthManager(VAMPIRE_HEALTH);
}

void Vampire::Init()
{
    // Step 1. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x);
}

void Vampire::Draw()
{
    if (m_life == Life::Alive)
        std::cout << m_symbol;
}

void Vampire::Move()
{
    m_pCalculateMove->CalculateEnemyMove(&m_x, &m_y);
}

void Vampire::DecreaseHealth(int amount)
{
    if (m_pHealthManager->DamageHealth(amount))
        m_life = Life::Dead;
}

// Check if enemy is alive for drawing purposes.
bool Vampire::IsAlive()
{
    if (m_life == Life::Alive)
        return true;
    
    return false;
}

// After enemy has been killed by player, World.cpp will collect the money to award the player.
int Vampire::AwardMoney()
{
    return VAMPIRE_REWARD_LOW + (rand() % VAMPIRE_REWARD_HIGH);
}

WalletManagementParticipantTypes Vampire::GetType() const
{
    return m_participantType;
}

Vampire::~Vampire()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
    delete m_pHealthManager;
    m_pHealthManager = nullptr;
}
