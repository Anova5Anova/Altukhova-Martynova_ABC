//#pragma pack(4)

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

// Лабораторная работа 7.1.
void lab7_1()
{
  cout << "Lab 7.1." << endl;

  const int rows = 5, cols = 7;
  int M[rows][cols];
  cout << "const int rows = 5, cols = 7;" << endl;
  cout << "int M[rows][cols];" << endl;
  cout << "Size of element = " << sizeof(M[0][0]) << endl;
  cout << "Adjacent row elements address = " << (char*)(&M[0][1]) - (char*)(&M[0][0]) << endl;
  cout << "Adjacent column elements address = " << (char*)(&M[1][0]) - (char*)(&M[0][0]) << endl;
  cout << "Size of matrix = " << sizeof(M) << endl;
  cout << "Address of element in row i column j = (int*)((char*)(M) + (i*cols + j)*sizeof(int)) = (int*)((char*)(M) + (i*7 + j)*4)" << endl;
}

// Лабораторная работа 7.2.
void lab7_2()
{
  cout << "Lab 7.2." << endl;
  // Эта функция будет работать только на 32-битной платформе
  if (sizeof(void*) != 4) {
    cout << "This code can work in 32-bit platforms only!" << endl;
    return;
  }

  int n;
  cout << "Enter natural number of elements: ";
  cin >> n;
  if (n < 1) {
    cout << "Illegal value." << endl;
    return;
  }

  int* alpha = new int[n];
  for (int i = 0; i < n; ++i) {
    cout << "Enter alpha[" << i << "]: ";
    cin >> alpha[i];
  }
  int result;
  asm volatile (
    "	mov	%[n], %%ecx"		"\n"	// ecx = n
    "	mov	%[alpha], %%edx"	"\n"	// edx = адрес массива
    "	xor	%%eax, %%eax"		"\n"	// eax = сумма (пока 0)
    "0:"				"\n"
    "	add	(%%edx), %%eax"		"\n"	// eax += alpha[i]
    "	add	$4, %%edx"		"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "	mov	%%eax, %[result]"	"\n"	// запись результата
    : [result]"=m"(result)			// выходные операнды
    : [alpha]"m"(alpha), [n]"m"(n)		// входные операнды
    : "%eax", "%ecx", "%edx"			// разрушаемые регистры (memory - память, cc - флаги)
  );
  cout << "Sum of elements = " << result << endl;
  delete[] alpha;

  // Бонус
  cout << endl;
  const int rows = 5, cols = 7;
  int M[rows][cols] = {
      {  1,  2,  3,  4,  5,  6,  7 },
      { -1, -2, -3, -4, -5, -6, -7 },
      { 70, 60, 50, 40, 30, 20, 10 },
      { 11, 22, 33, 44, 55, 66, 77 },
      { -3, -2, -1,  0,  1,  2,  3 },
    };
  cout << "const int rows = 5, cols = 7;" << endl;
  cout << "int M[rows][cols] = {" << endl;
  cout << "    {  1,  2,  3,  4,  5,  6,  7 }," << endl;
  cout << "    { -1, -2, -3, -4, -5, -6, -7 }," << endl;
  cout << "    { 70, 60, 50, 40, 30, 20, 10 }," << endl;
  cout << "    { 11, 22, 33, 44, 55, 66, 77 }," << endl;
  cout << "    { -3, -2, -1,  0,  1,  2,  3 }," << endl;
  cout << "  };" << endl;

  int i;
  cout << "Enter row number (0.." << rows-1 << "): ";
  cin >> i;
  if (i < 0 || i > rows-1) {
    cout << "Illegal value." << endl;
    return;
  }
  asm volatile (
    "	mov	%[cols], %%ecx"		"\n"	// ecx = cols
    "	mov	%[M], %%edx"		"\n"	// edx = адрес массива
    "	mov	%%ecx, %%ebx"		"\n"
    "	imul	%[i], %%ebx"		"\n"	// ebx = кол-во элементов до текущей строки
    "	xor	%%eax, %%eax"		"\n"	// eax = сумма (пока 0)
    "0:"				"\n"
    "	add	(%%edx,%%ebx,4), %%eax"	"\n"	// eax += элемент строки i из M
    "	inc	%%ebx"			"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "	mov	%%eax, %[result]"	"\n"	// запись результата
    : [result]"=m"(result)			// выходные операнды
    : [M]"r"(&M), [cols]"m"(cols), [i]"m"(i)	// входные операнды
    : "%eax", "%ebx", "%ecx", "%edx"		// разрушаемые регистры (memory - память, cc - флаги)
  );
  cout << "Sum of elements = " << result << endl;
  
  int j;
  cout << "Enter column number (0.." << cols-1 << "): ";
  cin >> j;
  if (j < 0 || j > cols-1) {
    cout << "Illegal value." << endl;
    return;
  }
  asm volatile (
    "	mov	%[rows], %%ecx"		"\n"	// ecx = cols
    "	mov	%[M], %%edx"		"\n"	// edx = адрес массива
    "	mov	%[j], %%ebx"		"\n"	// ebx = кол-во элементов до текущего столбца (номер столбца)
    "	xor	%%eax, %%eax"		"\n"	// eax = сумма (пока 0)
    "0:"				"\n"
    "	add	(%%edx,%%ebx,4), %%eax"	"\n"	// eax += элемент столбца j из M
    "	add	%[cols], %%ebx"		"\n"	// переходим к следующей строке массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "	mov	%%eax, %[result]"	"\n"	// запись результата
    : [result]"=m"(result)			// выходные операнды
    : [M]"r"(&M), [rows]"m"(rows), [cols]"m"(cols), [j]"m"(j) // входные операнды
    : "%eax", "%ebx", "%ecx", "%edx"		// разрушаемые регистры (memory - память, cc - флаги)
  );
  cout << "Sum of elements = " << result << endl;
}

