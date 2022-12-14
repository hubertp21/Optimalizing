#include"opt_alg.h"
#include <cmath>

double* expansion(matrix(*ff)(matrix, matrix, matrix), double x0, double d, double alpha, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		double* p = new double[2]{ 0,0 };
		int i = 0;
		solution X0(x0), X1(x0 + d);
		X0.fit_fun(ff, ud1, ud2);
		X1.fit_fun(ff, ud1, ud2);
		if (X0.y == X1.y)
		{
			p[0] = m2d(X0.x);
			p[1] = m2d(X1.x);
			return p;
		}
		if (X0.y < X1.y)
		{
			d *= -1;
			X1.x = X0.x + d;
			X1.fit_fun(ff, ud1, ud2);
			if (X1.y >= X0.y)
			{
				p[0] = m2d(X1.x);
				p[1] = m2d(X0.x) - d;
				return p;
			}
		}
		solution X2;
		int last_f_call = solution::f_calls;
		while (true)
		{
			++i;
			X2.x = x0 + pow(alpha, i) * d;
			X2.fit_fun(ff, ud1, ud2);
			if (X2.y >= X1.y || solution::f_calls > Nmax)
				break;
			X0 = X1;
			X1 = X2;
		}
		cout << solution::f_calls - last_f_call;
		d > 0 ? p[0] = m2d(X0.x), p[1] = m2d(X2.x) : (p[0] = m2d(X2.x), p[1] = m2d(X0.x));
		return p;
	}



	catch (string ex_info)
	{
		throw ("double* expansion(...):\n" + ex_info);
	}
}

solution fib(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, matrix ud1, matrix ud2)
{
	/*try
	{
		solution Xopt;
		int last_f_call = solution::f_calls;
		Xopt.ud = b - a;
		int n = static_cast<int>(ceil(log2(sqrt(5) * (b - a) / epsilon) / log2((1 + sqrt(5)) / 2)));
		int* F = new int[n] {1, 1};
		for (int i = 2; i < n; ++i)
			F[i] = F[i - 2] + F[i - 1];
		solution A(a), B(b), C, D;
		C.x = B.x - 1.0 * F[n - 2] / F[n - 1] * (B.x - A.x);
		D.x = A.x + B.x - C.x;
		C.fit_fun(ff, ud1, ud2);
		D.fit_fun(ff, ud1, ud2);
		for (int i = 0; i <= n - 3; ++i)
		{
			if (C.y < D.y)
				B = D;
			else
				A = C;
			C.x = B.x - 1.0 * F[n - i - 2] / F[n - i - 1] * (B.x - A.x);
			D.x = A.x + B.x - C.x;
			C.fit_fun(ff, ud1, ud2);
			D.fit_fun(ff, ud1, ud2);

			Xopt.ud.add_row((B.x - A.x)());
		}
		Xopt = C;
		Xopt.flag = 0;
		solution::f_calls -= last_f_call;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution fib(...):\n" + ex_info);
	}*/

	try
	{
		solution Xopt;
		Xopt.ud = b - a;
		int n = static_cast<int>(ceil(log2(sqrt(5) * (b - a) / epsilon) / log2((1 + sqrt(5)) / 2)));
		long long* F = new long long[n] {1, 1};
		for (int i = 2; i < n; ++i)
			F[i] = F[i - 2] + F[i - 1];
		solution A(a), B(b), C, D;
		C.x = B.x - 1.0 * F[n - 2] / F[n - 1] * (B.x - A.x);
		D.x = A.x + B.x - C.x;
		C.fit_fun(ff, ud1, ud2);
		D.fit_fun(ff, ud1, ud2);
		for (int i = 0; i <= n - 3; ++i)
		{
			/*if (A.x < B.x) {
				cout << A.x << B.x << "\n";
			}
			else {
				cout << B.x << A.x << "\n";
			}*/

			if (C.y < D.y)
				B = D;
			else
				A = C;

			C.x = B.x - 1.0 * F[n - i - 2] / F[n - i - 1] * (B.x - A.x);
			D.x = A.x + B.x - C.x;
			C.fit_fun(ff, ud1, ud2);
			D.fit_fun(ff, ud1, ud2);

			Xopt.ud.add_row((B.x - A.x)());
		}
		Xopt = C;
		Xopt.flag = 0;
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution fib(...):\n" + ex_info);
	}

}

