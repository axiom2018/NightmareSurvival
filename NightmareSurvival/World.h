// World.h
#pragma once
#include <vector>
#include <queue>

class World
{
private:
    World();
    static World *m_pInstance;
    class Entities **m_ppSpace;
    class EnemyManagement *m_pEnemyManagement;
    class Player *m_pPlayer;
    class BulletManager *m_pBulletManager;
    class VendorMediator *m_pVendorMediator;
    class WalletMediator *m_pWalletMediator;
    class Vendor *m_pVendor;
    bool m_gameRunning;

    bool MoveToNextLevel();
    void UpdateWorld();
    bool DrawPlayer(int x, int y);
public:
    static World *Instance();
    void CreateWorld();
    bool CheckIsGameRunning() const;
    class WalletMediator *GetWalletMediator() const;
    class EnemyManagement *GetEnemyManager() const;
    class BulletManager *GetBulletManager() const;
    class Player *GetPlayer() const;
    bool CheckBorder(int index) const;
    void Update();
    void TerminateGame();
    void DeleteWorld();
};