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
    class InventoryManager *m_pInventoryManager;
    class BorderManagement *m_pBorderManagement;
    class Wallet *m_pWallet;

    char m_player;
    int m_health;
    int m_armor;
    int m_x;
    int m_y;
    int m_saveWorldWidth;
    int m_saveWorldHeight;
    int m_coolDown;
    Directions m_directions;
    std::string m_participantName;
    int m_playerInventorySize;

    void UseFirstAid();
    void UseArmor();
    void Reload();
    bool ArmorDamage(int damage);
    void AlterDirection(char key);

    bool ApplyUpgrade(int typeOfUpgrade, int index);
    bool UseUpgrade(int typeOfUpgrade);
public:
    Player(int worldWidth, int worldHeight);
    void DrawPlayer() const { std::cout << m_player; }
    bool UpdatePlayer();
    void DrawControls() const;
    void DrawStats() const;
    int GetX() const { return m_x; } 
    int GetY() const { return m_y; }
    // void Shoot();

    // bool DrawBullets(int x, int y); 
    // void EnemyCollision(); 
    // void UpdateBullets(); 
    void Damage(int damage); 
    
    Directions GetDirection() const { return m_directions; } 
    // void SetCurrentWeapon(class Items *pWeapon) { m_pCurrentWeapon = pWeapon; } 
    // void AddItemToInventory(class Items *pItem) { m_pInventory.push_back(pItem); }

    // Needed for World.cpp.
    class WalletManagementParticipants * GetWallet() const { return m_pWallet; }

    // virtual int GetPlayerMoney() const override { return m_money; };
    virtual int GetPlayerMoney() const override;
    virtual void SetPlayerMoney(int value) override;
    virtual void DeliverPlayerItem(class Items *pItem) override { AddItemToInventory(pItem); }

    ~Player();
};