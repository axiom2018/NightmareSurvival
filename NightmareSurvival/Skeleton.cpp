// Skeleton.cpp
#include "Skeleton.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"

// Initialize settings with constructor.
Skeleton::Skeleton() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_pHealthManager(nullptr),
    m_symbol('1'),
    m_life(Life::Alive),
    m_x(0),
    m_y(0),
    m_speed(SKELETON_SPEED),
    m_damage(SKELETON_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
{
    // Step 1. Init spawn point.
    m_pSpawnPoint = new Spawn;

    // Step 2. Init calculate move.
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);

    // Step 3. Init health manager.
    m_pHealthManager = new HealthManager(SKELETON_HEALTH);
}

void Skeleton::Init()
{
    // Step 1. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x);
}

void Skeleton::Draw()
{
    if (m_life == Life::Alive)
    {
        std::cout << m_symbol;
    }
}

void Skeleton::Move()
{
    m_pCalculateMove->CalculateEnemyMove(&m_x, &m_y);
}

// Enemy health control, and award player if enemy has been killed.
void Skeleton::DecreaseHealth(int amount)
{
    if (m_pHealthManager->DamageHealth(amount))
        m_life = Life::Dead;
}

// Check if enemy is alive for drawing purposes.
bool Skeleton::IsAlive()
{
    if (m_life == Life::Alive)
        return true;

    return false;
}

// After enemy has been killed by player, World.cpp will collect the money to award the player.
int Skeleton::AwardMoney()
{
    return SKELETON_REWARD_LOW + (rand() % SKELETON_REWARD_HIGH);
}

WalletManagementParticipantTypes Skeleton::GetType() const
{
    return m_participantType;
}

// Handle memory.
Skeleton::~Skeleton()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
    delete m_pHealthManager;
    m_pHealthManager = nullptr;
}