// Player.h
#pragma once
#include "Directions.h"
#include <vector>
#include <iostream>
#include "Participants.h"
#include "Wallet.h"

// Player management.

class Player : public Participants
{
private:
    std::vector<class Items*> m_pInventory;
    class WeaponAlgorithms *m_pBulletControl;
    class WeaponsFactory *m_pWF;
    class PlayerAlgorithms *m_pCycleInventory;
    class Items *m_pCurrentWeapon;
    // class Mediator *m_pMediator;
    class BorderManagement *m_pBorderManagement;
    class Wallet *m_pWallet;

    char m_player;
    int m_health;
    int m_armor;
    int m_money;
    int m_x;
    int m_y;
    int m_saveWorldWidth;
    int m_saveWorldHeight;
    int m_coolDown;
    Directions m_directions;
    std::string m_participantName;
    int m_playerInventorySize;

    void CycleWeaponInventory();
    bool WeaponCoolDown();
    bool WeaponAmmunitionCheck(int weaponAmmo) const;

    int GetBulletsSize() const;
    void UseFirstAid();
    void UseArmor();
    void Reload();
    bool ArmorDamage(int damage);
    void AlterDirection(char key);

    bool ApplyUpgrade(int typeOfUpgrade, int index);
    bool UseUpgrade(int typeOfUpgrade);
    bool CheckAreaForBorders(char key);
public:
    Player(int worldWidth, int worldHeight);
    void DrawPlayer() const { std::cout << m_player; }
    bool UpdatePlayer();
    void DrawControls() const;
    void DrawStats() const;
    int GetX() const { return m_x; } 
    int GetY() const { return m_y; }
    void Shoot();

    bool DrawBullets(int x, int y); 
    void EnemyCollision(); 
    void UpdateBullets(); 
    // Make wallet a participant.
    void AwardMoney(int x) { m_money += x; } 
    void Damage(int damage); 
    
    Directions GetDirection() const { return m_directions; } 
    void SetCurrentWeapon(class Items *pWeapon) { m_pCurrentWeapon = pWeapon; } 
    // int GetMoney() const { return m_money; }
    // void SetMoney(int value) { m_money = value; } 
    void AddItemToInventory(class Items *pItem) { m_pInventory.push_back(pItem); }

    // Needed for World.cpp.
    class WalletManagementParticipants * GetWallet() const { return m_pWallet; }

    virtual int GetPlayerMoney() const override { return m_money; };
    virtual void SetPlayerMoney(int value) override { m_money = value; }
    virtual void DeliverPlayerItem(class Items *pItem) override { AddItemToInventory(pItem); }

    ~Player();
};