/*********************************************
Kod stanowi uzupe�nienie materia��w do �wicze�
w ramach przedmiotu metody optymalizacji.
Kod udost�pniony na licencji CC BY-SA 3.0
Autor: dr in�. �ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia G�rniczo-Hutnicza
*********************************************/

#include"opt_alg.h"

using namespace std;

void lab1();
void lab2();
void lab3();
void lab4();
void lab5();
void lab6();

int main()
{
	try
	{
		//freopen("out.txt", "w", stdout);
		lab1();
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
	int TIMES = 1;
	srand(time(NULL));
	for (int i = 0; i < TIMES; i++) {
		
		//double* Y = new double[3];
	    double epsilon = 1e-5, gamma = 1e-200, Nmax = 1000, alpha = 2;
		//Y[0] = 1; Y[1] = 1; Y[2] = 1;
		//matrix ud1;

		//int LBOUND = -100, HBOUND = 100;
		
		//int x0 = 0 + (std::rand() % (100 - 0 + 1));
		double* interval = expansion(ff1R, 0.0001, 0.01, 2, 1000);

		cout << "EXPANSION:\n" << endl << "Point[0] = " << interval[0] << endl << "Point[1] = " << interval[1] << endl;

		//cout << ";" << interval[0];
		//cout << ";" << interval[1];
		//cout << ";" << x0 << ";";

		//FIBONACCI

		//solution solF = fib(func_lab_12, LBOUND, HBOUND, epsilon);
		solution solF = fib(ff1R, interval[0], interval[1], epsilon);

		//cout << solF.x;
		//cout << solF.y;

		///*cout << ";" << solF.x;
		//cout << ";" << solF.y;*/
		//cout << solF.f_calls;
		//solF.clear_calls();
		//cout << ";" << func_lab_12(solF.x, solF.ud, ud2) << endl;

		//LAGRANGE

		solution solL = lag(ff1R, interval[0], interval[1], epsilon, gamma, Nmax);

		/*cout << ";" << solL.x;
		cout << ";" << solL.y;*/
		cout << solL.x;
		cout << solL.y;

		//cout << solL.f_calls << endl;
		//cout << ";" << func_lab_12(solL.x, solL.ud, ud2);

		//cout << endl;
	}


	//TESTY

	/*cout << "\nFIBBONACI\n\n";
	solution solF = fib(func_lab_12, 53, 81, epsilon);
	cout << solF.x << solF.y << solF.f_calls << endl;*/
	

	/*solution solL = lag(func_lab_12, 53, 81, 0.001, 1e-7, 1000);
	cout << "," << solL.x;
	cout << "," << solL.y;
	cout << "," << solL.f_calls;*/

	/*double* interval = expansion(func_lab_12, 10, 1.0, 1.5, 1000);
	cout << interval[0] << "   ;   " << interval[1] << endl;*/
	
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
