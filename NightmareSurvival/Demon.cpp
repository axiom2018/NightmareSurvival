// Demon.cpp
#include "Demon.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"

Demon::Demon() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_pHealthManager(nullptr),
    var(232),
    m_symbol(var),
    m_life(Life::Alive),
    m_x(0),
    m_y(0),
    m_speed(DEMON_SPEED),
    m_damage(DEMON_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
{
    // Step 1. Init spawn point.
    m_pSpawnPoint = new Spawn;

    // Step 2. Init calculate move.
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);

    // Step 3. Init health manager.
    m_pHealthManager = new HealthManager(DEMON_HEALTH);
}

void Demon::Init()
{
    // Step 1. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x);
}

void Demon::Draw()
{
    if (m_life == Life::Alive)
    {
        std::cout << m_symbol;
    }
}

void Demon::Move()
{
    m_pCalculateMove->CalculateEnemyMove(&m_x, &m_y);
}

void Demon::DecreaseHealth(int amount)
{
    if (m_pHealthManager->DamageHealth(amount))
        m_life = Life::Dead;
}

// Check if enemy is alive for drawing purposes.
bool Demon::IsAlive()
{
    if (m_life == Life::Alive)
        return true;
    
    return false;
}

// After enemy has been killed by player, World.cpp will collect the money to award the player.
int Demon::AwardMoney()
{
    return DEMON_REWARD_LOW + (rand() % DEMON_REWARD_HIGH);
}

WalletManagementParticipantTypes Demon::GetType() const
{
    return m_participantType;
}

Demon::~Demon()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
    delete m_pHealthManager;
    m_pHealthManager = nullptr;
}