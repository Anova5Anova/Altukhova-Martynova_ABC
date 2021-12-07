#include <iostream>
#include <locale.h>
using namespace std;
extern "C" unsigned foo(unsigned x, unsigned y);

int check(int x, int y)
{
    return 1234+x-5*y;
}
int main()
{
    setlocale(0,"");
    cout<<"--------------Задание 1---------------"<<endl;
    int x=1,y=0;
    cout <<"Решение с помощью модуля на ассемблере: z="<< foo(x, y) <<endl;
    cout<<"Проверка: z="<<check(x,y)<<endl;
    return 0;
}
