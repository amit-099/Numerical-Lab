#include<bits/stdc++.h>
using namespace std;
const int MAXN = 50;
int N;

double p[MAXN];
double b[MAXN][MAXN];
double mult[MAXN][MAXN];

map<pair<string,int>, double> var_to_coeff;
map<string, int> var_to_idx;
map<int, string> idx_to_var;
double coeff_arr[MAXN][MAXN];

bool is_char(char c)
{
    if((c>='A' && c<='Z') || (c>='a' && c<='z')) return true;
    return false;
}

bool is_operator(char c)
{
    if(c=='+' || c=='-' || c=='=') return true;
    return false;
}

bool is_minus(char c)
{
    return c=='-'?true:false;
}

void matrix_constructor()
{
    map<pair<string,int>,double>::iterator it;

    int var_no = 0;
    for (it=var_to_coeff.begin(); it!=var_to_coeff.end(); ++it)
    {
        if(it->first.first!="cons")
        {
            if(var_to_idx.find(it->first.first)==var_to_idx.end())
            {
                var_to_idx[it->first.first] = var_no;
                idx_to_var[var_no] = it->first.first;
                var_no++;
            }
            coeff_arr[it->first.second][var_to_idx[it->first.first]] = it->second;
        }
    }
    for (it=var_to_coeff.begin(); it!=var_to_coeff.end(); ++it)
    {
        if(it->first.first=="cons")
        {
            if(var_to_idx.find(it->first.first)==var_to_idx.end())
            {
                var_to_idx[it->first.first] = var_no;
                idx_to_var[var_no] = it->first.first;
                var_no++;
            }
            coeff_arr[it->first.second][var_to_idx[it->first.first]] = it->second;
        }
    }
}

void variable_parser(string s, int equation_no)
{
    int i=0;
    string coeff = "";
    string var_name = "";
    char ch[10];

    bool is_neg = is_minus(s[0]);
    bool is_cons = ((s[0]=='=')?true:false);
    if(is_cons)
    {
        is_neg = is_minus(s[1]);
        while(is_char(s[i])==false && i<s.size())
        {
            if(is_operator(s[i]))
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
        while(is_char(s[i])==false && i<s.size())
        {
            if(is_operator(s[i]))
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

    var_to_coeff[make_pair(var_name, equation_no)] = coeff_val;

}

void parser(string s, int equation_no)
{
    string temp = "";
    for(int i=0; i<s.size(); i++)
    {
        if(is_operator(s[i]))
        {
            variable_parser(temp,equation_no);
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
        variable_parser(temp2,equation_no);
    }
}

void parser_util()
{
    string s;
    int equation_no = 0;
    while(getline(cin, s))
    {
        cout<<s<<endl;
        parser(s,equation_no);
        equation_no++;
    }
    N = equation_no;
    matrix_constructor();
}

void inverse(double a[MAXN][MAXN], int x, int y)
{
    if(x==y)
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
    else
    {
        cout<<"Inverse of matrix cannot be calculated as the matrix is not a square matrix...";
    }
}

void display(double mat[MAXN][MAXN], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%5.2lf ", mat[i][j]);
        cout<<endl;
    }
}

void print_answer(double ans[][50])
{
    cout<<"\nSolution for the system:"<<endl;
    for(int i=0; i<N; i++)
    {
        cout<<idx_to_var[i]<<" = "<<mult[i][0]<<endl;
    }
}

void multiplication(double bb[MAXN])
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
    cout<<"Given Equations:"<<endl;
    parser_util();
    cout<<"\nMatrix from the equations after parsing from file:"<<endl;
    display(coeff_arr,N, N);

    double constant[MAXN];
    inverse(coeff_arr, N, N);
    for(int i=0; i<N; i++)
    {
        constant[i] = coeff_arr[i][N];
    }

    multiplication(constant);
    print_answer(mult);
    return 0;
}
