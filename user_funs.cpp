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