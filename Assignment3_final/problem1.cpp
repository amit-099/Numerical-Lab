#include<bits/stdc++.h>
using namespace std;

const int MAXNumber = 50;
int N;
map<pair<string,int>, double> variableToCoefficient;
map<string, int> variableToIndex;
map<int, string> indexToVariable;
double coefficientArray[MAXNumber][MAXNumber];
double coefficientArray2[MAXNumber][MAXNumber];

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

void coEfficientMatrixForm()
{
    map<pair<string,int>,double>::iterator it;

    int var_no = 0;
    for (it=variableToCoefficient.begin(); it!=variableToCoefficient.end(); ++it)
    {
        if(it->first.first!="cons")
        {
            if(variableToIndex.find(it->first.first)==variableToIndex.end())
            {
                variableToIndex[it->first.first] = var_no;
                indexToVariable[var_no] = it->first.first;
                var_no++;
            }
            coefficientArray[it->first.second][variableToIndex[it->first.first]] = it->second;
        }
    }
    for (it=variableToCoefficient.begin(); it!=variableToCoefficient.end(); ++it)
    {
        if(it->first.first=="cons")
        {
            if(variableToIndex.find(it->first.first)==variableToIndex.end())
            {
                variableToIndex[it->first.first] = var_no;
                indexToVariable[var_no] = it->first.first;
                var_no++;
            }
            coefficientArray[it->first.second][variableToIndex[it->first.first]] = it->second;
        }
    }
}

void variableParseFromFile(string s, int equation_no)
{
    int i=0;
    string coeff = "";
    string var_name = "";
    char ch[10];

    bool is_neg = isMinus(s[0]);
    bool is_cons = ((s[0]=='=')?true:false);
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

    variableToCoefficient[make_pair(var_name,equation_no)] = coeff_val;

}

void parseFromFile(string s, int equation_no)
{

    string temp = "";
    for(int i=0; i<s.size(); i++)
    {
        if(isOperator(s[i]))
        {
            variableParseFromFile(temp,equation_no);
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
        variableParseFromFile(temp2,equation_no);
    }
}

void startParsing()
{
    string s;
    int equation_no = 0;
    while(getline(cin, s))
    {
        cout<<s<<endl;
        parseFromFile(s,equation_no);
        equation_no++;
    }
    N = equation_no;
    coEfficientMatrixForm();
}

void coFactorMatrix(double mat[][MAXNumber], double temp[][MAXNumber], int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double determinantMatrix(double mat[][MAXNumber], int n)
{
    double D = 0.0;
    if (n == 1)
        return mat[0][0];

    double temp[MAXNumber][MAXNumber];

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        coFactorMatrix(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinantMatrix(temp, n - 1);
        sign = -sign;
    }

    return D;
}

void displayMatrix(double mat[MAXNumber][MAXNumber], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%5.2lf ", mat[i][j]);
        cout<<endl;
    }
}

void generateOutput(double ans[])
{
    cout<<"\nSolution for the system:"<<endl;
    for(int i=0; i<N; i++)
    {
        cout<<indexToVariable[i]<<" = "<<ans[i]<<endl;
    }
}

int main()
{
    freopen("input1.txt","r", stdin);
    freopen("output1.txt","w", stdout);
    cout<<"Input Equations:"<<endl;
    startParsing();

    double afterEqualConstants[MAXNumber];
    double ans[MAXNumber];

    for(int i = 0; i < N; i++)
        for(int j =0; j < N; j++)
            coefficientArray2[i][j] = coefficientArray[i][j];

    cout<<"\nGenerated matrix after parsing from file:"<<endl;
    displayMatrix(coefficientArray, N, N);
    for(int i=0; i<N; i++)
    {
        afterEqualConstants[i] = coefficientArray[i][N];
    }

    int A = determinantMatrix(coefficientArray, N);

    if(A == 0) cout<<"Determinant of the matrix is zero, is not possible to get solution of this system by cremer's rule."<<endl;

    else
    {
        int k = 0;
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                coefficientArray2[j][k] = afterEqualConstants[j];
            }

            ans[i] = determinantMatrix(coefficientArray2, N) / A;

            for(int i = 0; i < N; i++)
                for(int j = 0; j < N; j++)
                    coefficientArray2[i][j] = coefficientArray[i][j];

            k++;
        }
        generateOutput(ans);
    }
    return 0;
}
