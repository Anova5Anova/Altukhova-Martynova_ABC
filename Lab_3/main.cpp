#include <iostream>
#include <locale.h>
#include <bitset>
using namespace std;
void check(unsigned int x,unsigned int y)//������� �� C++ ��� �������� ��������
{
    unsigned int z=(x+79)/y;
    unsigned int w=(x+79)%y;
    cout<<"��������:"<<endl;
    cout<<"z="<<z<<endl<<"w="<<w<<endl;
}

int main()
{
    setlocale(0,"");
    cout<<"--------------������� 1---------------"<<endl;
    unsigned int x = 5, y = 6;
    unsigned int z,w;
    asm(
       "add    $79, %[X]\n"
       "cltd\n"
       "div %[Y]\n"
	   :"=a"(z),"=d"(w)
       :[X]"a" (x), [Y]"c" (y)
       :"cc");
    cout<<"������� � ������� ������������ �������:"<<endl;
    cout<<"z="<<z<<endl<<"w="<<w<<endl;
    check(x,y);


    cout<<"--------------������� 2---------------"<<endl;
    unsigned int*p=&x;
    unsigned int*q=&y;
    int tmp1,tmp2;
     asm(
       "mov (%[X]),%%eax\n"
       "mov (%[Y]),%%ecx\n"
       "add  $79, %%eax\n"
       "cltd\n"
       "div %%ecx\n"
	   :"=a"(z),"=d"(w)
       :[X]"a" (p), [Y]"c" (q)
       :"cc");
    cout<<"������� � ������� ������������ �������:"<<endl;
    cout<<"z="<<z<<endl<<"w="<<w<<endl;
    check(x,y);

    cout<<"--------------������� 3---------------"<<endl;
     asm(
       "add  $79, %[X]\n"
       "mov %[X], %%eax\n"
       "cltd\n"
       "div %[Y]\n"
       "mov %%eax,%[Z]\n"
       "mov %%edx,%[W]\n"
	   :[Z]"=r"(z),[W]"=r"(w)
       :[X]"r" (x), [Y]"r" (y)
       :"cc","eax","edx");
    cout<<"������� � ������� ������������ �������:"<<endl;
    cout<<"z="<<z<<endl<<"w="<<w<<endl;
    check(x,y);

    cout<<"--------------������� 4---------------"<<endl;
    long long n = 10;
	int* Array = new int[n];

	asm("mov %[N], %%rcx\n"
        "Go:movl $0x0,-4(%[Array],%%rcx,4)\n"
        "dec %%rcx\n"
        "cmp $0,%%rcx\n"
        "jne Go\n"
        ::[N]"r"(n),[Array]"r"(Array)
        :"rcx"
         );

	for (size_t i = 0; i < n; i++)
	{
		cout << *(Array+i) << " ";
	};
	long long k=2;
	long long value=13;
	asm("mov %[Value],-4(%[Array],%[K],4)\n"
        ::[Array]"r"(Array),[K]"r"(k),[Value]"r"(value)
        :
        );
    cout << endl << "������ ������� ������� � �������  "<< k << " �����: " << *(Array+k-1)<<endl;;

    cout<<"--------------������� 5---------------"<<endl;
    long long j=5;
        asm("mov -4(%[Array],%[j],4),%%rbx\n"
            "mov $32,%%rcx\n"
            "Go1:bts %%rcx,%%rbx\n"
            "dec %%rcx\n"
            "cmp $23,%%rcx\n"
            "jne Go1\n"
            "mov %%rbx,-4(%[Array],%[j],4)\n"
            ::[Array]"r"(Array),[j]"r"(j)
            :"rbx","rcx"
           );
    cout << endl << "������ ������� ������� � �������  "<< j << " �����: " <<hex<<*(Array+j-1);

    return 0;

}
