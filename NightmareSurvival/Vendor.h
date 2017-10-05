// Vendor.h
#pragma once
#include "Entities.h"
#include <vector>
#include <iostream>
#include "Participants.h"

// After the player clears a level, they'll receive an opportunity to buy weapons and upgrades from the vendor NPC.

class Vendor : public Participants
{
private:
    class Mediator *m_pMediator;
    class WeaponsFactory *m_pWF;
    class UpgradeFactory *m_pUF;
    class Items *m_pItem;
    std::vector<std::pair<class Items*, int>> m_pProducts;
    const int k_upgradePrice = 100; // Universal upgrade price. 
    char m_cursor;
    char m_marker;
    bool m_displayShop;
    int m_currentChosenIndex;
    int m_weaponTracker;
    int m_upgradeTracker;
    int m_max;
    int m_price;
    int m_productSize;

    void DeleteItemPointer(class Items *pItem);
    void GetAllWeapons();
    void GetAllUpgrades(); 

    void OpenVendorsShop();
    void NormalCursorMovement(int *pIndex, char direction);
    void MoveCursorDown(int *pIndex, char direction);
    void MoveCursorUp(int *pIndex, char direction);
    void Selection(int *index, char direction);
    bool Transaction(int listedIndex);
    void AddItem(int listedIndex);
    void PurchaseItem();
    bool ProcessPlayerInput(char input);
    void DisplayVendorControls();
    void DisplayVendorMessage();
    void DisplayPurchaseOptions();
public:
    Vendor(class Mediator *pMediator);
    virtual void OpenVendorShop() override;
    void DeleteVendor();
};

