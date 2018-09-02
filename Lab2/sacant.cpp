#include<bits/stdc++.h>
using namespace std;

double acc;

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
    //return 2*powk(x,3)-7*powk(x,2)-14*x+5;
    return (x-4)*(x-4)*(x+2);
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
    if(iteration == 1) printf("%d    %.8lf    %.8lf    %.8lf    %.8lf    %.8lf    %s\n", iteration, lower, upper, f_lower, f_upper, newroot, "N/A");
    else printf("%d    %.8lf    %.8lf    %.8lf    %.8lf    %.8lf    %.8lf\n", iteration, lower, upper, f_lower, f_upper, newroot, relativeError(newroot, oldroot));
}

void sacant(double lower, double upper)
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
}

int main()
{
    double lower, upper, root;
    cin>>lower>>upper>>acc;
    sacant(lower, upper);
    return 0;
}

