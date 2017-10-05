// Demon.cpp
#include "Demon.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"
#include "EnemyDamageRates.h"

Demon::Demon() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_windowWidth(0),
    m_windowHeight(0),
    var(232),
    m_symbol(var),
    m_life(Life::Alive),
    m_health(15),
    m_x(8),
    m_y(10),
    // m_value(0),
    m_damage(DEMON_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
{
    m_speed = 2;

    m_pSpawnPoint = new Spawn;
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);
}

void Demon::Init(int width, int height)
{
    // Step 1. Width and height are required for EnemySpawn and CalculateMove algorithms.
    m_windowWidth = width;
    m_windowHeight = height;

    // Step 2. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x, m_windowWidth, m_windowHeight);
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
    if (m_health - amount <= 0)
    {
        m_health = 0;
        m_life = Life::Dead;
        // m_value = 40 + (rand() % 150);
        // m_pPlayer->AwardMoney(m_value);
    }

    else
    {
        m_health -= amount;
    }
}

bool Demon::IsAlive()
{
    if (m_life == Life::Alive)
        return true;
    
    return false;
}

// After enemy has been killed by player, World.cpp will collect the money to award the player.
int Demon::AwardMoney()
{
    return 40 + (rand() % 150);
}

Demon::~Demon()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
}