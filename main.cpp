#include "stdafx.h"
#include "Gra.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
int main()
{ cout<<"Patryk Kostrzewski, 226441"<<endl;
cout<<"Aby zmienic wymiary planszy i zasady wygranej, \nnalezy edytowac zdefiniowane wartosci w pliku Game.h"<<endl<<endl;
cout<<endl<<endl<<endl<<"INSTRUKCJA:\n Strzalki sluza do poruszania kursorem, spacja do postawienia pionka\n\n(wcisnij ENTER)...";
    cin.get();
    //srand(std::time(0));
    int wybor = 1;

    while(wybor==1){

    Gra MojaGra;
    MojaGra.Start();
    cin.get();
    cin.get();
    cout<<"Wprowadz 1, aby zagrac ponownie.\n  Wprowadz cokolwiek, aby wyjsc: ";
    cin>> wybor;
    }
    system("cls");
    cout<<"Milego dnia"<<endl;
}
