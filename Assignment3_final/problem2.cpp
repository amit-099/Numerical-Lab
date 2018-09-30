#include<bits/stdc++.h>
using namespace std;

const int MAXNumber = 50;
int N;
map<pair<string,int>, double> variableToCoefficient;
map<string, int> variableToIndex;
map<int, string> indexToVariable;
double coefficientArray[MAXNumber][MAXNumber];
double p[MAXNumber];
double b[MAXNumber][MAXNumber];
double mult[MAXNumber][MAXNumber];

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
        for(int j=0; j < coeff.size(); j++)
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

    variableToCoefficient[make_pair(var_name, equation_no)] = coeff_val;

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

void inverseOfTheMatrix(double a[MAXNumber][MAXNumber], int x, int y)
{
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            if(i==j)
            {
                b[i][j]=1;
            }
            else
            {
                b[i][j]=0;
            }
        }
    }
    for(int i=0; i<x; i++)
    {
        p[i]=a[i][i];
        for(int j=0; j<y; j++)
        {
            b[i][j]=b[i][j]/p[i];
            a[i][j]=a[i][j]/p[i];
        }
        for(int j=0; j<x; j++)
        {
            for(int k=0; k<y; k++)
            {
                if(j!=i)
                {
                    p[j]=a[j][i];
                    b[j][k]-=b[i][k]*p[j];
                }
            }
        }
        for(int j=0; j<x; j++)
        {
            for(int k=0; k<y; k++)
            {
                if(j!=i)
                {
                    a[j][k] -= a[i][k]*p[j];
                }
            }
        }
    }
    cout<<"\nInverse of the matrix: \n";
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            printf("%10.5lf ", b[i][j]);
        }
        cout<<"\n";
    }
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

void generateOutput(double ans[][50])
{
    cout<<"\nSolution for the system:"<<endl;
    for(int i=0; i<N; i++)
    {
        cout<<indexToVariable[i]<<" = "<<mult[i][0]<<endl;
    }
}

void multiplication(double bb[MAXNumber])
{
    int r1, r2, c1, c2;
    r1 = r2 = c1 = N;
    c2 = 1;
    for(int i = 0; i < r1; ++i)
        for(int j = 0; j < c2; ++j)
        {
            mult[i][j]=0;
        }

    for(int i = 0; i < r1; ++i)
        for(int j = 0; j < c2; ++j)
            for(int k = 0; k < c1; ++k)
            {
                mult[i][j] += b[i][k] * bb[k];
            }
}

int main()
{
    freopen("input2.txt","r", stdin);
    freopen("output2.txt","w", stdout);
    cout<<"Input Equations:"<<endl;
    startParsing();
    cout<<"\nGenerated matrix after parsing from file:"<<endl;
    displayMatrix(coefficientArray,N, N);

    double afterEqualConstants[MAXNumber];
    inverseOfTheMatrix(coefficientArray, N, N);
    for(int i=0; i<N; i++)
    {
        afterEqualConstants[i] = coefficientArray[i][N];
    }

    multiplication(afterEqualConstants);
    generateOutput(mult);
    return 0;
}
