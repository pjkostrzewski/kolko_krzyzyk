#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


struct InputManager
{
    int *KeyID, *Stan, Size;

    enum Key { UP,DOWN,LEFT,RIGHT,ENTER };
    InputManager() //konstruktor
    {
        Size = 5; //ilosc uzywanych klawiszy
        KeyID = new int[Size]{0x26,0x28,0x25,0x27,0x20}; //wartosci dla danych klawiszy spacja 0x20
        Stan = new int[Size]{};
    }
    ~InputManager() //destruktor
    {
        delete[] KeyID;
        delete[] Stan;
    }
    void Aktualizuj() //aktualizowanie statusu klawiszy
    {
        for(int i=0; i<Size; ++i)
        {
            if(Stan[i]==2 && !GetAsyncKeyState(KeyID[i])) Stan[i] = 0;
            if(Stan[i]==1) Stan[i] = 2;
            if(Stan[i]==0 && GetAsyncKeyState(KeyID[i])) Stan[i] = 1; //jesli jest 0 i jest trzymany klawisz to ustawi sie na 1
        }
    }
    bool Click(int ID){ return Stan[ID]==1; }
    bool Keep(int ID){ return Stan[ID]==2; }
    bool Unkeep(int ID){ return Stan[ID]==0; }
} Input;
