/*********************************************
Kod stanowi uzupe³nienie materia³ów do æwiczeñ
w ramach przedmiotu metody optymalizacji.
Kod udostêpniony na licencji CC BY-SA 3.0
Autor: dr in¿. £ukasz Sztangret
Katedra Informatyki Stosowanej i Modelowania
Akademia Górniczo-Hutnicza
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
	for (int i = 0; i < 100; i++) {
		
		double* Y = new double[3];
	    double epsilon = 1e-10, gamma = 1e-200, Nmax = 1000;
		Y[0] = 1; Y[1] = 1; Y[2] = 1;
		matrix ud2;

		int LBOUND = -100, HBOUND = 100;
		
		//int x0 = 0 + (std::rand() % (100 - 0 + 1));
		//double* interval = expansion(func_lab_12, x0, 1, 10, 1000);

		////cout << "EXPANSION:\nX0: " << x0 << endl << "Point[0] = " << interval[0] << endl << "Point[1] = " << interval[1] << endl;

		//cout << ";" << interval[0];
		//cout << ";" << interval[1];
		//cout << ";" << x0 << ";";

		solution solF = fib(func_lab_12, LBOUND, HBOUND, epsilon);

		cout << solF.x;
		cout << solF.y;

		/*cout << ";" << solF.x;
		cout << ";" << solF.y;*/
		cout << solF.f_calls;
		solF.clear_calls();
		cout << ";" << func_lab_12(solF.x, solF.ud, ud2);

		solution solL = lag(func_lab_12, LBOUND, HBOUND, epsilon, gamma, Nmax);

		/*cout << ";" << solL.x;
		cout << ";" << solL.y;*/
		cout << solL.x;
		cout << solL.y;

		cout << solL.f_calls;
		cout << ";" << func_lab_12(solL.x, solL.ud, ud2);

		cout << endl;
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
