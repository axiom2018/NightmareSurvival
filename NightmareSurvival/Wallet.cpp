// Wallet.cpp
#include "Wallet.h"

// Initialize wallet with proper type.
Wallet::Wallet() :
    m_money(0),
    m_participantType(WalletManagementParticipantTypes::Wallet)
{

}

void Wallet::ReceiveFunds(int value)
{
    m_money += value;
}

int Wallet::GetFunds() const
{
    return m_money;
}
