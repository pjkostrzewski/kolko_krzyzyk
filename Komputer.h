#pragma once

#include "Stos.h"
#include "Kolor.h"
#include "Input.h"
#include "Core.h"

#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>




class Komputer
{
public:
    bool Ruch;
    Core *MainCore;
    Wektor_2 Najlepszy_Ruch; //najlepszy ruch
    int Sytuacja();
    void Tasuj(Stos<Wektor_2> &Wektor); //przetasowanie stosu obiektow typu Wektor_2
    void Aktualizuj(); //aktualizacja wynikow
    Wektor_2 ZwrocNajRuch(); //zwraca najlepszy mozliwy ruch do wykonania okreslony w wyniku dzialania algorytmu MinMax

    Komputer(Core *_MainCore) :	Ruch(1), MainCore(_MainCore)
    {;} //konstruktor
     //okresl sytuacje na planszy: 0:nie wiadomo, -1:przegrana/remis, 1:wygrana
    void Swap(Wektor_2 &A, Wektor_2 &B); //zamien ze soba dwa obiekty typu Wektor_2 #swap XD

    void RunMinMax(); //rozpoczynanie algorytmu MinMax(przeszukiwanie na pierwszej glebokosci)
    void MinMax(int &wynikTemp, bool TypeFigure, int Lvl); //algorytm MinMax na dalszych g³êbokosciach w zale¿nosci od obliczonego wyniku przewidzianych ruchów


};

int Komputer::Sytuacja(){
    int Win = MainCore->CheckWin(); //sprawdza wygrana

        if(Win==0) return 0;    //nic
        if(Win==1) return -1;   //wygra³o kolko
        if(Win==2) return 1;    //wygra³ krzyzyk
        if(Win==3) return -1;   //remis
    return 0;
}

void Komputer::Tasuj(Stos<Wektor_2> &Wektor){ //tasuje wszytskie mozlilwe ruchy

    for(int i=0; i<Wektor.GetRozmiar(); ++i)
    {
        Swap(Wektor[i], Wektor[rand()%Wektor.GetRozmiar()]); //zmienia kolejne elementy stosu Wektor miejscami z losowymi elementami
    }
}

void Komputer::Swap(Wektor_2 &A, Wektor_2 &B){

    Wektor_2 Temp;
    Temp = A;
    A = B;
    B = Temp;
}



/*
 * Ogolnie komputer chce miec wynik (Score) jak najwiekszy, wtedy wygrywa
 * a poszukuje drogi do jak najmniejszej ilosci wygranych gracza
 * i jak najwiekszej ilosci wygranej komputera (liczy delte)
 */

 void Komputer::Aktualizuj(){ //aktualizacja wynikow

    RunMinMax();
}

Wektor_2 Komputer::ZwrocNajRuch(){ //zwraca najlepszy mozliwy ruch do wykonania okreslony w wyniku dzialania algorytmu MinMax

    return Najlepszy_Ruch;
}

void Komputer::RunMinMax(){//rozpoczynanie algorytmu MinMax(przeszukiwanie na pierwszej g³êbokosci)

    int BestScore=-999; //BestScore(-999=-oo)
    Stos<Wektor_2> MozliwyRuch; //mozliwe ruchy
    for(int y=0; y<MainCore->Rozmiar.y; ++y)
        for(int x=0; x<MainCore->Rozmiar.x; ++x)
            if(MainCore->GetChar(Wektor_2(x,y))==' ') MozliwyRuch.Push(Wektor_2(x,y));
    Tasuj(MozliwyRuch);
    for(int i=0; i<MozliwyRuch.GetRozmiar(); ++i){

        Wektor_2 Temp(MozliwyRuch[i]);

        MainCore->PostawPionek(Temp, Ruch); //wstawienie oczekiwanej (nast w kolejnosci - tutaj zawsze X) figury w danym ruchu
        int wynikDelta = Sytuacja(); //ilosc pkt jaka zostanie dodana lub odjeta->
        if(wynikDelta>0){ //->jesli ten wynik bedzie>0
            Najlepszy_Ruch=Temp;
            MainCore->UsunPionek(Temp); //usuniecie pionka z planszy
            return;
            }
        int wynikTemp = wynikDelta;
        MinMax(wynikTemp, !Ruch, 0); //przeszukiwanie, tu po g³êbokosci "0"
        if(wynikTemp>BestScore){ //znaleniono lepszy ruch(za wieksza ilosc pkt)

            BestScore = wynikTemp;
            Najlepszy_Ruch = Temp;
            }
        MainCore->UsunPionek(Temp); //usuniecie pionka z planszy
    }
}

void Komputer::MinMax(int &wynikTemp, bool TypeFigure, int Lvl){ //algorytm MinMax na dalszych g³êbokosciach w zale¿nosci od obliczonego wyniku przewidzianych ruchów

    for(int y=0; y<MainCore->Rozmiar.y; ++y)
        for(int x=0; x<MainCore->Rozmiar.x; ++x)
            if(MainCore->GetChar(Wektor_2(x,y))==' '){

                Wektor_2 Temp(x,y);
                MainCore->PostawPionek(Temp, TypeFigure); //wstawienie oczekiwanej figury w danym ruchu
                int wynikDelta = Sytuacja(); //ilosc pkt jaka zostanie dodana lub odjêta
                if(Lvl>0 && wynikDelta>=0 && !MainCore->IsFull()) MinMax(wynikTemp, !TypeFigure, Lvl-1); //sprawdza czy Lvl>0 i czy plansza nie jest zape³niona i czy ruch nie spowodowa³ przegranej
                else wynikTemp+=wynikDelta; //w innym przypadku dodanie deltasc do wynikTemp
                MainCore->UsunPionek(Temp); //usuniecie pionka z planszy
            }
}

