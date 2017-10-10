// Boss.cpp
#include "Boss.h"
#include "Spawn.h"
#include "CalculateMove.h"
#include "Player.h"
#include "EnemyDamageRates.h"

Boss::Boss() :
    m_pSpawnPoint(nullptr),
    m_pCalculateMove(nullptr),
    m_windowWidth(0),
    m_windowHeight(0),
    var(225),
    m_symbol((char)225),
    m_life(Life::Alive),
    m_health(35),
    m_x(10),
    m_y(10),
    // m_value(0),
    m_damage(BOSS_DAMAGE),
    m_participantType(WalletManagementParticipantTypes::Enemy)
{
    m_speed = 0;

    m_pSpawnPoint = new Spawn;
    m_pCalculateMove = new CalculateMove(m_speed, m_damage);
}

void Boss::Init(int width, int height)
{
    // Step 1. Width and height are required for EnemySpawn and FindPlayer algorithms.
    m_windowWidth = width;
    m_windowHeight = height;

    // Step 2. Set enemy spawn point.
    m_pSpawnPoint->SpawnPoint(&m_y, &m_x, m_windowWidth, m_windowHeight);
}

void Boss::Draw()
{
    if (m_life == Life::Alive)
    {
        std::cout << m_symbol;
    }
}

void Boss::Move()
{
    m_pCalculateMove->CalculateEnemyMove(&m_x, &m_y);
}

void Boss::DecreaseHealth(int amount)
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

bool Boss::IsAlive()
{
    if (m_life == Life::Alive)
        return true;

    return false;
}

// After enemy has been killed by player, World.cpp will collect the money to award the player.
int Boss::AwardMoney()
{
    return 100 + (rand() % 200);
}

Boss::~Boss()
{
    delete m_pSpawnPoint;
    m_pSpawnPoint = nullptr;
    delete m_pCalculateMove;
    m_pCalculateMove = nullptr;
}