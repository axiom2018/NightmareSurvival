// BulletManager.h
#pragma once
#include "Directions.h"
#include <vector>

// The bullet algorithm will guide bullet movement.

class BulletManager
{
private:
    std::vector<class Entities*> m_pBullets; 
    std::vector<class Enemies*> m_pSaveEnemies;
    int m_x; 
    int m_y; 
    int m_bulletX; 
    int m_bulletY; 
    int m_bulletSize; 
    int m_index;
    int m_size; 
    int m_amountOfEnemies;
    Directions m_direction;

    // Bullet creation helper functions.
    void SetData();
    void AlterData();

    // Updating bullets helper functions.
    bool CheckBulletSize();
    void ReturnBullet(int *pBulletIndex);
    void SouthBulletUpdate(int *pBulletIndex);
    void EastBulletUpdate(int *pBulletIndex);
    void WestBulletUpdate(int *pBulletIndex);
    void NorthBulletUpdate(int *pBulletIndex);
    void BulletUpdate(int *pBulletIndex);

    // Enemy collision helper functions.
    void CheckForEnemyCollision(int *pBulletIndex);
    void SetBulletPos(int bulletIndex);
    void DetermineBulletDirection(int bulletIndex);
public:
    BulletManager();
    void RequestBullet(int weaponId); 
    bool DrawBullets(int x, int y); 
    void UpdateBullets(); 
    bool EnemyCollision();
    void ReturnAllBulletsOnGameBoard();
    ~BulletManager();
};

