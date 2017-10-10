// World.h
#pragma once
#include <vector>
#include <queue>

// Manage the game.

class World
{
private:
    World();
    static World *m_pInstance;
    class Entities **m_ppSpace;
    class EnemyManagement *m_pEnemyManagement;

    class Player *m_pPlayer;
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
    bool CheckBorder(int index) const;
    class WalletMediator * GetWalletMediator() const { return m_pWalletMediator; }
    class EnemyManagement * GetEnemyManager() const { return m_pEnemyManagement; }
    class Player *GetPlayer() const { return m_pPlayer; }
    bool CheckIsGameRunning() const { return m_gameRunning; }
    int GetWidth() const { return k_columns; }
    int GetHeight() const { return k_rows; }
    void Update();
    void TerminateGame();
    void DeleteWorld();
};