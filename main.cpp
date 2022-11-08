/*********************************************
Kod stanowi uzupe³nienie materia³ów do æwiczeñ
w ramach przedmiotu metody optymalizacji.
Kod udostêpniony na licencji CC BY-SA 3.0
Autor: dr in¿. £ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Górniczo-Hutnicza
*********************************************/

#include"opt_alg.h"

void lab1();
void lab2();
void lab3();
void lab4();
void lab5();
void lab6();

matrix func_lab_1(matrix x, matrix ud1, matrix ud2);

int main()
{
	try
	{
		for (int i = 0; i < 100; i++) {
			double* Y = new double[3];
			double epsilon = 1e-10, gamma = 1e-200, Nmax = 1000;
			Y[0] = 1; Y[1] = 1; Y[2] = 1;
			matrix ud2;
			int x0 = 0 + (std::rand() % (100 - 0 + 1));
			double* interval = expansion(func_lab_1, x0, 1, 2, 1000, matrix(3, Y), ud2);
			cout << "," << interval[0];
			cout << "," << interval[1];
			cout << "," << x0;
			solution solF = fib(func_lab_1, interval[0], interval[1], epsilon);
			cout << "," << solF.x;
			cout << "," << solF.y;
			cout << "," << solF.f_calls;
			cout << "," << func_lab_1(solF.x, solF.ud, ud2);
			solution solL = lag(func_lab_1, interval[0], interval[1], epsilon, gamma, Nmax);
			cout << "," << solL.x;
			cout << "," << solL.y;
			cout << "," << solL.f_calls;
			cout << "," << func_lab_1(solL.x, solL.ud, ud2);
			cout << endl;
		}
	}
	catch (string EX_INFO)
	{
		cerr << "ERROR:\n";
		cerr << EX_INFO << endl << endl;
	}
	system("pause");
	return 0;
}

void lab1()
{

}

void lab2()
{

}

void lab3()
{

}

void lab4()
{

}

void lab5()
{

}

void lab6()
{

}

matrix func_lab_1(matrix x, matrix ud1, matrix ud2) {
	return -cos(0.1 * x()) * exp(-pow(0.1 * x() - 2 * 3.14, 2)) + 0.002 * pow(0.1 * x(), 2);
}