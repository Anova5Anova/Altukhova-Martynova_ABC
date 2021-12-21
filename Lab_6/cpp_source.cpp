#include <iostream>
#include <iomanip>
#include <cmath>
#include <locale.h>
using namespace std;

extern "C" bool task1_asm(int x);

void task1()
{

    cout << "--------------������� 1---------------" << endl;
    int x;
    cout<<"������� x:"<<endl;
    cin>>x;
    cout << "x = " << x << ", (x < 7) : " << task1_asm(x) << endl;
    cout << endl;
}

extern "C" bool task2_asm(int x);
void task2()
{

    int x;
    cout << "--------------������� 2---------------" << endl;
    cout<<"������� x:"<<endl;
    cin>>x;
    cout << "x = " << x << ", y= " << task2_asm(x) << endl;
    cout << endl;

}

void task3()
{

    double x,y;
    cout << "--------------������� 3---------------" << endl;
    cout<<"������� x:"<<endl;
    cin>>x;

    const double _7_3 = 7.3, _2_5 = 2.5;
    asm volatile (
    "	fldl	%[x]"			"\n"	// st(0) = x
    "	fldl	%[_7_3]"		"\n"	// st(0) = 7.3 | st(1) = x
    "	fcomip	%%st(1), %%st(0)"	"\n"	// ���������� 7.3 � x, ������� st(0): ������ st(0) = x
    "	jb	0f"			"\n"	// �������, ���� ������ (7.3 < x, �.�. x > 7.3)
    "	fsin"				"\n"	// st(0) = sin(x)
    "	jmp	1f"			"\n"	// ������!
    "0:	fstp	%%st(0)"		"\n"	// ������� st(0)
    "	fldl	%[_2_5]"		"\n"	// st(0) = 2.5
    "1:	fstpl	%[y]"			"\n"	// ������ ����������
    : [y]"=m"(y)				// �������� ��������
    : [x]"m"(x), [_7_3]"m"(_7_3), [_2_5]"m"(_2_5) // ������� ��������
    : "%eax"					// ����������� �������� (memory - ������, cc - �����)
  );
    cout << "x = " << x << ", y= " << y<< endl;
    cout << endl;
}

void task4()
{
  cout << "--------------������� 4---------------" << endl;
  int n;
  cout << "������� ���������� ������ �����������������, ������� ������ ��������� (N>0): ";
  cin >> n;
  if (n < 1) {
    cout << "������! ����������� ��������." << endl;
    return;
  }
  int x0;
  cout << "������� ������ ���� ������������������: ";
  cin >> x0;
  cout << "x" << 0 << " = " << x0 << endl;
  for (int i = 1; i < n; ++i) {
    int xi;
    asm volatile (
      "	mov	%[x0], %%eax"		"\n"	// eax = x
      "	imul	$3, %%eax, %%edx"	"\n"	// edx = 3 * x
      "	inc	%%edx"			"\n"	// edx = 3 * x + 1
      "	shr	$1, %%eax"		"\n"	// eax = x / 2
      "	testl	$1, %[x0]"		"\n"	// eax % 2 ?
      "	cmovnz	%%edx, %%eax"		"\n"	// eax = edx, ���� x % 2 != 0
      "	mov	%%eax, %[xi]"		"\n"	// ������ ����������
      : [xi]"=m"(xi)				// �������� ��������
      : [x0]"m"(x0)				// ������� ��������
      : "%eax", "%edx"				// ����������� �������� (memory - ������, cc - �����)
    );
    cout << "x" << i << " = " << xi << endl;
    x0 = xi;
  }
}

void task5()
{
  cout << "--------------������� 5---------------" << endl;
  int n;
  cout << "������� ���������� ��������� � ������� (N>0): ";
  cin >> n;
  if (n < 1) {
    cout << "������! ����������� ��������." << endl;
    return;
  }
  int* x = new int[n];
  cout << "������� ������ ������� �������: ";
  cin >> *x;

  asm volatile (
    "	mov	%[n], %%ecx"		"\n"	// ecx = n
    "	dec	%%ecx"			"\n"	// ecx = n-1
    "	jz	3f"			"\n"	// �������, ���� n = 1 (����� ������ ������ x0)
    "	mov	%[x], %%edx"		"\n"	// edx = ����� �������
    "	mov	(%%edx), %%eax"		"\n"	// eax = x0
    "0:"				"\n"
    "	add	$4, %%edx"		"\n"	// ��������� � ���������� �������� �������
    "	test	$1, %%eax"		"\n"	// eax % 2 ?
    "	jz	1f"			"\n"	// �������, ���� x % 2 == 0
    "	imul	$3, %%eax"		"\n"	// eax = 3 * x
    "	inc	%%eax"			"\n"	// eax = 3 * x + 1
    "	jmp	2f"			"\n"	// ������!
    "1:	shr	$1, %%eax"		"\n"	// eax = x / 2
    "2:	mov	%%eax, (%%edx)"		"\n"	// ������ ����������
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "3:"				"\n"
    :						// �������� ��������
    : [x]"m"(x), [n]"m"(n)			// ������� ��������
    : "%eax", "%ecx", "%edx", "memory"		// ����������� �������� (memory - ������, cc - �����)
  );
  for (int i = 0; i < n; ++i) {
    cout << "x[" << i << "] = " << *(x+i) << endl;
  }
  delete[] x;
}

extern "C" double task6_asm(double eps);

void task6()
{
    double eps = pow(10,-6);

    cout << "--------------������� 6---------------:" << endl;
    cout << "Sum = " << task6_asm(eps) << endl;
}
int main()
{
    setlocale(0,"");
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    task6();
    return 0;
}
