// Mediator.h
#pragma once
#include <list>
#include <string>

// Simple mediator pattern to govern who is allowed to communicate. This exercises decoupling.

class Mediator
{
    std::list<class Participants*> m_pParticipants;
public:
    void RegisterParticipant(class Participants *pParticipant);
    void OpenVendorShop(class Participants *pSender);
    int GetPlayerMoney(class Participants *pSender); 
    virtual void SetPlayerMoney(class Participants *pSender, int value);
    virtual void DeliverPlayerItem(class Participants *pSender, class Items *pItem);
};