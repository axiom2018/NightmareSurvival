// WaveManager.h 
#pragma once
#include "Waves.h"

// Manages each wave of enemies the player has to combat.

class WaveManager
{   
    Waves m_curWave;
    int m_currentWave;
    class WaveManagerRequestEnemyStrategy *m_pEnemyTypeStrategy;
    int m_waveRequest;
public:
    WaveManager();
    int GetCurrentWave() const;
    bool IsGameOver() const;
    bool NextWave();
    int RequestEnemyType();
    ~WaveManager();
};