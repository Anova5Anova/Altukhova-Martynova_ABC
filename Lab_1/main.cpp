#include <cstddef>
#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

template<typename T>
void print_size(string type_name)
{
    cout << type_name <<": " << (sizeof(T)) << endl;
}
template<class T>
void __print(string type, T value)
{
  cout << type << "16-����� �������������: " << hex << value << endl;
  cout << type << "10-����� �������������: " << dec << value << endl;
}


void print16(void *p)
{
  __print("������������� ����������� �������������,",*(reinterpret_cast<unsigned short*>(p)));
  __print("������������� �������� �������������,", *(reinterpret_cast<short*>(p)));
    cout<<endl;
}

void print32(void* p)
{
   __print("������������� ����������� �������������,",*(reinterpret_cast<unsigned int*>(p)));
   __print("������������� �������� �������������,", *(reinterpret_cast<int*>(p)));
   cout<<"������������� � �������� ����� � ��������� �������:"<<*(reinterpret_cast<float*>(p))<<endl<<endl;
}

void print64(void* p)
{
   __print("������������� ����������� �������������,",*(reinterpret_cast<unsigned long long*>(p)));
   __print("������������� �������� �������������,", *(reinterpret_cast<long long*>(p)));
   cout<<"������������� � �������� ����� � ��������� �������:"<<*(reinterpret_cast<double*>(p))<<endl<<endl;

}

void CastSignedFrom16To32(short p)
{
	int signed_res32 = static_cast<int> (p);
    cout<<"���������� 2 -������� ���������� �������������� ��������"<<endl;
    print32(&signed_res32);
}

void CastUnsignedFrom16To32(unsigned short p)
{
	unsigned int unsigned_res32 = static_cast<unsigned int> (p);
    cout<<"���������� 1 -������� ���������� �������������� �����������"<<endl;
    print32(&unsigned_res32);
}

void printDump(void* p, size_t N)
{
  cout << hex;
  auto pb = (uint8_t*)p;
  for(size_t i = 0; i < N; ++i)
  {
    cout << (int)pb[i] << " ";
  }
  cout << endl << dec;
}

