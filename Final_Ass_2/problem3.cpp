#include<bits/stdc++.h>
using namespace std;
double acc;

double f(double x)
{
    return 8*sin(x)*exp(-x)-1;
}

double rootSacant(double lower, double upper, double f_lower, double f_upper)
{
    double x = (f_upper*(upper-lower))/(f_upper-f_lower);
    return upper-x;
}

double relativeError(double newxm, double oldxm)
{
    return fabs(((newxm - oldxm) / newxm));
}

void printfunc(int iteration, double lower, double upper, double f_lower, double f_upper, double newroot, double oldroot)
{
    char l1[11]="Iter";
    char l2[11]="Lower";
    char l3[11]="Upper";
    char l4[11]="f(Lower)";
    char l5[11]="f(Upper)";
    char l6[11]="New_root";
    char l7[11]="Error";
    if(iteration == 1)
    {
        printf("-----------------------------------------Secant Method---------------------------------------------\n");
        printf("|%12s |%12s |%12s |%12s | %12s| %12s| %12s|\n",l1,l2,l3,l4,l5,l6,l7);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf |%-12lf | %-12s|\n", iteration, lower, upper, f_lower, f_upper, newroot, "N/A");

    }
    else
    {
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf |%-12lf | %-12lf|\n", iteration, lower, upper, f_lower, f_upper, newroot, relativeError(newroot, oldroot));
    }
}

void secant(double lower, double upper)
{
    int i = 1;
    double error, oldroot, newroot = lower;
    while(1)
    {
        double f_lower = f(lower);
        double f_upper = f(upper);
        oldroot = newroot;
        newroot = rootSacant(lower, upper, f_lower, f_upper);

        printfunc(i, lower, upper, f_lower, f_upper, newroot, oldroot);

        if(i!=1)
        {
            error = relativeError(newroot, oldroot);
            if(error <= acc) break;
        }

        if (f(newroot) == 0.0) break;

        lower = upper;
        upper = newroot;

        i++;
    }
    printf("\nThe value of root is (Secant) : %.8lf\n", newroot);
}

int main()
{
    double lower, upper, root;
    cout<<"Enter the value of initial guess & Accuracy: "<<endl;
    cin>>lower>>upper>>acc;
    if(lower>upper) swap(lower, upper);
    secant(lower, upper);
    puts("\n\nRunning Again...\n\n");
    main();
    return 0;
}
