#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int N, eq;

map<pair<string,int>, double> var_to_coeff;
map<string, int> var_to_idx;
map<int, string> idx_to_var;
double coeff_arr[MAXN][MAXN];
double coeff_arr2[MAXN][MAXN];
double lower[MAXN][MAXN], upper[MAXN][MAXN];
double z[MAXN], x[MAXN];

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

bool is_equal(char c)
{
    return c=='='?true:false;
}


void matrix_constructor()
{
    map<pair<string,int>,double>::iterator it;

    int var_no = 0;
    for (it=var_to_coeff.begin(); it!=var_to_coeff.end(); ++it)
    {
        if(it->first.first!="cons" && it->first.first!="")
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
    N = var_no;
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
    bool is_cons = is_equal(s[0]);
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

    //variable mapping
    var_to_coeff[make_pair(var_name,equation_no)] = coeff_val;

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
    eq = equation_no;
    matrix_constructor();
}

void displaySteps(double temp[][MAXN], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << setw(6) << temp[i][j] << "\t";
        cout<<endl;
    }
    cout<<endl;
}

void luDecomposition(double mat[][MAXN], int n)
{
    memset(lower, 0, sizeof(lower));
    memset(upper, 0, sizeof(upper));

    cout<<"Initial Upper: "<<endl;
    displaySteps(upper, n);

    cout<<"Initial Lower: "<<endl;
    displaySteps(lower, n);

    printf("\n\n");

    for (int i = 0; i < n; i++)
    {
        cout<<"Upper Step: "<<i+1<<endl<<endl;
        for (int k = i; k < n; k++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
                sum += (lower[i][j] * upper[j][k]);

            upper[i][k] = mat[i][k] - sum;
        }

        displaySteps(upper, n);
        cout<<"(Lower Step: "<<i+1<<")"<<endl<<endl;
        for (int k = i; k < n; k++)
        {
            if (i == k)
                lower[i][i] = 1;
            else
            {
                double sum = 0.0;
                for (int j = 0; j < i; j++)
                    sum += (lower[k][j] * upper[j][i]);

                lower[k][i] = (double)(mat[k][i] - sum) / (double)upper[i][i];
            }
        }
        displaySteps(lower, n);
    }

    printf("\nFinal LU Decomposition:\n\n");

    cout << setw(10) << "      Lower Triangular"
         << setw(40) << "Upper Triangular" << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(6) << lower[i][j] << "\t";
        cout << "\t";

        for (int j = 0; j < n; j++)
            cout << setw(6) << upper[i][j] << "\t";
        cout << endl;
    }
}

void generateOutput(double ans[])
{
    cout<<"\nSolution for the system:"<<endl;
    for(int i=0; i<N; i++)
    {
        cout<<idx_to_var[i]<<" = "<<ans[i]<<endl;
    }
}

void backSubs(double afterEqualConstants[MAXN])
{
    double sum;

    for(int i=0;i<N;i++)
    {
        sum=0;
        for(int p=0;p<i;p++)
            sum+=lower[i][p]*z[p];
        z[i]=(afterEqualConstants[i]-sum)/lower[i][i];
    }

    cout<<"\nZ Matrix from L*Z=b:"<<endl;

    for(int i = 0; i < N; i++)
        cout<<"z"<<i+1<<" = "<<z[i]<<endl;
    puts("");

    for(int i=N-1;i>=0;i--)
    {
        sum=0;
        for(int p=N-1;p>i;p--)
            sum+=upper[i][p]*x[p];
        x[i]=(z[i]-sum)/upper[i][i];
    }
    generateOutput(x);
}

int main()
{
    freopen("input1.txt","r", stdin);
    freopen("output1.txt","w", stdout);
    cout<<"Input Equations:"<<endl;

    double afterEqualConstants[MAXN];
    parser_util();
    cout<<"\nGenerated matrix after parsing from file:"<<endl;
    displaySteps(coeff_arr, N);

    for(int i=0; i<N; i++)
    {
        afterEqualConstants[i] = coeff_arr[i][N];
    }
    luDecomposition(coeff_arr, N);
    backSubs(afterEqualConstants);

    return 0;
}
