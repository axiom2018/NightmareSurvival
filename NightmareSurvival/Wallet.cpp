// Wallet.cpp
#include "Wallet.h"

// Initialize wallet with proper type.
Wallet::Wallet() :
    m_money(0),
    m_participantType(WalletManagementParticipantTypes::Wallet)
{

}

// While killing enemies, add all the reward received and have the amount stack.
void Wallet::AddFunds(int value)
{
    m_money += value;
}

// The mediator will supply the change after player makes a purchase.
void Wallet::ReceiveChange(int value)
{
    m_money = value;
}

int Wallet::GetFunds() const
{
    return m_money;
}
