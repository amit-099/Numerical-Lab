#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100;
double coefficientArray[MAXN][MAXN];
map<pair<string,int>, double> variableToCoef;
map<string, int> variableToIndex;
map<int, string> idx_to_var;
double constants[MAXN];
int N, eq;
double init_guesses[MAXN];
double sum[MAXN];

bool isCharacter(char c)
{
    if((c>='A' && c<='Z') || (c>='a' && c<='z')) return true;
    return false;
}

bool isOperator(char c)
{
    if(c=='+' || c=='-' || c=='=') return true;
    return false;
}

bool isMinus(char c)
{
    return c=='-'?true:false;
}

bool isEqual(char c)
{
    return c=='='?true:false;
}

void parsingVariable(string s, int equation_no)
{
    int i=0;
    string coeff = "";
    string var_name = "";
    char ch[10];

    bool is_neg = isMinus(s[0]);
    bool is_cons = isEqual(s[0]);
    if(is_cons)
    {
        is_neg = isMinus(s[1]);
        while(isCharacter(s[i])==false && i<s.size())
        {
            if(isOperator(s[i]))
            {
                i++;
                continue;
            }
            coeff += s[i];
            i++;
        }
        var_name = "cons";
    }
    else
    {
        while(isCharacter(s[i])==false && i<s.size())
        {
            if(isOperator(s[i]))
            {
                i++;
                continue;
            }
            coeff += s[i];
            i++;
        }

        while(i<s.size())
        {
            var_name += s[i];
            i++;
        }

    }
    if(coeff!="")
    {
        for(int j=0; j<coeff.size(); j++)
        {
            ch[j] = coeff[j];
        }
    }
    else
    {
        ch[0] = '1';
    }
    double coeff_val = atof(ch);
    if(is_neg) coeff_val *= -1;
    variableToCoef[make_pair(var_name,equation_no)] = coeff_val;
}

void parserMain(string s, int equation_no)
{

    string temp = "";
    for(int i=0; i<s.size(); i++)
    {
        if(isOperator(s[i]))
        {
            parsingVariable(temp,equation_no);
            temp = "";
            temp += s[i];
        }
        else if(s[i]==' ')
        {
            continue;
        }
        else
        {
            temp += s[i];
        }

    }
    if(temp!="")
    {
        string temp2 = "";
        if(temp[0]!='=')
            temp2 = '=' + temp;
        else temp2 = temp;
        parsingVariable(temp2,equation_no);
    }
}

void showEachStep(double temp[][MAXN], int row, int col, FILE * fp1)
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
            fprintf(fp1, "%0.3lf\t", temp[i][j]);
        fprintf(fp1, "\n");
    }
    fprintf(fp1, "\n");
}

void generateOutput(double ans[], FILE * fp1)
{
    fprintf(fp1, "\nSolution for the system:\n");
    for(int i=0; i<N; i++)
    {
        fprintf(fp1, "%s = %0.8lf\n", idx_to_var[i].c_str(), ans[i]);
    }
}

void coefficientMatrixForm()
{
    map<pair<string,int>,double>::iterator it;
    int var_no = 0;
    for (it=variableToCoef.begin(); it!=variableToCoef.end(); ++it)
    {
        if(it->first.first!="cons" && it->first.first!="")
        {
            if(variableToIndex.find(it->first.first)==variableToIndex.end())
            {
                variableToIndex[it->first.first] = var_no;
                idx_to_var[var_no] = it->first.first;
                var_no++;
            }
            coefficientArray[it->first.second][variableToIndex[it->first.first]] = it->second;
        }
    }
    N = var_no;
    for (it=variableToCoef.begin(); it!=variableToCoef.end(); ++it)
    {
        if(it->first.first=="cons")
        {
            if(variableToIndex.find(it->first.first)==variableToIndex.end())
            {
                variableToIndex[it->first.first] = var_no;
                idx_to_var[var_no] = it->first.first;
                var_no++;
            }
            coefficientArray[it->first.second][variableToIndex[it->first.first]] = it->second;
        }
    }
}

