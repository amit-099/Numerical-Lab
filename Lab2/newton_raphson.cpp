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
    //return (x-4)*(x-4)*(x+2);
    return x*x*exp(-x) - 0.5;
}

double f_prime(double x)
{
    return 2*x*exp(-x) - x*x*exp(-x);
}

double rootRaphson(double x_val, double f_xval)
{
    double x = f_xval/f_prime(x_val);
    return x_val-x;
}

double relativeError(double newxm, double oldxm)
{
    return fabs(((newxm - oldxm) / newxm));
}

void printfunc(int iteration, double x_val, double f_xval, double f_prime_xval, double newroot, double oldroot)
{
    printf("%d    %.8lf    %.8lf    %.8lf    %.8lf    %.8lf\n", iteration, x_val, f_xval, f_prime_xval, newroot, relativeError(newroot, oldroot));
}

void newtonRaphson(double x_val)
{
    int i = 1;
    double error, oldroot, newroot = x_val;
    while(1)
    {
        double f_xval = f(x_val);
        double f_prime_xval = f_prime(x_val);
        oldroot = x_val;
        newroot = rootRaphson(x_val, f_xval);

        printfunc(i, x_val, f_xval, f_prime_xval, newroot, oldroot);

        error = relativeError(newroot, oldroot);
        if(error <= acc) break;


        if (f(newroot) == 0.0) break;

        x_val = newroot;
        i++;
    }
}

int main()
{
    double x_val;
    cin>>x_val>>acc;
    newtonRaphson(x_val);
    return 0;
}
