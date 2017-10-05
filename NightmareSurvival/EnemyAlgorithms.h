// EnemyAlgorithms.h
#pragma once

/* Strategy pattern used. https://en.wikibooks.org/wiki/Computer_Science_Design_Patterns/Strategy#/media/File:StrategyPatternClassDiagram.svg
   The enemies need a strategy to be able to choose a spawn point and also move. */

class EnemyAlgorithms
{
public:
    EnemyAlgorithms() {}
    virtual void SpawnPoint(int *y, int *x, int width, int height) {}
    virtual void CalculateEnemyMove(int *y, int *x) {}
    virtual ~EnemyAlgorithms() {}
};