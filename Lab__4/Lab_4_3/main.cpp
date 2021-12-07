#include <iostream>
#include <locale.h>
using namespace std;
extern "C" int fifth_arg(int arg1,int arg2,int arg3,int arg4,int arg5);
int fifth_arg(int arg1,int arg2,int arg3,int arg4,int arg5)
{

    setlocale(0,"");
    cout<<"Аргументы функции:"<<endl;
    cout<<"1 - "<<arg1<<endl;
    cout<<"2 - "<<arg2<<endl;
    cout<<"3 - "<<arg3<<endl;
    cout<<"4 - "<<arg4<<endl;
    cout<<"5 - "<<arg5<<endl;
    return arg5;
}

