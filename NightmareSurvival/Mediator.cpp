// Mediator.cpp
#include "Mediator.h"
#include "Participants.h"
#include "World.h"
#include "Player.h"
#include <iostream>
// Simple mediator pattern to govern who is allowed to communicate. This exercises decoupling.

void Mediator::RegisterParticipant(Participants * pParticipant)
{
    m_pParticipants.push_back(pParticipant); 

    /*
    if (pParticipant == (Participants*)World::Instance()->GetPlayer())
    {
        std::cout << "Hey, whatdya know, it's the player person!\n";
    }

    else
    {
        std::cout << "Wtf\n";
    }
    */
}

void Mediator::OpenVendorShop(Participants * pSender)
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

int Mediator::GetPlayerMoney(Participants * pSender)
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

void Mediator::SetPlayerMoney(Participants * pSender, int value)
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

void Mediator::DeliverPlayerItem(Participants * pSender, class Items *pItem)
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
