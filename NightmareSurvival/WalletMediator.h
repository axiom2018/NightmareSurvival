// WalletMediator.h
#pragma once
#include <list>
#include <string>

/* 9-29-2017: The purpose of WalletMediator is to decouple the current connection of Player and all other enemies. Currently, when a
player defeats an enemy, that enemy has a saved reference of player which they can all the AwardMoney() function that is in the players
interface. We'll have a wallet to manage all the players money which is of course a decent use of delegating. Then we'll make the wallet
and Enemies communicate to manage the players money, but the communication is decoupled since this mediator will exist. So 2 things
accomplished with this:

a) Enemies no longer have a reference to player. (Decoupled).
b) Players money is delegated somewhere else for management. */

class WalletMediator
{
    std::list<class WalletManagementParticipants*> m_pParticipants;
public:
    void RegisterParticipant(class WalletManagementParticipants *pParticipant);
    void AddFundsToPlayersWallet(int value);
    void RemoveParticipant(class WalletManagementParticipants *pDeleteParticipant);
};