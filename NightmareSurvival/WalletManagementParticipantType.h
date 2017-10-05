// WalletManagementParticipantTypes.h
#pragma once

/* This enum exists to assist the WalletMediator.h/.cpp. The main problem was how to loop through the vector of 
WalletManagementParticipants in WalletMediator.cpp, and find the Wallet to continue distributing funds to player.
This problem is solved thanks to this enum, allowing the WalletMediator to know exactly what is what via an ID
system. 

Design pluses:
a) One might say after seeing this implemented, "Great, now everytime we add more enemies we'll have to come back
here and update this file." Not exactly. See in WalletMediator.cpp the function AddFundsToPlayersWallet() is 
strictly looking for the players wallet, which of course in the WalletMediators list of pointers. So giving
each specific enemy a value with this declared enum is completely unnecessary. No one has to give them any
unique type, they can return the same value for all I care. The point is, to distinguish the wallet from every
other entity inside of the list of pointers that WalletMediator.h/.cpp holds. So despite one initially thinking
this is a design flaw, it's actually a plus! */

enum class WalletManagementParticipantTypes
{
    Enemy,
    Wallet
};
