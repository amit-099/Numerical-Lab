#include<bits/stdc++.h>
using namespace std;

double acc;

double func(double x)
{
    double res;
    res = ((4+x)/(((42-2*x)*(42-2*x))*(28-x))) - 0.016;
    return res;
}

double relativeError(double newxm, double oldxm)
{
    return fabs(((newxm - oldxm) / newxm));
}

void printfunc(int iteration, double upper, double lower, double newxm, double oldxm, double fxm)
{
    if(iteration == 1) printf("%d    %.5lf    %.5lf    %.5lf    %.5lf    %s\n", iteration, upper, lower, newxm, fxm, "N/A");
    else printf("%d    %.5lf    %.5lf    %.5lf    %.5lf    %.5lf\n", iteration, upper, lower, newxm, fxm, relativeError(newxm, oldxm));
}

void bisection(double a, double b)
{
    if (func(a) * func(b) >= 0)
    {
        printf("Wrong assumption of a and b\n");
        return;
    }

    FILE *f1 = fopen("error1.csv", "w");
    double c = a;
    int i = 1;
    double oldxm = 0.0, newxm;
    while (1)
    {
        oldxm = c;
        c = (a+b)/2;
        newxm = c;

        fprintf(f1, "%d,%lf\n", i, relativeError(newxm, oldxm) * 100.0);

        if(relativeError(newxm, oldxm) <= acc) break;

        if (func(c) == 0.0)
            break;

        else if (func(c) * func(a) < 0)
            b = c;
        else
            a = c;
        i++;
    }
    printf("The value of root is (Bisection) : %lf\n",c);
}

void regulaFalsi(double a, double b)
{
    if (func(a) * func(b) >= 0)
    {
        printf("Wrong assumption of a and b\n");
        return;
    }

    double c = a;
    int i = 1;
    double oldxm = 0.0, newxm;
    FILE *f = fopen("error2.csv", "w");

    while (1)
    {
        oldxm = c;
        c = (a*func(b) - b*func(a))/ (func(b) - func(a));
        newxm = c;
        printfunc(i, a, b, newxm, oldxm, func(newxm));

        fprintf(f, "%d,%lf\n", i, relativeError(newxm, oldxm) * 100.0);

        if(relativeError(newxm, oldxm) <= acc) break;

        if (func(c)==0)
            break;

        else if (func(c)*func(a) < 0)
            b = c;
        else
            a = c;

        i++;
    }
    printf("The value of root is (False Position) : %lf\n",c);
}

int main()
{
    FILE *fp = fopen("gprb2.csv", "w");
    for(int i=0; i<=20; i++)
    {
        fprintf(fp, "%d,%lf\n", i, func(i));
        cout<<fixed<<setprecision(10)<<func(i)<<endl;
    }
    double upper, lower;
    cin>>upper>>lower>>acc;

    if(lower > upper) swap(upper, lower);
    regulaFalsi(upper, lower);
    bisection(lower, upper);


    return 0;
}
