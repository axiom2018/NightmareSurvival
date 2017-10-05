// WalletManagementParticipants.h
#pragma once
#include "WalletManagementParticipantType.h"
// For the WalletMediator.h/.cpp.
class WalletManagementParticipants
{
public:
    virtual WalletManagementParticipantTypes GetType() const = 0;
    virtual void ReceiveFunds(int value) {} // For player.
};
