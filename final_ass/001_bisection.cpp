#include<bits/stdc++.h>
using namespace std;
typedef long long Long;
double a, b, acc;

double f(double x)
{
    return ((9.8*x)/15.0) * (1-exp((-15.0/x) * 9.0)) - 35.0;
}

double relativeError(double newxm, double oldxm)
{
    return fabs(((newxm - oldxm) / newxm) * 100);
}

void printfunc(FILE *f1, FILE *f2, int iteration, double upper, double lower, double newxm, double oldxm, double fxm)
{
    if(iteration == 1) printf("%d    %lf    %lf    %lf    %lf       %s\n", iteration, upper, lower, newxm, fxm, "N/A");
    else
    {
        printf("%d    %lf    %lf    %lf    %lf    %lf\n", iteration, upper, lower, newxm, fxm, relativeError(newxm, oldxm));
        fprintf(f1, "%d,%lf\n", iteration, relativeError(newxm, oldxm) * 100.0);
        fprintf(f2, "%lf,%lf\n", newxm, relativeError(newxm, oldxm) * 100.0);
    }
}

void printfunc_false(FILE *f_false1, FILE *f_false2, int iteration, double upper, double lower, double newxm, double oldxm, double fxm)
{
    if(iteration == 1) printf("%d    %lf    %lf    %lf    %lf    %s\n", iteration, upper, lower, newxm, fxm, "N/A");
    else
    {
        printf("%d    %lf    %lf    %lf    %lf    %lf\n", iteration, upper, lower, newxm, fxm, relativeError(newxm, oldxm));
        fprintf(f_false1, "%lf,%lf\n", newxm, relativeError(newxm, oldxm) * 100.0);
        fprintf(f_false2, "%d,%lf\n", iteration, relativeError(newxm, oldxm) * 100.0);
    }
}

void regulaFalsi(double a, double b)
{
    if (f(a) * f(b) >= 0)
    {
        printf("Wrong assumption of a and b (False Position)\n");
        return;
    }
    printf("\nIter  Upper        Lower         Xm         f(Xm)       Error\n");

    double c = a;
    int i = 1;
    double oldxm = 0.0, newxm;
    FILE *f_false1 = fopen("g3_error3_false_XvsE.csv", "w");
    FILE *f_false2 = fopen("g4_error4_false_IvsE.csv", "w");
    puts("");

    while (1)
    {
        oldxm = c;
        c = (a*f(b) - b*f(a))/ (f(b) - f(a));
        newxm = c;
        printfunc_false(f_false1, f_false2, i, a, b, newxm, oldxm, f(newxm));

        if(relativeError(newxm, oldxm) <= acc) break;
        if (f(c)==0) break;
        else if (f(c)*f(a) < 0) b = c;
        else a = c;
        i++;
    }
    printf("\nThe value of root is (False Position) : %lf\n",c);
}

void bisection(double a, double b)
{
    puts("");
    cout<<"Function values for the initial guesses: "<<endl;
    cout<<"For "<<a<<": "<<f(a)<<"       "<<"For "<<b<<": "<<f(b)<<endl;
    puts("");
    if (f(a) * f(b) >= 0)
    {
        printf("\nWrong assumption of a and b (Bisection)\n");
        return;
    }
    printf("\nIter  Upper        Lower         Xm         f(Xm)       Error\n");
    puts("");

    FILE *f1 = fopen("g2_error1_bisection_IvsE.csv", "w");
    FILE *f2 = fopen("g3_error2_bisection_XvsE.csv", "w");
    double c = a;
    int i = 1;
    double oldxm = 0.0, newxm;
    while(1)
    {
        oldxm = c;
        c = (a+b)/2;
        newxm = c;
        printfunc(f1, f2, i, b, a, newxm, oldxm, f(newxm));

        if(relativeError(newxm, oldxm) <= acc) break;
        if (f(c) == 0.0) break;
        else if (f(c) * f(a) < 0) b = c;
        else a = c;
        i++;
    }
    printf("\nThe value of root is (Bisection) : %lf\n",c);
}

int main()
{
    FILE *fp1 = fopen("g1_bisection.csv", "w");
    cout<<"Enter the value of initial guesses & Accuracy: "<<endl;
    cin>>a>>b>>acc;
    printf("\n   X                           f(X)\n\n");
    for(double i = a; i <= b; i += 0.1)
    {
        fprintf(fp1, "%lf,%lf\n", i, f(i));
        printf("%lf                   %lf\n", i, f(i));
    }

    bisection(a, b);
    regulaFalsi(a, b);
    puts("\n\nRunning Again...\n\n");
    main();
    return 0;
}
