#pragma once
#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <ctime>


struct Wektor_2 //wektor dwóch zmiennych
{
    int x,y;
    Wektor_2(int _x, int _y):x(_x),y(_y){;}
    Wektor_2():x(0),y(0){;}
    Wektor_2(const Wektor_2 &Obj):x(Obj.x),y(Obj.y){;}
    bool operator==(const Wektor_2 &Obj) const { return x==Obj.x && y==Obj.y; }
    bool operator!=(const Wektor_2 &Obj) const { return x!=Obj.x || y!=Obj.y; }
    void Set(int _x, int _y){x=_x; y=_y;}
    Wektor_2& operator=(const Wektor_2 &Obj){ x=Obj.x; y=Obj.y; return *this; }
    Wektor_2 operator+(const Wektor_2 &Obj){ return Wektor_2(x+Obj.x, y+Obj.y); }
};

/*
 * Nadanie kolorów znakom w konsoli
 */
enum class Kolor_enum
{
    // Red=0x0c, Blue=0x07, White=0x0f, Grey=0x08
     Blue=0x0b, Red=0x0d, White=0x0f,
};

/*
*SetConsoleTextAttribute-zmienia atrybuty dla znaków wyświetlanych w konsoli
*GetStdHandle - uchwyt do bufora ekranu konsoli
*/
void SetTextKolor_enum(Kolor_enum Kolor_enum) {     //tak bylo na internecie
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(Kolor_enum));
}



