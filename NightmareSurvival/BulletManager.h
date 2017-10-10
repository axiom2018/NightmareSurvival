// BulletManager.h
#pragma once
#include "WeaponAlgorithms.h"
#include "Directions.h"
#include <vector>

// The bullet algorithm will guide bullet movement.

class BulletManager
{
private:
    // Primary variables.
    std::vector<class Entities*> m_pBullets; 
    std::vector<class Enemies*> m_pSaveEnemies; // No need to save enemies, get them directly.
    int m_x; // Save player X.
    int m_y; // Save player Y.
    int m_bulletX; // Save bullet position.
    int m_bulletY; // Save bullet position.
    int m_bulletSize; // Help bullet control.
    // int m_nextBulletPos; // Wtf does this shit even DO?
    int m_width; // 
    int m_height; //
    int m_index; // 
    int m_size; //
    int m_amountOfEnemies; //
    Directions m_direction; // 

    // Bullet creation helper functions.
    void SetData();
    void AlterData();

    // Updating bullets helper functions.
    bool CheckBulletBize();
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
    virtual void UpdateBullets();
    virtual int GetBulletSize() const { return m_pBullets.size(); }
    virtual bool EnemyCollision();
    ~BulletManager();
};

