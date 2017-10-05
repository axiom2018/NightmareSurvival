// Vampire.cpp
#include "Vampire.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"
#include "EnemyDamageRates.h"

Vampire::Vampire() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_windowWidth(0),
    m_windowHeight(0),
    m_symbol('%'),
    m_life(Life::Alive),
    m_health(6),
    m_x(10),
    m_y(10),
    // m_value(0),
    m_damage(VAMPIRE_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
{
    m_speed = 1;

    m_pSpawnPoint = new Spawn;
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);
}

void Vampire::Init(int width, int height)
{
    // Step 1. Width and height are required for EnemySpawn and FindPlayer algorithms.
    m_windowWidth = width;
    m_windowHeight = height;

    // Step 2. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x, m_windowWidth, m_windowHeight);
}

void Vampire::Draw()
{
    if (m_life == Life::Alive)
    {
        std::cout << m_symbol;
    }
}

void Vampire::Move()
{
    m_pCalculateMove->CalculateEnemyMove(&m_x, &m_y);
}

void Vampire::DecreaseHealth(int amount)
{
    if (m_health - amount <= 0)
    {
        m_health = 0;
        m_life = Life::Dead;
        // m_value = 60 + (rand() % 110);
        // m_pPlayer->AwardMoney(m_value);
    }

    else
    {
        m_health -= amount;
    }
}

bool Vampire::IsAlive()
{
    if (m_life == Life::Alive)
        return true;
    
    return false;
}

// After enemy has been killed by player, World.cpp will collect the money to award the player.
int Vampire::AwardMoney()
{
    return 60 + (rand() % 110);
}

Vampire::~Vampire()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
}
