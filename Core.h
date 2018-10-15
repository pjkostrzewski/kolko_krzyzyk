#pragma once

#include "Stos.h"
#include "Kolor.h"
#include "Input.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>



class Core
{
public:
    int n;
    char **Mapa;
    Wektor_2 Rozmiar;
    Stos<Wektor_2> Pionki[2];

    Core(const Wektor_2 &_Rozmiar, int _n) : Rozmiar(_Rozmiar), n(_n) 
    {
        Mapa = new char*[Rozmiar.x];
        for(int i=0; i<Rozmiar.x; ++i)
        {
            Mapa[i] = new char[Rozmiar.y]{};
            for(int j=0; j<Rozmiar.y; ++j) Mapa[i][j]=' ';
        }
    }
    ~Core()
    {
        for(int i=0; i<Rozmiar.x; ++i) delete[] Mapa[i];
        delete[] Mapa;
    }

    bool IsOnMapa(const Wektor_2 &Pos); //czy pozycja Pos nalezy do planszy
    void Wyswietl(const Wektor_2 &Cursor); //wyswietlenie planszy
    char GetSymbol(bool Turn); //pobranie symbolu O lub X
    bool IsFull(); //czy plansza jest zapelniona figurami <=> czy remis
    void AktualizujPionki(); //wypelnianie stosow z figurami
    char& GetChar(const Wektor_2 &Pos); //zwracanie znaku na konkretnej pozycji na planszy
    int CheckWin(); //sprawdzenie wygranej, jezeli 0:nic, 1:wygrywa O, 2:wygrywa
    bool PostawPionek(const Wektor_2 &Pos, bool Turn); //postawienie figury Turn(0lubX) na pozycji Pos na planszy
    void UsunPionek(const Wektor_2 &Pos); //usuniecie figury z planszy na pozycji Pos

};


char Core::GetSymbol(bool Turn)
{
    return (Turn?'O':'X');
}

bool Core::IsFull()
{
    return Pionki[0].GetRozmiar()+Pionki[1].GetRozmiar()==Rozmiar.x*Rozmiar.y;
}

void Core::AktualizujPionki()
{
    for(int f=0; f<2; ++f)
    {
        Pionki[f].Clear();
        for(int x=0; x<Rozmiar.x; ++x)
            for(int y=0; y<Rozmiar.y; ++y)
                if(GetSymbol(f)==GetChar(Wektor_2(x,y))) Pionki[f].Push(Wektor_2(x,y));
    }
}

char& Core::GetChar(const Wektor_2 &Pos)
{
    return Mapa[Pos.x][Pos.y];
}



bool Core::IsOnMapa(const Wektor_2 &Pos)
{
    return (Pos.x>=0 && Pos.y>=0 && Pos.x<Rozmiar.x && Pos.y<Rozmiar.y);
}

void Core::Wyswietl(const Wektor_2 &Cursor)
{
    system("cls");
    for(int i=0; i<Rozmiar.y; ++i)
    {
        for(int j=0; j<Rozmiar.x; ++j)
        {
            SetTextKolor_enum(Kolor_enum::White);
            std::cout<<(Cursor==Wektor_2(j,i)?"|+":"| "); //dla kursora i nawiasow
            if(Mapa[j][i]=='X') SetTextKolor_enum(Kolor_enum::Blue); //niebieski dla O
            else if(Mapa[j][i]=='O') SetTextKolor_enum(Kolor_enum::Red); //czerwony dla X
            std::cout<<Mapa[j][i];
            SetTextKolor_enum(Kolor_enum::White);
            std::cout<<'|';
            SetTextKolor_enum(Kolor_enum::White);
        }
        std::cout<<'\n';
    }
}

bool Core::PostawPionek(const Wektor_2 &Pos, bool Turn)
{
    if(GetChar(Pos)==' ')
    {
        GetChar(Pos)=GetSymbol(Turn);
        return true;
    }
    return false;
}

int Core::CheckWin(){

    Wektor_2 TabV[4] = {Wektor_2(1,0), Wektor_2(1,1), Wektor_2(0,1), Wektor_2(-1,1)};

    AktualizujPionki();
    for(int turn=0; turn<2; ++turn){

        for(int f=0; f<Pionki[turn].GetRozmiar(); ++f){

            for(int v=0; v<4; ++v){

                Wektor_2 V(TabV[v]);
                Wektor_2
                 Temp(Pionki[turn][f]);

                bool IsWin = true;
                for(int i=0; i<n; ++i){

                    if(!IsOnMapa(Temp) || GetChar(Temp)!=GetSymbol(turn)){

                        IsWin = false;
                        break;
                    }
                    Temp = Temp+V;
                }
                if(IsWin) return turn+1;
            }
        }
    }
    if(IsFull()) return 3;
    return 0;
}


void Core::UsunPionek(const Wektor_2 &Pos)
{
    GetChar(Pos)=' ';
}


