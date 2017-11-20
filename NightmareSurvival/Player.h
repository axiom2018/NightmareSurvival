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
    class HealthManager *m_pHealthManager;
    class ArmorManager *m_pArmorManager;
    class Wallet *m_pWallet;
    char m_player;
    int m_ammunition;
    int m_x;
    int m_y;
    Directions m_direction;
    std::string m_participantName;

    void AlterDirection(char key);
public:
    Player();
    void DrawPlayer() const;
    bool UpdatePlayer();
    void DrawControls() const;
    void DrawStats() const;
    class WalletManagementParticipants * GetWallet() const;
    class HealthManager * GetHealthManager() const;
    class ArmorManager * GetArmorManager() const;
    int GetX() const;
    int GetY() const;
    Directions GetDirection() const;
    void Damage(int damage);
    void ResetPlayerPosition();

    virtual int GetPlayerMoney() const override;
    virtual void SetPlayerMoney(int value) override;
    virtual void DeliverPlayerItem(class Items *pItem) override;
    ~Player();
};