solution lag(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, double gamma, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		int last_f_call = solution::f_calls;
		int ct = 0;
		Xopt.ud = b - a;
		solution A(a), B(b), C, D, D_old(a);
		/*if (A.x < B.x) {
			cout << A.x << B.x << " counter: " << ct << "\n";
		}
		else {
			cout << B.x << A.x << " counter: " << ct << "\n";
		}*/
		C.x = (a + b) / 2;
		A.fit_fun(ff, ud1, ud2);
		B.fit_fun(ff, ud1, ud2);
		C.fit_fun(ff, ud1, ud2);
		long double l, m;
		while (true) {
			ct++;
			l = m2d(A.y * (pow(B.x) - pow(C.x)) + B.y * (pow(C.x) - pow(A.x)) + C.y * (pow(A.x) - pow(B.x)));
			m = m2d(A.y * (B.x - C.x) + B.y * (C.x - A.x) + C.y * (A.x - B.x));
			if (m <= 0) {
				Xopt = D_old;
				Xopt.flag = 2;
				solution::f_calls -= last_f_call;
				return Xopt;
			}
			D.x = 0.5 * l / m;

			

			D.fit_fun(ff, ud1, ud2);
			if (A.x <= D.x && D.x <= C.x) {
				if (D.y < C.y) {
					A.x = A.x;
					B.x = C.x;
					C.x = D.x;
				}
				else {
					A.x = D.x;
					C.x = C.x;
					B.x = B.x;
				}

			}
			else if (C.x <= D.x && D.x <= B.x) {
				if (D.y < C.y) {
					A.x = C.x;
					C.x = D.x;
					B.x = B.x;
				}
				else {
					A.x = A.x;
					C.x = C.x;
					B.x = D.x;
				}
			}
			else {
				Xopt = D_old;
				Xopt.flag = 2;
				solution::f_calls -= last_f_call;
				return Xopt;
			}
			A.fit_fun(ff, ud1, ud2);
			B.fit_fun(ff, ud1, ud2);
			C.fit_fun(ff, ud1, ud2);

			/*if (A.x < B.x) {
				cout << A.x << B.x << " counter: " << ct << "\n";
			}
			else {
				cout << B.x << A.x << " counter: " << ct << "\n";
			}*/

			Xopt.ud.add_row((B.x - A.x)());
			//cout << "LEN B-A: " << B.x - A.x << endl;

			if (B.x - A.x < epsilon || abs(D.x() - D_old.x()) < gamma) {
				Xopt = D;
				Xopt.flag = 0;
				break;
			}
			if (solution::f_calls > Nmax) {
				Xopt = D;
				Xopt.flag = 1;
				break;
			}
			D_old = D;
		}
	
		return Xopt;
	}
	catch (string ex_info) {
		throw ("solution lag(...):\n" + ex_info);
	}
}
//test dziala
solution HJ(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution XB, XB_old, X;
		XB.x = x0;
		XB.fit_fun(ff, ud1, ud2);
		while (true)
		{

			X = HJ_trial(ff, XB, s, ud1, ud2);
			//cout << X.x(0) << " " << X.x(1) << endl;
			if (X.y < XB.y)
			{
				while (true)
				{
					XB_old = XB;
					XB = X;
					X.x = XB.x + XB.x - XB_old.x;

					X.fit_fun(ff, ud1, ud2);
					X = HJ_trial(ff, X, s, ud1, ud2);
					if (X.y >= XB.y)
						break;
					if (XB.f_calls > Nmax)
						return XB;
				}
			}
			else
				s *= alpha;
			if (XB.f_calls > Nmax || s < epsilon)
				return XB;
		}

	}
	catch (string ex_info)
	{
		throw ("solution HJ(...):\n" + ex_info);
	}
}

solution HJ_trial(matrix(*ff)(matrix, matrix, matrix), solution XB, double s, matrix ud1, matrix ud2)
{
	try
	{
		//Tu wpisz kod funkcji
		int n = get_dim(XB);
		solution X;
		matrix d = ident_mat(n);
		for (int i = 0; i < n; i++) {
			X.x = XB.x + s * d[i];
			X.fit_fun(ff,ud1,ud2);
			if (X.y < XB.y) {
				XB = X;
			}
			else {
				X.x = XB.x - s* d[i];
				X.fit_fun(ff, ud1, ud2);
				if (X.y < XB.y) {
					XB = X;
				}
				
			}
			
		}
		return XB;
	}
	catch (string ex_info)
	{
		throw ("solution HJ_trial(...):\n" + ex_info);
	}
}