// Лабораторная работа 7.3.
void lab7_3()
{
  cout << "Lab 7.3." << endl;
  // Эта функция будет работать только на 32-битной платформе
  if (sizeof(void*) != 4) {
    cout << "This code can work in 32-bit platforms only!" << endl;
    return;
  }

  int n;
  cout << "Enter natural number of elements: ";
  cin >> n;
  if (n < 1) {
    cout << "Illegal value." << endl;
    return;
  }

  double *beta = new double[n];
  for (int i = 0; i < n; ++i) {
    cout << "Enter beta[" << i << "]: ";
    cin >> beta[i];
  }
  double result;
  asm volatile (
    "	mov	%[n], %%ecx"		"\n"	// ecx = n
    "	mov	%[beta], %%eax"		"\n"	// edx = адрес массива
    "	fldz"				"\n"	// st(0) = сумма (пока 0)
    "0:"				"\n"
    "	faddl	(%%eax)"		"\n"	// st(0) += beta[i]
    "	add	$8, %%eax"		"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "	fstpl	%[result]"		"\n"	// запись результата
    : [result]"=m"(result)			// выходные операнды
    : [beta]"m"(beta), [n]"m"(n)		// входные операнды
    : "%eax", "%ecx"				// разрушаемые регистры (memory - память, cc - флаги)
  );
  cout << "Sum of elements = " << std::setprecision(8) << result << endl;
  delete[] beta;
}

// Лабораторная работа 7.4.
void lab7_4()
{
  cout << "Lab 7.4." << endl;
  // Эта функция будет работать только на 32-битной платформе
  if (sizeof(void*) != 4) {
    cout << "This code can work in 32-bit platforms only!" << endl;
    return;
  }

  struct Table {
    int key;
    double val;
  } table;
  cout << "struct Table {" << endl;
  cout << "  int key;" << endl;
  cout << "  double val;" << endl;
  cout << "} table;" << endl;
  cout << "Size of struct = " << sizeof(Table) << endl;
  cout << "Size of struct elements = " << sizeof(Table::key) + sizeof(Table::val) << endl;
  cout << "Offset of key field = " << (char*)&table.key - (char*)&table << endl;
  cout << "Offset of val field = " << (char*)&table.val - (char*)&table << endl;
  cout << "A structure whose size does not depend on alignment:" << endl;
  cout << "struct Table {" << endl;
  cout << "  int key;" << endl;
  cout << "  int padding_;  // for alignment" << endl;
  cout << "  double val;" << endl;
  cout << "} table;" << endl;
}

