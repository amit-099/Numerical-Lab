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
    if(iteration == 1) printf("%d    %.8lf    %.8lf    %.8lf    %.8lf    %.8lf      %s\n", iteration, lower, upper, f_lower, f_upper, newroot, "N/A");
    else printf("%d    %.8lf    %.8lf    %.8lf    %.8lf    %.8lf    %.8lf\n", iteration, lower, upper, f_lower, f_upper, newroot, relativeError(newroot, oldroot));
}

void secant(double lower, double upper)
{
    int i = 1;
    double error, oldroot, newroot = lower;
    printf("\nIter   Lower         Upper        f(Lower)       f(Upper)      New_root       Error\n\n");
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
