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
    cout<<"--------------������� 1---------------"<<endl;
    int x=1,y=0;
    cout <<"������� � ������� ������ �� ����������: z="<< foo(x, y) <<endl;
    cout<<"��������: z="<<check(x,y)<<endl;
    return 0;
}
