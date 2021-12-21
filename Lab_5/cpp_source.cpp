#include <iostream>
#include <iomanip>
#include <cmath>
#include <locale.h>
using namespace std;

void task1()
{
    cout << "--------------������� 1---------------" << endl;

    cout << "��������� ��� ������� ���������� ���� float:" << endl;

    float Sd_float [3];
    float Sa_float [3];

    int n[3] = {1000,1000000,1000000000};

    for(int k = 0; k < 3; k++)
    {
        for(int i = 1; i <= n[k]; i++)
            Sd_float[k] += static_cast<float>(1)/i;
        for(int i = n[k]; i > 0; i--)
            Sa_float[k] += static_cast<float>(1)/i;
        cout << "n = " << n[k] << " : Sd = " << Sd_float[k] << ", Sa = " << Sa_float[k] << endl;
    }

    cout << "��������� ��� ������� ���������� ���� double:" << endl;

    double Sd_double [3];
    double Sa_double [3];

    for(int k = 0; k < 3; k++)
    {
        for(int i = 1; i <= n[k]; i++)
            Sd_double[k] += static_cast<double>(1)/i;
        for(int i = n[k]; i > 0; i--)
            Sa_double[k] += static_cast<double>(1)/i;
        cout << "n = " << n[k] << " : Sd = " << Sd_double[k] << ", Sa = " << Sa_double[k] << endl;
    }

    cout << endl;
}
double i_sequence_term2(unsigned long long int i)
{
    return pow(-1,i)*((i+1)/(pow(i,2)-1));
}

double two_sum(double& t, double a, double b)
{
    double s = a+b; // ����� ����� a � b

    // ���������� ����������� ���������� �����
    double bs = s-a;
    double as = s-bs;
    t = (b-bs)+(a-as);

    return s;
}
void task2()
{
    cout << "--------------������� 2---------------" << endl;
    double eps = pow(10,-6);

    double sum1 = 0; // ������� �������� ����� ��� ������� ���������
    double t = 0; // ������� �������� ����������� ��������� �����
    double t_i; // ����������� �� i-�� ��������

    // Rump�Ogita�Oishi algorithm
    for(int i = 2; abs(i_sequence_term2(i+1)) > eps; i++)
    {
        sum1 = two_sum(t_i,sum1,i_sequence_term2(i));
        t += t_i;
    }

    cout <<"sum = " << sum1+t << ", eps = " << eps << endl;
    cout << endl;
}

double i_sequence_term3(unsigned long long int i, double alpha)
{
    return 1.0/pow(i,alpha);
}

void task3()
{
    cout << "--------------������� 3---------------" << endl;
    double eps = pow(10,-6);
    double alpha;
    cout<<"������� �������� alpha:"<<endl;
    cin>>alpha;
    if (alpha<2)
    {
        cout<<"��� ����������"<<endl;
        return ;
    }

    double sum1 = 0; // ������� �������� ����� ��� ������� ���������
    double a_i = i_sequence_term3(1,alpha);
    double t = 0; // ������� �������� ����������� ��������� �����
    double t_i; // ����������� �� i-�� ��������

    for(int i = 1; a_i + i_sequence_term3(i+1,alpha-1)/(alpha-1) > eps; i++)
    {
        sum1 = two_sum(t_i,sum1,i_sequence_term3(i,alpha));
        t += t_i;
        a_i = i_sequence_term3(i+1,alpha);
    }

    cout << "sum = " << sum1+t << ", eps = " << eps << endl;
    cout << endl;
}

void task4()
{
  cout << "--------------������� 4---------------" << endl;
  double x;
  cout << "������� �������� x: ";
  cin >> x;

  double result;
  const double _7_9 = 7.9;
  asm volatile (
    "	fldl	%[x]"			"\n"	// st(0) = x
    "	fsin"				"\n"	// st(0) = sin(x)
    "	fsubrl	%[_7_9]"		"\n"	// st(0) = 7.9 - sin(x)
    "	fld1"				"\n"	// st(0) = 1.0 | st(1) = 7.9 - sin(x)
    "	fldl	%[x]"			"\n"	// st(0) = x | st(1) = 1.0 | st(2) = 7.9 - sin(x)
    "	fcos"				"\n"	// st(0) = cos(x) | st(1) = 1.0 | st(2) = 7.9 - sin(x)
    "	fsubrp"				"\n"	// st(0) = 1.0 - cos(x) | st(1) = 7.9 - sin(x)
    "	fdivrp"				"\n"	// st(0) = (7.9 - sin(x)) / (1.0 - cos(x))
    "	fstpl	%[result]"		"\n"	// ������ ����������, ���� ����
    : [result]"=m"(result)			// �������� ��������
    : [x]"m"(x), [_7_9]"m"(_7_9)		// ������� ��������
  );
  cout << "������� � ������� FPU: y= " << std::setprecision(6) << result << endl;
  cout<<"�������� �� C++: y="<<(7.9-sin(x))/(1.0-cos(x))<<endl;
}

void task5()
{
  cout << "--------------������� 5---------------" << endl;
  double x[4], y[4], z[4];
  cout << "������� ������ x (����� enter): ";
  cin >> x[0] >> x[1] >> x[2] >> x[3];
  cout << "������� y (����� enter): ";
  cin >> y[0] >> y[1] >> y[2] >> y[3];

  // ���������� ����� AVX ��� double
  asm volatile (
    "	vmovupd	(%[x]), %%ymm0"		"\n"	// xmm0 = ������ x
    "	vmulpd	(%[y]), %%ymm0, %%ymm0"	"\n"	// xmm0 *= ������ y
    "	vmovupd	%%ymm0, (%[z])"		"\n"	// ������ ����������
    :						// �������� ��������
    : [x]"r"(x), [y]"r"(y), [z]"r"(z)		// ������� ��������
    : "%ymm0", "memory"				// ����������� �������� (memory - ������, cc - �����)
  );
  cout << "z = [" << std::setprecision(6) << z[0] << ", " << z[1] << ", " << z[2] << ", " << z[3] <<"]"<< endl;
}
extern "C" double task6_cpp(double x, double y);
double task6_cpp(double x, double y)
{
    return 4.6*pow(x,y)-1.3;
}
/*int main()
{
    setlocale(0,"");
    //task1();
    //task2();
    //task3();
    //task4();
    task5();
    return 0;
}*/
