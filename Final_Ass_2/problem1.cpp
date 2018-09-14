#include<bits/stdc++.h>
using namespace std;
typedef long long Long;
double a, b, acc;
const double eps = 1e-9;

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
    char l1[11]="Iter";
    char l2[11]="Upper";
    char l3[11]="Lower";
    char l4[11]="Xm";
    char l5[11]="f(Xm)";
    char l6[11]="Error";
    if(iteration == 1)
    {
        printf("--------------------------------Bisection Method-------------------------------------\n");
        printf("|%12s |%12s |%12s |%12s | %12s| %12s|\n",l1,l2,l3,l4,l5,l6);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf | %-12s|\n", iteration, upper, lower, newxm, fxm, "N/A");

    }
    else
    {
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf | %-12lf|\n", iteration, upper, lower, newxm, fxm, relativeError(newxm, oldxm));
        fprintf(f1, "%d,%lf\n", iteration, relativeError(newxm, oldxm) * 100);
        fprintf(f2, "%lf,%lf\n", newxm, relativeError(newxm, oldxm) * 100);
    }
}

void printfunc_false(FILE *f_false1, FILE *f_false2, int iteration, double upper, double lower, double newxm, double oldxm, double fxm)
{
    char l1[11]="Iter";
    char l2[11]="Upper";
    char l3[11]="Lower";
    char l4[11]="Xm";
    char l5[11]="f(Xm)";
    char l6[11]="Error(\%)";
    if(iteration == 1)
    {
        printf("--------------------------------False Position Method--------------------------------\n");
        printf("|%12s |%12s |%12s |%12s | %12s| %12s|\n",l1,l2,l3,l4,l5,l6);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf | %-12s|\n", iteration, upper, lower, newxm, fxm, "N/A");

    }
    else
    {
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf | %-12lf|\n", iteration, upper, lower, newxm, fxm, relativeError(newxm, oldxm));
        fprintf(f_false1, "%lf,%lf\n", newxm, relativeError(newxm, oldxm) * 100);
        fprintf(f_false2, "%d,%lf\n", iteration, relativeError(newxm, oldxm) * 100);
    }
}

void regulaFalsi(double a, double b)
{
    if (f(a) * f(b) >= 0)
    {
        printf("Wrong assumption of a and b (False Position)\n");
        return;
    }

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
    cout<<"Enter the value of initial guesses & Accuracy: "<<endl;
    cin>>a>>b>>acc;
    FILE *fp1 = fopen("g1_bisection.csv", "w");
    printf("\n   X                           f(X)\n\n");
    for(double i = a; i <= b+eps; i += 0.1)
    {
        fprintf(fp1, "%lf,%lf\n", i, f(i));
        printf("%lf                   %lf\n", i, f(i));
    }
    bisection(a, b);
    regulaFalsi(a, b);
    return 0;
}
