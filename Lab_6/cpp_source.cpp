#include <iostream>
#include <iomanip>
#include <cmath>
#include <locale.h>
using namespace std;

extern "C" bool task1_asm(int x);

void task1()
{

    cout << "--------------Задание 1---------------" << endl;
    int x;
    cout<<"Введите x:"<<endl;
    cin>>x;
    cout << "x = " << x << ", (x < 7) : " << task1_asm(x) << endl;
    cout << endl;
}

extern "C" bool task2_asm(int x);
void task2()
{

    int x;
    cout << "--------------Задание 2---------------" << endl;
    cout<<"Введите x:"<<endl;
    cin>>x;
    cout << "x = " << x << ", y= " << task2_asm(x) << endl;
    cout << endl;

}

void task3()
{

    double x,y;
    cout << "--------------Задание 3---------------" << endl;
    cout<<"Введите x:"<<endl;
    cin>>x;

    const double _7_3 = 7.3, _2_5 = 2.5;
    asm volatile (
    "	fldl	%[x]"			"\n"	// st(0) = x
    "	fldl	%[_7_3]"		"\n"	// st(0) = 7.3 | st(1) = x
    "	fcomip	%%st(1), %%st(0)"	"\n"	// сравниваем 7.3 с x, удаляем st(0): теперь st(0) = x
    "	jb	0f"			"\n"	// прыгаем, если меньше (7.3 < x, т.е. x > 7.3)
    "	fsin"				"\n"	// st(0) = sin(x)
    "	jmp	1f"			"\n"	// готово!
    "0:	fstp	%%st(0)"		"\n"	// удаляем st(0)
    "	fldl	%[_2_5]"		"\n"	// st(0) = 2.5
    "1:	fstpl	%[y]"			"\n"	// запись результата
    : [y]"=m"(y)				// выходные операнды
    : [x]"m"(x), [_7_3]"m"(_7_3), [_2_5]"m"(_2_5) // входные операнды
    : "%eax"					// разрушаемые регистры (memory - память, cc - флаги)
  );
    cout << "x = " << x << ", y= " << y<< endl;
    cout << endl;
}

void task4()
{
  cout << "--------------Задание 4---------------" << endl;
  int n;
  cout << "Введите количество членов последоватльности, которое хотите расчитать (N>0): ";
  cin >> n;
  if (n < 1) {
    cout << "Ошибка! Невозможное значение." << endl;
    return;
  }
  int x0;
  cout << "Введите первый член последовательности: ";
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
      "	cmovnz	%%edx, %%eax"		"\n"	// eax = edx, если x % 2 != 0
      "	mov	%%eax, %[xi]"		"\n"	// запись результата
      : [xi]"=m"(xi)				// выходные операнды
      : [x0]"m"(x0)				// входные операнды
      : "%eax", "%edx"				// разрушаемые регистры (memory - память, cc - флаги)
    );
    cout << "x" << i << " = " << xi << endl;
    x0 = xi;
  }
}

void task5()
{
  cout << "--------------Задание 5---------------" << endl;
  int n;
  cout << "Введите количество элементов в массиве (N>0): ";
  cin >> n;
  if (n < 1) {
    cout << "Ошибка! Невозможное значение." << endl;
    return;
  }
  int* x = new int[n];
  cout << "Введите первый элемент массива: ";
  cin >> *x;

  asm volatile (
    "	mov	%[n], %%ecx"		"\n"	// ecx = n
    "	dec	%%ecx"			"\n"	// ecx = n-1
    "	jz	3f"			"\n"	// выходим, если n = 1 (нужен только только x0)
    "	mov	%[x], %%edx"		"\n"	// edx = адрес массива
    "	mov	(%%edx), %%eax"		"\n"	// eax = x0
    "0:"				"\n"
    "	add	$4, %%edx"		"\n"	// переходим к следующему элементу массива
    "	test	$1, %%eax"		"\n"	// eax % 2 ?
    "	jz	1f"			"\n"	// прыгаем, если x % 2 == 0
    "	imul	$3, %%eax"		"\n"	// eax = 3 * x
    "	inc	%%eax"			"\n"	// eax = 3 * x + 1
    "	jmp	2f"			"\n"	// готово!
    "1:	shr	$1, %%eax"		"\n"	// eax = x / 2
    "2:	mov	%%eax, (%%edx)"		"\n"	// запись результата
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "3:"				"\n"
    :						// выходные операнды
    : [x]"m"(x), [n]"m"(n)			// входные операнды
    : "%eax", "%ecx", "%edx", "memory"		// разрушаемые регистры (memory - память, cc - флаги)
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

    cout << "--------------Задание 6---------------:" << endl;
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