void parseFromFile(FILE * pFile, FILE * fp1)
{
    char s[1000];
    int equation_no = 0;
    if(pFile == NULL) perror("Error opening file");
    else
    {
        while(fgets(s, 1000, pFile))
        {
            fprintf(fp1, "%s", s);
            parserMain(s, equation_no);
            equation_no++;
        }
        fclose (pFile);
    }
    eq = equation_no;
    coefficientMatrixForm();
}

double relativeApproxError(double newval, double oldval)
{
    return fabs(((newval - oldval)/newval)*100);
}

void jacobiIteration(double temp[][MAXN], int row, int col, int iterations, FILE * fp1)
{
    double a = 0;
    int k,p;
    double pp[MAXN];

    for(int n = 0; n < iterations; n++)
    {
        for(int m = 0; m < row; m++)
            pp[m] = init_guesses[m];
        for(int i = 0; i < row; i++)
        {
            a = 0;
            for(int j = 0; j < col; j++)
            {
                if(j != i)
                {
                    a += temp[i][j] * pp[j];
                }
                else
                    k = temp[i][j];
            }
            init_guesses[i] = (constants[i] - a) / k;
        }
        fprintf(fp1, "\nIteration number %d:\n", n+1);
        generateOutput(init_guesses, fp1);
        fprintf(fp1, "\n");

        for(int i = 0; i < row; i++)
        {
            if(n!=0)
                fprintf(fp1, "Relative approximate error %d: %0.3lf%\n", i+1, relativeApproxError(init_guesses[i], pp[i]));
        }
    }
}

bool dominantCheck(double temp[][MAXN], int row, int col, FILE * fp1)
{
    int k = 0;
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(i != j) sum[i]+=temp[i][j];
        }
        fprintf(fp1, "Sum of row (%d) elements (without diagonal entry): %0.3lf\n", i+1, sum[i]);
    }
    fprintf(fp1, "\nDiagonal entries are:  ");
    for(int i = 0; i < row; i++)
        fprintf(fp1, "%0.3lf  ", temp[i][i]);
    fprintf(fp1, "\n");
    for(int j = 0; j < row; j++)
    {
        if(temp[k][k] < sum[j])
            return false;
        k++;
    }
    return true;
}

int main()
{
    FILE *fp1 = fopen("output1.txt", "w");
    FILE * pFile;
    pFile = fopen("input1.txt","r");
    fprintf(fp1, "Input Equations:\n");
    parseFromFile(pFile, fp1);
    fprintf(fp1, "\nGenerated matrix after parsing from file:\n");
    showEachStep(coefficientArray, eq, N, fp1);
    for(int i = 0; i<N; i++) constants[i] = coefficientArray[i][N];
    int iterations;

    if(eq == N)
    {
        bool isDom = dominantCheck(coefficientArray, eq, N, fp1);
        if(isDom)
        {
            fprintf(fp1, "\nThe given matrix is diagonally dominant.\n");
            cout<<"Enter "<<N<<" initial guesses:"<<endl;
            fprintf(fp1, "\nInitial guesses are:\n");
            for(int i = 0; i < N; i++)
            {
                cin>>init_guesses[i];
                fprintf(fp1, "%0.3lf ", init_guesses[i]);
            }
            fprintf(fp1, "\n");
            cout<<"\nEnter number of iterations"<<endl;
            fprintf(fp1, "\nNumber of iterations are:\n");
            cin>>iterations;
            fprintf(fp1, "%d\n", iterations);
            jacobiIteration(coefficientArray, eq, N, iterations, fp1);
            cout<<"\nSee output1.txt file for the result."<<endl;
        }
        else
        {
            fprintf(fp1, "\nThe matrix is not diagonally dominant, Jacobi iteration method will not converge to a solution.\n");
            cout<<"\nSee output1.txt file for the result."<<endl;
        }
    }
    else
    {
        fprintf(fp1, "\nThe matrix is not a square matrix, can not be solved using Jacobi Iteration.\n");
        cout<<"\nSee output1.txt file for the result."<<endl;
    }
    return 0;
}
