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
    class VendorMediator *m_pMediator;
    class WeaponsFactory *m_pWF;
    class UpgradeFactory *m_pUF;
    std::vector<std::pair<class Items*, int>> m_pProducts;
    class Items *m_pItem;
    class CursorManager *m_pCursorManager;
    bool m_displayShop;
    int m_weaponTracker;
    int m_upgradeTracker;
    int m_max;
    int m_price;
    int m_productSize;

    void DeleteItemPointer(class Items *pItem);
    void GetAllWeapons();
    void GetAllUpgrades(); 

    void OpenVendorsShop();
    bool Transaction(int listedIndex);
    void AddItem(int listedIndex);
    void PurchaseItem();
    void DisplayVendorControls();
    void DisplayVendorMessage();
    void DisplayPurchaseOptions();
public:
    Vendor(class VendorMediator *pMediator);
    virtual void OpenVendorShop() override;
    void DeleteVendor();
};

