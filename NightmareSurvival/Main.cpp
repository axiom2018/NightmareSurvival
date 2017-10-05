// Main.cpp
#include <iostream>
#include <conio.h>
#include <time.h>
#include "vld.h"
#include "World.h"
#include "WeaponsFactory.h"
#include "Items.h"
#include <list>
#include <string>

int main()
{
    srand(unsigned int(time(0)));

    World::Instance()->CreateWorld();

    while (World::Instance()->CheckIsGameRunning())
    {
        World::Instance()->Update();
    }

    World::Instance()->DeleteWorld();

    _getch();

    return 0;
}