#pragma once
/// @brief Временное положение
volatile int32_t pheseTemp[6] = {0,0,0,0,0,0};

/// @brief Считывание изменения временного положения
void phaseTick()
{
    pheseTemp[0] += ( enc_1.get_phi() - pheseTemp[0] );
    pheseTemp[1] += ( enc_2.get_phi() - pheseTemp[1] );
    pheseTemp[2] += ( enc_3.get_phi() - pheseTemp[2] );
    pheseTemp[3] += ( enc_4.get_phi() - pheseTemp[3] );
    pheseTemp[4] += ( enc_5.get_phi() - pheseTemp[4] );
    pheseTemp[5] += ( enc_6.get_phi() - pheseTemp[5] );
}

/// @brief Синхронизация глобального и временного положений
void pheseSynchro()
{
    pheseTemp[0] = enc_1.get_phi();
    pheseTemp[1] = enc_2.get_phi();
    pheseTemp[2] = enc_3.get_phi();
    pheseTemp[3] = enc_4.get_phi();
    pheseTemp[4] = enc_5.get_phi();
    pheseTemp[5] = enc_6.get_phi();
}

/// @brief Сброс временного положения
void phese0()
{
    for(int i = 0; i < 6; i++)
    {
        pheseTemp[i] = 0;
    }
}