int main()
{
    setlocale(0,"");
    cout<<"--------------������� 1---------------"<<endl;
    cout<<"�������� � ������� ������, ���������� ���������� ������ ������:"<<endl;
    print_size<char>("char");
    print_size<signed char>("signed char");
    print_size<unsigned char>("unsigned char");
    print_size<char*>("char*");
    print_size<wchar_t>("wchar_t");
    print_size<wchar_t*>("wchar_t*");
    print_size<short>("short");
    print_size<short*>("short*");
    print_size<int>("int");
    print_size<int*>("int*");
    print_size<long>("long");
    print_size<long*>("long*");
    print_size<long long>("long long");
    print_size<long long*>("long long*");
    print_size<float>("float");
    print_size<float*>("float*");
    print_size<double>("double");
    print_size<double*>("double*");
    print_size<long double>("long double");
    print_size<long double*>("long double*");
    cout<<"--------------------------------------"<<endl;

    cout<<"--------------������� 2---------------"<<endl;
    unsigned int min_unsigned_16bit=0b0000000000000000;
    unsigned int max_unsigned_16bit=0b1111111111111111;
    int min_signed_16bit=0b1000000000000000;
    int max_signed_16bit=0b0111111111111111;
    int y=0b0000000000000011;
    int z=0b1111111111111000;
    cout<<"������������� ����� 0b0000000000000000"<<endl;
    print16(&min_unsigned_16bit);
    cout<<"������������� ����� 0b1111111111111111"<<endl;
    print16(&max_unsigned_16bit);
    cout<<"������������� ����� 0b1000000000000000"<<endl;
    print16(&min_signed_16bit);
    cout<<"������������� ����� 0b0111111111111111"<<endl;
    print16(&max_signed_16bit);
    cout<<"������������� ����� "<<y<<endl;
    print16(&y);
    cout<<"������������� ����� "<<z<<endl;
    print16(&z);
    cout<<"--------------------------------------"<<endl;

    cout<<"--------------������� 3---------------"<<endl;
    //32
    unsigned int min_unsigned_32bit=0b00000000000000000000000000000000;
    unsigned int max_unsigned_32bit=0b11111111111111111111111111111111;
    int min_signed_32bit=0b10000000000000000000000000000000;
    int max_signed_32bit=0b01111111111111111111111111111111;
    cout<<"������������� ����� 0b00000000000000000000000000000000"<<endl;
    print32(&min_unsigned_32bit);
    cout<<"������������� ����� 0b11111111111111111111111111111111"<<endl;
    print32(&max_unsigned_32bit);
    cout<<"������������� ����� 0b10000000000000000000000000000000"<<endl;
    print32(&min_signed_32bit);
    cout<<"������������� ����� 0b01111111111111111111111111111111"<<endl;
    print32(&max_signed_32bit);


    int ix = 0xA1B2C3D4;
    int iy = 3;
    int iz = -8;
    cout <<"������������� ����� 0xA1B2C3D4 ��� ��������������:" <<endl;
    print32(&ix);
    cout <<"������������� ����� 3 ��� ��������������:"<< endl;
    print32(&iy);
    cout <<"������������� ����� -8 ��� ��������������:"<< endl;
    print32(&iz);
    cout << endl;

    float fx = 0xA1B2C3D4;
    float fy = 3;
    float fz = -8;
    cout <<"������������� ����� 0xA1B2C3D4 � ��������� �������:" <<endl;
    print32(&fx);
    cout <<"������������� ����� 3 � ��������� �������:"<< endl;
    print32(&fy);
    cout <<"������������� ����� -8 � ��������� �������:" <<endl;
    print32(&fz);
    cout << endl;

    // 64
    unsigned long long min_unsigned_64bit=0b0000000000000000000000000000000000000000000000000000000000000000;
    unsigned long long max_unsigned_64bit=0b1111111111111111111111111111111111111111111111111111111111111111;
    long long min_signed_64bit=0b1000000000000000000000000000000000000000000000000000000000000000;
    long long max_signed_64bit=0b0111111111111111111111111111111111111111111111111111111111111111;
    cout<<"������������� ����� 0b0000000000000000000000000000000000000000000000000000000000000000"<<endl;
    print64(&min_unsigned_64bit);
    cout<<"������������� ����� 0b1111111111111111111111111111111111111111111111111111111111111111"<<endl;
    print64(&max_unsigned_64bit);
    cout<<"������������� ����� 0b1000000000000000000000000000000000000000000000000000000000000000"<<endl;
    print64(&min_signed_64bit);
    cout<<"������������� ����� 0b0111111111111111111111111111111111111111111111111111111111111111"<<endl;
    print64(&max_signed_64bit);


    long long lx = 0xA1B2C3D4;
    long long ly = 3;
    long long lz = -8;
    cout <<"������������� ����� 0xA1B2C3D4 ��� ��������������:" <<endl;
    print64(&lx);
    cout <<"������������� ����� 3 ��� ��������������:"<< endl;
    print64(&ly);
    cout <<"������������� ����� -8 ��� ��������������:"<< endl;
    print64(&lz);
    cout << endl;

    double dx = 0xA1B2C3D4;
    double dy = 3;
    double dz = -8;
    cout <<"������������� ����� 0xA1B2C3D4 � ��������� �������:" <<endl;
    print64(&dx);
    cout <<"������������� ����� 3 � ��������� �������:"<< endl;
    print64(&dy);
    cout <<"������������� ����� -8 � ��������� �������:" <<endl;
    print64(&dz);
    cout << endl;

    cout<<"--------------������� 4---------------"<<endl;
    short y__ = 3;
    short z__ = -8;
    cout<<"������� ��������:"<<endl;
    print16(&y__);
    CastUnsignedFrom16To32(y__);
    CastSignedFrom16To32(y__);

    cout<<"������� ��������:"<<endl;
    print16(&z__);
    CastUnsignedFrom16To32(z__);
	CastSignedFrom16To32(z__);

    cout<<"--------------������� 4---------------"<<endl;
    int x = 0xA1B2C3D4;
    cout <<"����� �����" <<endl;
    printDump(&x, sizeof(int));
    auto arr = new int[3]{(int)0xA1B2C3D4, 3, -8};
    cout <<"������" << endl;
    printDump(arr, sizeof(int) * 3);
    delete[] arr;
    double _y = 3;
    cout <<"����� � ��������� �������" << endl;
    printDump(&_y, sizeof(double));
    cout <<"������" << endl;
    char str1[] = "bcdxy";
    printDump(&str1, sizeof(char) * 6); // 5 chars + 0
    char str2[] = "�����";
    printDump(&str2, sizeof(char) * 11);
    cout <<"������� ������" << endl;
    wchar_t wstr1[] = L"bcdxy";
    printDump(&wstr1, sizeof(wchar_t) * 6);



}
