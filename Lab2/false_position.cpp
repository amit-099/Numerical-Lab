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
    if(iteration == 1) printf("%d    %lf    %lf    %lf    %lf    %s\n", iteration, upper, lower, newxm, fxm, "N/A");
    else printf("%d    %lf    %lf    %lf    %lf    %lf\n", iteration, upper, lower, newxm, fxm, relativeError(newxm, oldxm));
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

        if(i > 1)
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
    printf("\nIter  Upper        Lower         Xm         f(Xm)       Error\n");

    double c = a;
    int i = 1;
    double oldxm = 0.0, newxm;
    FILE *f = fopen("error2.csv", "w");
    puts("");

    while (1)
    {
        oldxm = c;
        c = (a*func(b) - b*func(a))/ (func(b) - func(a));
        newxm = c;
        printfunc(i, a, b, newxm, oldxm, func(newxm));

        if(i > 1)
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
    printf("\nThe value of root is (False Position) : %lf\n",c);
}

int main()
{
    FILE *fp = fopen("gprb2.csv", "w");
    cout<<"Function values for x = 0 to 20: "<<endl<<endl;
    for(int i=0; i<=20; i++)
    {
        fprintf(fp, "%d,%lf\n", i, func(i));
        cout<<i<<"                    "<<fixed<<setprecision(10)<<func(i)<<endl;
    }
    double upper, lower;
    printf("\n\n");
    cout<<"Enter the value of Upper, Lower & Accuracy: "<<endl;
    cin>>upper>>lower>>acc;

    if(lower > upper) swap(upper, lower);
    regulaFalsi(upper, lower);
    bisection(lower, upper);
    return 0;
}
