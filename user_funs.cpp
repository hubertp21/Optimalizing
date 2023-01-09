#include"user_funs.h"

matrix func_lab_12(matrix x, matrix ud1, matrix ud2) {
    return -cos(0.1 * x()) * exp(-pow(0.1 * x() - 2 * 3.14, 2)) + 0.002 * pow(0.1 * x(), 2);
}

matrix ff1R(matrix x, matrix ud1, matrix ud2)
{
    matrix y;
    matrix Y0 = matrix(3, new double[3]{ 5,1,10 });
    matrix *Y = solve_ode(df1, 0, 1, 1000, Y0, ud1, x);
    int n = get_len(Y[0]);
    double max = Y[1](0, 2);

    for (int i = 0; i < n; i++) {
        if (max < Y[1](i, 2)) {
            max = Y[1](i, 2);
        }
    }

    y = abs(max - 50);
    return y;
}

matrix df1(double t, matrix Y, matrix ud1, matrix ud2)
{
    double a = 0.98;
    double b = 0.63;
    double g = 9.81;
    double PA = 0.75;
    double TA = 90;
    double PB = 1;
    double DB = 0.00365665;
    double Fin = 0.01;
    double Tim = 10;

    matrix dY(3, 1);
    double FAout =  a * b * m2d(ud2) * sqrt(2 * g * Y(0) / PA);
    double FBout =  a * b * DB * sqrt(2 * g * Y(1) / PB);
    if (Y(0) < 0) FAout = 0;
    if (Y(1) < 0) FBout = 0;

    dY(0) = -FAout;
    dY(1) = FAout + Fin - FBout;
    dY(2) = (Fin / Y(1)) * (Tim - Y(2)) + (FAout / Y(1)) * (TA - Y(2));

    return dY;
}


matrix ff2T(matrix x, matrix ud1, matrix ud2) {
    return (pow(x(0), 2) + pow(x(1), 2) - cos(2.5 * 3.14 * x(0)) - cos(2.5 * 3.14 * x(1)) + 2);
}

matrix ff2R(matrix x, matrix ud1, matrix ud2)
{
    matrix y;
    matrix Y0(2, 1), Y_ref(2, new double[2]{ 3.14,0 });
    matrix* Y = solve_ode(df2, 0, 0.1, 100, Y0, Y_ref, x);
    int n = get_len(Y[0]);
    y = 0;
    for (int i = 0; i < n; ++i)
        y = y + 10 * pow(Y_ref(0) - Y[1](i, 0), 2) +
        pow(Y_ref(1) - Y[1](i, 1), 2) +
        pow(x(0) * (Y_ref(0) - Y[1](i, 0)) + x(1) * (Y_ref(1) - Y[1](i, 1)), 2);
    y = y * 0.1;
    return y;
}


matrix df2(double t, matrix Y, matrix ud1, matrix ud2)
{
    double mr = 1, mc = 5, l = 0.5, b = 0.5;
    double I = mr * l * l / 3 + mc * l * l;
    matrix dY(2, 1);
    dY(0) = Y(1);
    dY(1) = (ud2(0) * (ud1(0) - Y(0)) + ud2(1) * (ud1(1) - Y(1)) - b * Y(1)) / I;
    return dY;
}

matrix f4T(matrix x, matrix ud1, matrix ud2)
{
    matrix y;

    if (isnan(ud2(0, 0)))
        y = pow((x(0) + 2 * x(1) - 7), 2) + pow((2 * x(0) + x(1) - 5), 2);//funkcja celu

    else
        y = f4T(ud2(0) + x * ud2[1], ud1, ud2);

    return y;
}

matrix gf(matrix x, matrix ud1, matrix ud2) {
    matrix g(2, 1);

    g(0) = 10 * x(0) + 8 * x(1) - 34;
    g(1) = 8 * x(0) + 10 * x(1) - 38;

    return g;
}

matrix hf(matrix x, matrix ud1, matrix ud2) {
    matrix H(2, 2);

    H(0, 0) = 10;
    H(0, 1) = 8;
    H(1, 0) = 8;
    H(1, 1) = 10;

    return H;
}

matrix ff4R(matrix x, matrix ud1, matrix ud2)
{
    matrix y;
    int m = 100;
    int n = get_len(x);
    static matrix X(n, m), Y(1, m);
    static bool read = true;
    if (read)
    {
        ifstream S("XData.txt");
        S >> X;
        S.close();
        S.open("YData.txt");
        S >> Y;
        S.close();
        read = false;
    }
    double h;
    y = 0;
    for (int i = 0; i < m; ++i)
    {
        h = (trans(x) * X[i])();
        h = 1.0 / (1.0 + exp(-h));
        y = y - Y(0, i) * log(h) - (1 - Y(0, i)) * log(1 - h);
    }
    y = y / m;
    return y;
}

matrix gf4R(matrix x, matrix ud1, matrix ud2)
{
    int m = 100;
    int n = get_len(x);
    matrix g(n, 1);
    static matrix X(n, m), Y(1, m);
    static bool read = true;
    if (read)
    {
        ifstream S("XData.txt");
        S >> X;
        S.close();
        S.open("YData.txt");
        S >> Y;
        S.close();
        read = false;
    }
    double h;
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < m; ++i)
        {
            h = (trans(x) * X[i])();
            h = 1 / (1 + exp(-h));
            g(j) = g(j) + X(j, i) * (h - Y(0, i));
        }
        g(j) = g(j) / m;
    }
    return g;
}

matrix f5T(matrix x, matrix ud1, matrix ud2) {
    if (isnam(ud2(0, 0)) {
        y = matrix(2, 1);
        y(0) = ud1(1) * pow(x(0) - 2, 2) + pow(x(1) - 2, 2);
        y(1) = (1 / (ud1(1))) * pow(x(0) + 2, 2) + pow(x(1) + 2, 2);
    }
    else {
        matrix yt;
        yt = f5T(ud2[0] + x * ud2[1], ud1);
        y = ud1(0) * yt(0) + (1 - ud1(0)) * yt(1);
    }
    return y;
}

matrix fR5(matrix x, matrix ud1, matrix ud2) {
    matrix y;
    if (isnam(ud2(0, 0)) {
        y = matrix(3,1);
        double ro = 7800, P=1e3, E=207e9;
        y(0) = ro * x(0) * 3.14 * pow(x(1),2)/4;
        y(1) = 64 * P * pow(x(0),3)/(3*E*3.14*pow(ro,4));
        y(2) = (32 * P * x(0)) / (3.14 * pow(ro, 3));
    }
    else 
    {
        matrix yt, xt = ud2[0] + x * ud2[1];
            yt = fR5(xt, ud1);
            y = ud1 * (yt(0) - 0.06) / (1.53 - 0.06) + (1 - ud1) * (yt(1) - 5.25e-6) / (0.0032 - 5.25e-6);
        double c = 1e10;
        if (xt(0) < 0.2) {
            y = y + c * pow(0.2 - xt(0), 2);
        }
        if (xt(0) > 1) {
            y = y + c * pow( xt(0)-1, 2);
        }
        if (xt(1) < 0.01) {
            y = y + c * pow(0.01-xt(1),2);
        }
        if (xt(1) >0.05) {
            y = y + c * pow(xt(1)-0.05,2);
        }
        if (yt(1) > 0.005) {
            y = y + c * pow(yt(1)-0.005, 2);
        }
        if (yt(2) > 300e6) {
            y = y + c * pow(yt(2)-300e6, 2);
        }
    }
}