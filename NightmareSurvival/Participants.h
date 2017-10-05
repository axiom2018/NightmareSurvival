// Participants.h
#pragma once

// For Mediator pattern.

class Participants
{
public:
    virtual void OpenVendorShop() {}
    virtual int GetPlayerMoney() const { return -1; }
    virtual void SetPlayerMoney(int value) {} 
    virtual void DeliverPlayerItem(class Items *pItem) {}
};
