// VendorMediator.cpp
#include "VendorMediator.h"
#include "Participants.h"
#include "World.h"
#include "Player.h"
#include <iostream>

// Simple mediator pattern to govern who is allowed to communicate. This exercises decoupling.

void VendorMediator::RegisterParticipant(Participants * pParticipant)
{
    m_pParticipants.push_back(pParticipant); 
}

void VendorMediator::OpenVendorShop(Participants * pSender)
{
    for each (Participants *pParticipants in m_pParticipants)
    {
        if (pParticipants != pSender)
        {
            pParticipants->OpenVendorShop();
            return;
        }
    }
}

int VendorMediator::GetPlayerMoney(Participants * pSender)
{
    for each (Participants *pParticipants in m_pParticipants)
    {
        if (pParticipants != pSender)
        {
            return pParticipants->GetPlayerMoney();
        }
    }

    return 0;
}

void VendorMediator::SetPlayerMoney(Participants * pSender, int value)
{
    for each (Participants *pParticipants in m_pParticipants)
    {
        if (pParticipants != pSender)
        {
            pParticipants->SetPlayerMoney(value);
            return;
        }
    }
}

void VendorMediator::DeliverPlayerItem(Participants * pSender, class Items *pItem)
{
    for each (Participants *pParticipants in m_pParticipants)
    {
        if (pParticipants != pSender)
        {
            pParticipants->DeliverPlayerItem(pItem);
            return;
        }
    }
}
