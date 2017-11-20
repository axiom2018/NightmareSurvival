// Boss.cpp
#include "Boss.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"

Boss::Boss() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_pHealthManager(nullptr),
    var(225),
    m_symbol((char)225),
    m_life(Life::Alive),
    m_x(0),
    m_y(0),
    m_speed(BOSS_SPEED),
    m_damage(BOSS_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
{
    // Step 1. Init spawn point.
    m_pSpawnPoint = new Spawn;

    // Step 2. Init calculate move.
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);

    // Step 3. Init health manager.
    m_pHealthManager = new HealthManager(BOSS_HEALTH);
}

void Boss::Init()
{
    // Step 1. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x);
}

void Boss::Draw()
{
    if (m_life == Life::Alive)
        std::cout << m_symbol;
}

void Boss::Move()
{
    m_pCalculateMove->CalculateEnemyMove(&m_x, &m_y);
}

void Boss::DecreaseHealth(int amount)
{
    if (m_pHealthManager->DamageHealth(amount))
        m_life = Life::Dead;
}

// Check if enemy is alive for drawing purposes.
bool Boss::IsAlive()
{
    if (m_life == Life::Alive)
        return true;

    return false;
}

// After enemy has been killed by player, World.cpp will collect the money to award the player.
int Boss::AwardMoney()
{
    return BOSS_REWARD_LOW + (rand() % BOSS_REWARD_HIGH);
}

WalletManagementParticipantTypes Boss::GetType() const
{
    return m_participantType;
}

Boss::~Boss()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
    delete m_pHealthManager;
    m_pHealthManager = nullptr;
}