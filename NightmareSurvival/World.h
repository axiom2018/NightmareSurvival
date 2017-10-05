// World.h
#pragma once
#include <vector>
#include <queue>

// Manage the game.

class World
{
private:
    World();
    static World *_instance;
    class Entities **m_ppSpace;
    class Player *m_pPlayer;
    class EnemyManagement *m_pEnemyManagement;
    class Mediator *m_pMediator;
    class WalletMediator *m_pWalletMediator;
    class Vendor *m_pVendor;
    const int k_columns = 35;
    const int k_rows = 20;
    bool m_gameRunning;

    void MoveToNextLevel();
    void UpdateWorld();
    void UpdateBullets();

    bool DrawBullets(int x, int y);
    bool DrawPlayer(int x, int y);
public:
    static World *Instance();
    void CreateWorld();
    bool CheckIsGameRunning() const { return m_gameRunning; }
    void Update();
    void TerminateGame() { m_gameRunning = false; }
    int GetWidth() const { return k_columns; }
    int GetHeight() const { return k_rows; }
    int GetPlayerCurrency() const;
    class Entities **GetSpace() const { return m_ppSpace; } 
    class WalletMediator * GetWalletMediator() const { return m_pWalletMediator; }
    class EnemyManagement * GetEnemyManager() const { return m_pEnemyManagement; }
    class Player *GetPlayer() const { return m_pPlayer; } 
    std::pair<int, int> GetPlayerPosition() const;
    void DeleteWorld();
};