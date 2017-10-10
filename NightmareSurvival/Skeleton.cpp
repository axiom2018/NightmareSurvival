// Skeleton.cpp
#include "Skeleton.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"
#include "EnemyDamageRates.h"

// Update: Make mediator so enemies don't communicate directly with player. Decoupling is good.

// Initialize settings with constructor.
Skeleton::Skeleton() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_windowWidth(0),
    m_windowHeight(0),
    m_symbol('1'),
    m_life(Life::Alive),
    m_health(2),
    m_x(1), /// Why calculate this when we do spawn manually?
    m_y(1),
    m_damage(SKELETON_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
    // m_value(0)
{
    m_speed = 3;

    m_pSpawnPoint = new Spawn;
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);
}

void Skeleton::Init(int width, int height)
{
    // Step 1. Width and height are required for EnemySpawn and FindPlayer algorithms.
    m_windowWidth = width;
    m_windowHeight = height;

    // Step 2. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x, m_windowWidth, m_windowHeight);
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
    if (m_health - amount <= 0)
    {
        m_health = 0;
        m_life = Life::Dead;
    }

    else
    {
        m_health -= amount;
    }
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
    return 30 + (rand() % 90);
}

// Handle memory.
Skeleton::~Skeleton()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
}