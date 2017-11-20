// Wallet.h
#pragma once
#include "WalletManagementParticipants.h"
#include "WalletManagementParticipantType.h"

// The Wallet interface will be how the player's money gets managed.

class Wallet : public WalletManagementParticipants
{
    WalletManagementParticipantTypes m_participantType;
    int m_money;
public:
    Wallet();
    virtual void AddFunds(int value) override;
    virtual void ReceiveChange(int value) override;
    virtual WalletManagementParticipantTypes GetType() const override { return m_participantType; }
    int GetFunds() const;
};