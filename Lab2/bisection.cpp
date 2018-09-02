#include<bits/stdc++.h>
using namespace std;
typedef long long Long;

int n;
double a, b, acc;

Long fact(int n)
{

    Long res = 1;
    for(int i = 1; i<=n ; i++)
    {
        res *= i;
    }
    return res;

}

double powk(double a, int k)
{
    if(k==0)
        return 1.0;
    double res = a;
    for(int i=1; i<k; i++)
    {
        res *= a;
    }

    return res;
}

double f(double x)
{
    double sum = 0.0;

    for(int k=1; k<=5; k++)

    {
        double up = powk(-1, k) * powk(((x*x)/4.0), k);
        double down = up / (1.0 *fact(k));
        down /= ( 1.0 *fact(n+k) );
        sum += down;
    }
    return powk(x/2.0, n) *  sum;

}

double relativeError(double newxm, double oldxm)
{
    return fabs(((newxm - oldxm) / newxm) * 100);
}

void printfunc(int iteration, double upper, double lower, double newxm, double oldxm, double fxm)
{
    printf("%d    %lf    %lf    %lf    %lf    %lf\n", iteration, upper, lower, newxm, fxm, relativeError(newxm, oldxm));
}

void bisection(double a, double b)
{
    puts("");
    cout<<"Function values for the initial guesses: "<<endl;
    cout<<"For "<<a<<": "<<f(a)<<"       "<<"For "<<b<<": "<<f(b)<<endl;
    /*if (f(a) * f(b) >= 0)
    {
        printf("\nWrong assumption of a and b\n");
        return;
    }*/

    FILE *f1 = fopen("error1.csv", "w");
    double c = a;
    int i = 1;
    double oldxm = 0.0, newxm;
    while ((b-a) >= acc)
    {
        oldxm = c;
        c = (a+b)/2;
        newxm = c;

        printfunc(i, b, a, newxm, oldxm, f(newxm));
        fprintf(f1, "%d,%lf\n", i, relativeError(newxm, oldxm) * 100.0);

        if (f(c) == 0.0)
            break;

        else if (f(c) * f(a) < 0)
            b = c;
        else
            a = c;
        i++;
    }
    printf("The value of root is : %lf\n",c);
}

int main()
{
    n = 0;
    FILE *fp1 = fopen("g1.csv", "w");
    cout<<"Function values for n = 0, x = 0 to 10: "<<endl<<endl;

    for(double i = 0; i < 10; i += 0.1)
    {
        fprintf(fp1, "%lf,%lf\n", i, f(i));
        printf("%lf                   %lf\n", i, f(i));
    }

    n = 1;
    FILE *fp2 = fopen("g2.csv", "w");
    puts("");
    cout<<"Function values for n = 1, x = 0 to 10: "<<endl<<endl;

    for(double i = 0; i < 10; i += 0.1)
    {
        fprintf(fp2, "%lf,%lf\n", i, f(i));
        printf("%lf                   %lf\n", i, f(i));
    }

    n = 2;
    FILE *fp3 = fopen("g3.csv", "w");
    puts("");
    cout<<"Function values for n = 2, x = 0 to 10: "<<endl<<endl;

    for(double i = 0; i < 10; i += 0.1)
    {
        fprintf(fp3, "%lf,%lf\n", i, f(i));
        printf("%lf                   %lf\n", i, f(i));
    }
    puts("");
    cout<<"Enter the value of initial guesses & Accuracy: "<<endl;
    n = 0;
    cin>>a>>b>>acc;

    bisection(a, b);
}
