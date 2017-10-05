// WalletMediator.cpp
#include "WalletMediator.h"
#include "Wallet.h"
#include "WalletManagementParticipants.h"
#include "WalletManagementParticipantType.h"

// Allow participants to sign up for registration.
void WalletMediator::RegisterParticipant(WalletManagementParticipants * pParticipant)
{
    m_pParticipants.push_back(pParticipant);
}

// Send money over to player.
void WalletMediator::AddFundsToPlayersWallet(int value)
{
    // Step 1. Loop through list.
    for each (WalletManagementParticipants *pParticipants in m_pParticipants)
    {
        // Step 2. Find wallet.
        if (pParticipants->GetType() == WalletManagementParticipantTypes::Wallet)
        {
            // Step 3. Once wallet is found, add funds.
            pParticipants->ReceiveFunds(value);
            return;
        }
    }
}

// Removing a participant occurs when an enemy dies, AFTER giving currency to the players wallet. 
void WalletMediator::RemoveParticipant(WalletManagementParticipants * pDeleteParticipant)
{
    for each (WalletManagementParticipants *pParticipants in m_pParticipants)
    {
        if (pParticipants == pDeleteParticipant)
        {
            m_pParticipants.remove(pDeleteParticipant);
            return;
        }
    }
}
