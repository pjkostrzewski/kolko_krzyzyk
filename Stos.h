
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>


template<typename T>
class Stos
{
public:
	int Rozmiar; //rozm
	int MaxRozmiar; //maxrozm
	T *Tab; //tablica elementów stosu
	Stos(); //konstruktor
	~Stos(); //destruktor
	void Pop(); //usun
	void Push(const T &Obj); //wstaw

	T& operator[](int Index)
	{
		return Tab[Index];
	}
	int GetRozmiar(){ return Rozmiar; } //rozmiar
	void Clear(){ Rozmiar=0; } //czyœæ
};

template<typename T>
Stos<T>:: Stos()
{
	Rozmiar = 0;
	MaxRozmiar = 8;
	Tab = new T[MaxRozmiar];
}

template<typename T>
Stos<T>:: ~Stos()
{
	delete[] Tab;
}

template<typename T>
void Stos<T>:: Pop()
{
	if(Rozmiar>0) --Rozmiar;
}


template<typename T>
void Stos<T>:: Push(const T &Obj)
{
	if(Rozmiar>=MaxRozmiar)
	{
		MaxRozmiar*=2;
		T *NewTab = new T[MaxRozmiar];
		for(int i=0; i<Rozmiar; ++i) NewTab[i] = Tab[i];
		delete[] Tab;
		Tab = NewTab;
	}
	Tab[Rozmiar] = Obj;
	++Rozmiar;
}