// Лабораторная работа 7.5.
void lab7_5()
{
  cout << "Lab 7.5." << endl;
  // Эта функция будет работать только на 32-битной платформе
  if (sizeof(void*) != 4) {
    cout << "This code can work in 32-bit platforms only!" << endl;
    return;
  }
  struct Table {
    int key;
    double val;
  };
  if (sizeof(Table) != 16) {
    cout << "This code can work only with alignment >= 8 bytes: #pragma pack(8)" << endl;
    return;
  }

  int n;
  cout << "Enter natural number of elements: ";
  cin >> n;
  if (n < 1) {
    cout << "Illegal value." << endl;
    return;
  }

  Table* tables = new Table[n];
  srand(time(0));
  for (int i = 0; i < n; ++i) {
    tables[i].key = rand() % 5;
    tables[i].val = (rand() - 16384.0) / 1024.0;
    cout << "tables[" << i << "] = { .key = " << tables[i].key << ", .val = " << std::setprecision(16) << tables[i].val << " }" << endl;
  }
  int k;
  cout << "Enter key for sum: ";
  cin >> k;
  double result;
  asm volatile (
    "	mov	%[n], %%ecx"		"\n"	// ecx = n
    "	mov	%[tables], %%eax"	"\n"	// eax = адрес массива
    "	mov	%[k], %%edx"		"\n"	// edx = k
    "	fldz"				"\n"	// st(0) = сумма (пока 0)
    "0:"				"\n"
    "	cmp	%%edx, (%%eax)"		"\n"	// проверяем ключ
    "	jnz	1f"			"\n"	// пропускаем, если не совпадает
    "	faddl	8(%%eax)"		"\n"	// st(0) += table[i]
    "1:	add	$16, %%eax"		"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "	fstpl	%[result]"		"\n"	// запись результата
    : [result]"=m"(result)			// выходные операнды
    : [tables]"m"(tables), [n]"m"(n), [k]"m"(k)	// входные операнды
    : "%eax", "%ecx", "%edx"			// разрушаемые регистры (memory - память, cc - флаги)
  );
  cout << "Sum of elements with specified key = " << result << endl;
  delete[] tables;
}

// Лабораторная работа 7.6.
size_t snorm(void* M, size_t N, int E)
{
  asm volatile (
    "	mov	%[N], %%ecx"		"\n"	// ecx = n
    "	mov	%[M], %%eax"		"\n"	// eax = адрес массива
    "	mov	%[E], %%edx"		"\n"	// edx = k
    "	fldz"				"\n"	// st(0) = сумма (пока 0)
    "0:"				"\n"
    "	cmp	%%edx, (%%eax)"		"\n"	// проверяем ключ
    "	jnz	1f"			"\n"	// пропускаем, если не совпадает
    "	faddl	8(%%eax)"		"\n"	// st(0) += table[i]
    "1:	add	$16, %%eax"		"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    // st(0) = сумма

    "	mov	%[N], %%ecx"		"\n"	// ecx = n
    "	mov	%[M], %%eax"		"\n"	// eax = адрес массива
    "2:"				"\n"
    "	cmp	%%edx, (%%eax)"		"\n"	// проверяем ключ
    "	jnz	3f"			"\n"	// пропускаем, если не совпадает
    "	fldl	8(%%eax)"		"\n"	// st(0) = table[i] | st(1) = сумма
    "	fdiv	%%st(1), %%st(0)"	"\n"	// st(0) /= st(1) | st(1) = сумма
    "	fstpl	8(%%eax)"		"\n"	// записываем значение в массив | st(0) = сумма
    "3:	add	$16, %%eax"		"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	2b"			"\n"	// loop 0b
    "	fstp	%%st(0)"		"\n"	// удаляем st(0)
    :						// выходные операнды
    : [M]"m"(M), [N]"m"(N), [E]"m"(E)		// входные операнды
    : "%eax", "%ecx", "%edx"			// разрушаемые регистры (memory - память, cc - флаги)
  );
  return N;
}

