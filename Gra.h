#pragma once
#include "Stos.h"
#include "Kolor.h"
#include "Input.h"
#include "Core.h"
#include "Komputer.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


/*======================*/

#define iloscwierszy 3
#define ilosckolumn 3           // TUTAJ MOZNA ZMIENIC PARAMETRY GRY
#define wygrana 3

/*======================*/



class Gra
{
public:

    int Win, a,c;
    Wektor_2 Kursor;
    Core MyCore;

    bool Ruch;
    bool Wyswietl_bool;

    Komputer MojKomputer;
    //MyCore(Wektor_2(4,4),4) odpowiada za plansze->(4,4) rozmiar planszy, ( , ),4) ilosc znakow w rzedzie
    //Gra(): MyCore(Wektor_2(a,a),c), MojKomputer(&MyCore), Ruch(false), Win(0), Wyswietl_bool(true) //konstruktor
    //{;}
    Gra(): MyCore(Wektor_2(iloscwierszy,ilosckolumn),wygrana), MojKomputer(&MyCore), Ruch(false), Win(0), Wyswietl_bool(true) //konstruktor
    {;}
    void KontrolaKursora(); //ustawianie pozycji kursora za pomoca klawiszy WSAD
    void Aktualizuj(); //aktualizacja ruchow
    void Wyswietl(); //Wyswietlenie planszy
    void Start(); //glowna pêtla gry
};

void Gra::Wyswietl() //Wyswietl_boolenie planszy
{
    MyCore.Wyswietl(Kursor);
}

void Gra::Start() //glowna pêtla gry
{
    Wyswietl();
    while(!Win)
    {
        Aktualizuj(); //aktualizowanie gry
        if(Wyswietl_bool) { Wyswietl(); Wyswietl_bool = false; } //Wyswietlanie
        Input.Aktualizuj(); //aktualizowanie statusu klawiszy
    }
    if(Win==1) std::cout<<"Wygrana! \n";
    else if(Win==2) std::cout<<"Przegrana! \n";
    else if(Win==3) std::cout<<"Remis\n";
}

void Gra::KontrolaKursora() //ustawianie pozycji kursora za pomoca klawiszy WSAD
{
        Wektor_2 NextPos(Kursor);
        if(Input.Click(InputManager::Key::UP)) --NextPos.y; //gora
        if(Input.Click(InputManager::Key::DOWN)) ++NextPos.y; //dól
        if(Input.Click(InputManager::Key::LEFT)) --NextPos.x; //lewo
        if(Input.Click(InputManager::Key::RIGHT)) ++NextPos.x; //prawo
        if(MyCore.IsOnMapa(NextPos) && NextPos!=Kursor)
    {
        Wyswietl_bool = true;
        Kursor = NextPos;
    }
}

void Gra::Aktualizuj() //aktualizacja ruchów
{
    if(Ruch==0) //Gracz O
    {
        KontrolaKursora();
        if(Input.Click(InputManager::Key::ENTER) && MyCore.PostawPionek(Kursor, Ruch))
        {
            Wyswietl_bool = true;
            Win = MyCore.CheckWin();
            Ruch=!Ruch;
        }
    }
    else //Komputer X
    {
        std::cout<<"Oczekiwanie na ruch...\n";
        MojKomputer.Aktualizuj();
        if(MyCore.PostawPionek(MojKomputer.ZwrocNajRuch(), Ruch))
        {
            Wyswietl_bool = true;
            Win = MyCore.CheckWin();
            Ruch=!Ruch;
        }
    }
}



