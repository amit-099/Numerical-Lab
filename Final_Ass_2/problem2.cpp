#include<bits/stdc++.h>
using namespace std;
double acc;

double f(double x, int f_choice)
{
    if(!f_choice) return -x*x+1.8*x+2.5;
    else return exp(-0.5*x)*(4-x)-2;
}

double f_prime(double x, int f_choice)
{
    if(!f_choice) return -2*x+1.8;
    else return -0.5*exp(-0.5*x)*(4-x)-exp(-0.5*x);
}

double rootRaphson(double x_val, double f_xval, int f_choice)
{
    double x = f_xval/f_prime(x_val, f_choice);
    return x_val-x;
}

double relativeError(double newxm, double oldxm)
{
    return fabs(((newxm - oldxm) / newxm));
}


void printfunc(int iteration, double x_val, double f_xval, double f_prime_xval, double newroot, double oldroot)
{
    char l1[11]="Iter";
    char l2[11]="X_val";
    char l3[11]="f(X_val)";
    char l4[11]="f'(X_val)";
    char l5[11]="New_root";
    char l6[11]="Error";
    if(iteration == 1)
    {
        printf("--------------------------------Newton Raphson Method--------------------------------\n");
        printf("|%12s |%12s |%12s |%12s | %12s| %12s|\n",l1,l2,l3,l4,l5,l6);
        printf("|-------------|-------------|-------------|-------------|-------------|-------------|\n");
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf | %-12s|\n", iteration, x_val, f_xval, f_prime_xval, newroot, "N/A");

    }
    else
    {
        printf("|%-12d |%-12lf |%-12lf |%-12lf |%-12lf | %-12lf|\n", iteration, x_val, f_xval, f_prime_xval, newroot, relativeError(newroot, oldroot));
    }
}

void newtonRaphson(double x_val, int f_choice)
{
    int i = 1;
    double error, oldroot, newroot = x_val;
    while(1)
    {
        double f_xval = f(x_val, f_choice);
        double f_prime_xval = f_prime(x_val, f_choice);
        oldroot = x_val;
        newroot = rootRaphson(x_val, f_xval, f_choice);

        printfunc(i, x_val, f_xval, f_prime_xval, newroot, oldroot);
        error = relativeError(newroot, oldroot);

        if(error <= acc) break;
        if(f(newroot, f_choice) == 0.0) break;

        x_val = newroot;
        i++;
    }
    printf("\nThe value of root is (Newton-Raphson) : %.8lf\n", newroot);
}

int main()
{
    double x_val;
    int f_choice;

    cout<<"Choose which part of the problem you want to solve: 0 for (a), 1 for (b)"<<endl;
    cin>>f_choice;

    if(!f_choice)
    {
        cout<<"Enter the value of initial guess & Accuracy: "<<endl;
        cin>>x_val>>acc;
        newtonRaphson(x_val, f_choice);
    }
    else
    {
        for(int i = 1; i <= 3; i++)
        {
            cout<<"Enter the value of initial guess "<<i<<" & Accuracy: "<<endl;
            cin>>x_val>>acc;
            newtonRaphson(x_val, f_choice);
        }
    }
    puts("\n\nRunning Again...\n\n");
    main();
    return 0;
}