void lab7_6()
{
  cout << "Lab 7.6." << endl;
  // Эта функция будет работать только на 32-битной платформе
  if (sizeof(void*) != 4) {
    cout << "This code can work in 32-bit platforms only!" << endl;
    return;
  }
  struct Table {
    int key;
    double val;
  };
  if (sizeof(Table) != 16) {
    cout << "This code can work only with alignment >= 8 bytes: #pragma pack(8)" << endl;
    return;
  }

  int n;
  cout << "Enter natural number of elements: ";
  cin >> n;
  if (n < 1) {
    cout << "Illegal value." << endl;
    return;
  }

  Table* tables = new Table[n];
  srand(time(0));
  for (int i = 0; i < n; ++i) {
    tables[i].key = rand() % 5;
    tables[i].val = (rand() - 16384.0) / 1024.0;
    cout << "tables[" << i << "] = { .key = " << tables[i].key << ", .val = " << std::setprecision(16) << tables[i].val << " }" << endl;
  }
  int k;
  cout << "Enter key: ";
  cin >> k;
  double result;
  asm volatile (
    "	mov	%[n], %%ecx"		"\n"	// ecx = n
    "	mov	%[tables], %%eax"	"\n"	// eax = адрес массива
    "	mov	%[k], %%edx"		"\n"	// edx = k
    "	fldz"				"\n"	// st(0) = сумма (пока 0)
    "0:"				"\n"
    "	cmp	%%edx, (%%eax)"		"\n"	// проверяем ключ
    "	jnz	1f"			"\n"	// пропускаем, если не совпадает
    "	faddl	8(%%eax)"		"\n"	// st(0) += table[i]
    "1:	add	$16, %%eax"		"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "	fstpl	%[result]"		"\n"	// запись результата
    : [result]"=m"(result)			// выходные операнды
    : [tables]"m"(tables), [n]"m"(n), [k]"m"(k)	// входные операнды
    : "%eax", "%ecx", "%edx"			// разрушаемые регистры (memory - память, cc - флаги)
  );
  cout << "Sum of elements with specified key = " << result << endl;

  cout << endl;
  cout << "Normalizing...";
  snorm(tables, n, k);
  cout << " done!" << endl;
  asm volatile (
    "	mov	%[n], %%ecx"		"\n"	// ecx = n
    "	mov	%[tables], %%eax"	"\n"	// eax = адрес массива
    "	mov	%[k], %%edx"		"\n"	// edx = k
    "	fldz"				"\n"	// st(0) = сумма (пока 0)
    "0:"				"\n"
    "	cmp	%%edx, (%%eax)"		"\n"	// проверяем ключ
    "	jnz	1f"			"\n"	// пропускаем, если не совпадает
    "	faddl	8(%%eax)"		"\n"	// st(0) += table[i]
    "1:	add	$16, %%eax"		"\n"	// переходим к следующему элементу массива
    "	dec	%%ecx"			"\n"
    "	jnz	0b"			"\n"	// loop 0b
    "	fstpl	%[result]"		"\n"	// запись результата
    : [result]"=m"(result)			// выходные операнды
    : [tables]"m"(tables), [n]"m"(n), [k]"m"(k)	// входные операнды
    : "%eax", "%ecx", "%edx"			// разрушаемые регистры (memory - память, cc - флаги)
  );
  for (int i = 0; i < n; ++i) {
    cout << "tables[" << i << "] = { .key = " << tables[i].key << ", .val = " << std::setprecision(16) << tables[i].val << " }" << endl;
  }
  cout << "Sum of elements with specified key = " << result << endl;
  delete[] tables;
}

int main()
{
  lab7_1();
  cout << endl;
  lab7_2();
  cout << endl;
  lab7_3();
  cout << endl;
  lab7_4();
  cout << endl;
  lab7_5();
  cout << endl;
  lab7_6();
}