solution Rosen(matrix(*ff)(matrix, matrix, matrix), matrix x0, matrix s0, double alpha, double beta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution X(x0), Xt;
		int n = get_dim(X);
		matrix l(n, 1),
			p(n, 1),
			s(s0),
			D = ident_mat(n);
		X.fit_fun(ff, ud1, ud2);
		while (true)
		{
			for (int i = 0; i < n; ++i)
			{
				Xt.x = X.x + s(i) * D[i];
				Xt.fit_fun(ff, ud1, ud2);
				if (Xt.y < X.y)
				{
					X = Xt;
					l(i) += s(i);
					s(i) *= alpha;
				}
				else
				{
					++p(i);
					s(i) *= -beta;
				}
			}
			bool change = true;
			for (int i = 0; i < n; ++i)
				if (p(i) == 0 || l(i) == 0)
				{
					change = false;
					break;
				}
			if (change)
			{
				matrix Q(n, n), v(n, 1);
				for (int i = 0; i < n; ++i)
					for (int j = 0; j <= i; ++j)
						Q(i, j) = l(i);
				Q = D * Q;
				v = Q[0] / norm(Q[0]);
				D.set_col(v, 0);
				for (int i = 1; i < n; ++i)
				{
					matrix temp(n, 1);
					for (int j = 0; j < i; ++j)
						temp = temp + trans(Q[i]) * D[j] * D[j];
					v = (Q[i] - temp) / norm(Q[i] - temp);
					D.set_col(v, i);
				}
				s = s0;
				l = matrix(n, 1);
				p = matrix(n, 1);
			}
			double max_s = abs(s(0));
			for (int i = 1; i < n; ++i)
				if (max_s < abs(s(i)))
					max_s = abs(s(i));
			if (max_s<epsilon || solution::f_calls>Nmax)
				return X;
		}
	}
	catch (string ex_info)
	{
		throw ("solution Rosen(...):\n" + ex_info);
	}
}

solution pen(matrix(*ff)(matrix, matrix, matrix), matrix x0, double c, double dc, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try {
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution pen(...):\n" + ex_info);
	}
}

solution sym_NM(matrix(*ff)(matrix, matrix, matrix), matrix x0, double s, double alpha, double beta, double gamma, double delta, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution sym_NM(...):\n" + ex_info);
	}
}

solution SD(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		int n = get_len(x0);
		solution X0, X1;
		X0.x = x0;
		matrix d(n, 1), p(n, 2);
		solution h;
		double* ab;

		while (true) {
			d = -X0.grad(gf, ud1, ud2);
			if (h0 < 0) {
				p.set_col(X0.x, 0);
				p.set_col(d, 1);
				ab = expansion(ff, 0, 1, 1.2, Nmax, ud1, p);
				h = golden(ff, ab[0], ab[1], epsilon, Nmax, ud1, p);
				X1.x = X0.x + h.x * d;
			}

			X1.x = X0.x + h0 * d;
			if (norm(X0.x - X1.x) < epsilon) {
				Xopt = X1;
				break;
			}

			if (solution::f_calls > Nmax || solution::g_calls > Nmax)
				break;

			X0 = X1;
		}

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution SD(...):\n" + ex_info);
	}
}

solution CG(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		Xopt.ud = trans(x0);
		int n = get_len(x0);
		solution X0, X1;
		X0.x = x0;
		matrix d(n, 1), P(n, 2);
		solution h;
		double* ab{};
		double beta;
		d = -X0.grad(gf);
		while (true)
		{
			if (h0 < 0)
			{
				P.set_col(X0.x, 0);
				P.set_col(d, 1);
				ab = expansion(ff, 0, 1, 1.2, Nmax, ud1, P);
				h = golden(ff, ab[0], ab[1], epsilon, Nmax, ud1, P);
				X1.x = X0.x + h.x * d;
			}
			else
				X1.x = X0.x + h0 * d;

			Xopt.ud.add_row(trans(X1.x));

			if (norm(X1.x - X0.x) < epsilon)
			{
				Xopt = X1;
				Xopt.fit_fun(ff, ud1, ud2);
				Xopt.flag = 0;
				break;
			}
			if (std::max(solution::f_calls, solution::g_calls) > Nmax)
			{
				Xopt = X1;
				Xopt.fit_fun(ff, ud1, ud2);
				Xopt.flag = 1;
				break;
			}
			X1.grad(gf);
			beta = pow(norm(X1.g), 2) / pow(norm(X0.g), 2);
			d = -X1.g + beta * d;
			X0 = X1;
			//            std::cout << "X0.x = " << X0.x << std::endl;
		}
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution CG(...):\n" + ex_info);
	}
}

