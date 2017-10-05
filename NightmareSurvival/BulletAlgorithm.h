// BulletAlgorithm.h
#pragma once
#include "WeaponAlgorithms.h"
#include "Directions.h"
#include <vector>

// The bullet algorithm will guide bullet movement.

class BulletAlgorithm : public WeaponAlgorithms
{
private:
    // Primary variables.
    std::vector<class Entities*> m_pBullets; 
    std::vector<class Enemies*> m_pSaveEnemies;
    int m_x;
    int m_y;
    int m_bulletX;
    int m_bulletY;
    int m_bulletSize; 
    int m_nextBulletPos;
    int m_width;
    int m_height;
    int m_index;
    int m_size;
    int m_amountOfEnemies;
    Directions m_direction;

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
    BulletAlgorithm(int width, int height);
    virtual void BulletManager(int weaponId) override;
    virtual bool DrawBullets(int x, int y) override;
    virtual void UpdateBullets() override;
    virtual int GetBulletSize() const override { return m_pBullets.size(); }
    virtual bool EnemyCollision() override;
    ~BulletAlgorithm();
};