solution Newton(matrix(*ff)(matrix, matrix, matrix), matrix(*gf)(matrix, matrix, matrix),
	matrix(*Hf)(matrix, matrix, matrix), matrix x0, double h0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		ofstream Newton;
		Newton.open("Newton.txt");
		solution Xopt;
		Xopt.ud = trans(x0);
		int n = get_len(x0);
		solution X0, X1;
		X0.x = x0;
		matrix d(n, 1), P(n, 2);
		solution h;
		double* ab;
		while (true)
		{
			d = -inv(X0.hess(Hf, ud1, ud1)) * X0.grad(gf, ud1, ud2);
			if (h0 < 0)
			{
				P.set_col(X0.x, 0);
				P.set_col(d, 1);
				ab = expansion(ff, 0, 1, 1.2, Nmax, ud1, P);
				h = golden(ff, ab[0], ab[1], epsilon, Nmax, ud1, P);
				X1.x = X0.x + h.x * d;
			}
			else
				X1.x = X0.x + h0 * d;

			Xopt.ud.add_row(trans(X1.x));

			if (norm(X0.x - X1.x) < epsilon)
			{
				Xopt = X1;
				Xopt.fit_fun(ff, ud1, ud2);
				Xopt.flag = 0;
				break;
			}
			if (solution::f_calls > Nmax || solution::g_calls > Nmax)
			{
				Xopt = X1;
				Xopt.fit_fun(ff, ud1, ud2);
				Xopt.flag = 1;
				break;
			}
			X0 = X1;
			Newton << X1.x(0) << " " << X1.x(1) << endl;
		}
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Newton(...):\n" + ex_info);
	}
	}
	catch (string ex_info)
	{
		throw ("solution Newton(...):\n" + ex_info);
	}
}

solution golden(matrix(*ff)(matrix, matrix, matrix), double a, double b, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt, A, B, C, D;
		double alpha = (pow(5, 0.5) - 1) / 2;
		A.x = a;
		B.x = b;
		C.x = B.x - alpha * (B.x - A.x);
		D.x = A.x + alpha * (B.x - A.x);

		while (true) {
			if (C.fit_fun(ff, ud1, ud2) < D.fit_fun(ff, ud1, ud2)) {
				A.x = A.x;
				B.x = D.x;
				C.x = B.x - alpha * (B.x - A.x);
				D.x = C.x;
			}
			else {
				A.x = C.x;
				B.x = B.x;
				C.x = D.x;
				D.x = A.x + alpha * (B.x - A.x);
			}

			if ((B.x - A.x) < epsilon) {
				Xopt = (A.x + B.x) / 2;
				break;
			}

			if (solution::f_calls > Nmax) {
				break;
			}
		}
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution golden(...):\n" + ex_info);
	}
}

solution Powell(matrix(*ff)(matrix, matrix, matrix), matrix x0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		int n = get_len(x0);
		matrix D = ident_mat(n), A(n, 2);
		solution X, P, h;
		X.x = x0;
		double* ab;
		while (true)
		{
			P = X;
			for (int i = 0; i < n; ++i)
			{
				A.set_col(P.x, 0);
				A.set_col(D[i], 1);
				ab = expansion(ff, 0, 1, 1.2, Nmax, ud1, A);
				h = golden(ff, ab[0], ab[1], epsilon, Nmax, ud1, A);
				P.x = P.x + h.x * D[i];
			}
			if (norm(X.x - P.x) < epsilon)
			{
				Xopt = P;
				Xopt.fit_fun(ff, ud1, ud2);
				Xopt.flag = 0;
				break;
			}
			if (solution::f_calls > Nmax)
			{
				Xopt = P;
				Xopt.fit_fun(ff, ud1, ud2);
				Xopt.flag = 1;
				break;
			}
			for (int i = 0; i < n - 1; ++i)
				D.set_col(D[i + 1], i);
			D.set_col(P.x - X.x, n - 1);
			A.set_col(P.x, 0);
			A.set_col(D[n - 1], 1);
			ab = expansion(ff, 0, 1, 1.2, Nmax, ud1, A);
			h = golden(ff, ab[0], ab[1], epsilon, Nmax, ud1, A);
			X.x = P.x + h.x * D[n - 1];
		}
		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution Powell(...):\n" + ex_info);
	}
}

solution EA(matrix(*ff)(matrix, matrix, matrix), int N, matrix limits, int mi, int lambda, matrix sigma0, double epsilon, int Nmax, matrix ud1, matrix ud2)
{
	try
	{
		solution Xopt;
		//Tu wpisz kod funkcji

		return Xopt;
	}
	catch (string ex_info)
	{
		throw ("solution EA(...):\n" + ex_info);
	}
}
