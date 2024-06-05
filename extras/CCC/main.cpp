#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ifstream fin("level3_5.in");
ofstream fout("out.out");

using namespace std;

void solve_test(int test)
{
    int n,m;
    int A[21][21];
    int tree_i=0,tree_j=0;
    fin>>m>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            char x;
            fin>>x;
            if(x=='.')  A[i][j]=0;
            else
            {
                A[i][j]=1;
                tree_i=i;
                tree_j=j;
            }
        }
    char string[1000];
    fin>>string;
    int miscari=strlen(string);
    bool gasit=false;
    for(int ii=0;ii<n;ii++)
        for(int ji=0;ji<m;ji++)
        {
            if(!(ii==tree_i && ji==tree_j))
            {
                int I=ii,J=ji;
                int B[21][21]={0};
                B[tree_i][tree_j]=1;
                B[I][J]=1;
                bool okay=true;
                for(int i=0;i<miscari && okay==true;i++)
                {
                    if(string[i]=='W')
                        I--;
                    if(string[i]=='S')
                        I++;
                    if(string[i]=='A')
                        J--;
                    if(string[i]=='D')
                        J++;
                    if(I<0 || I>=n || J<0 || J>=m)
                    {
                        okay=false;
                        //cout<<"AICI1"<<endl;
                    }
                    else if(I==tree_i && J==tree_j)
                    {
                        okay=false;
                        //cout<<"AICI2"<<endl;
                    }
                    else if(B[I][J]==1)
                    {
                        okay=false;
                        //cout<<"AICI3"<<endl;
                    }
                    else
                    {
                        B[I][J]=1;
                        //cout<<"AICI4"<<endl;
                    }
                    //cout<<endl;
                }
                if(okay==true)
                {
                    /*
                    for(int x=0;x<n;x++)
                    {
                        for(int y=0;y<m;y++)
                        cout<<B[x][y];
                        cout<<endl;
                    }
                    cout<<test<<endl;*/
                    bool oky=true;

                    for(int x=0;x<n;x++)
                        for(int y=0;y<m;y++)
                            if(B[x][y]==0)
                                oky=false;
                    if(oky==true)
                    {
                        gasit=true;
                        goto yuppie;
                    }

                }

            }
        }
    yuppie:
    if(gasit==true)
    {
        fout<<"VALID"<<endl;
    }
    else fout<<"INVALID"<<endl;
}
int main()
{

    int tests;
    fin >> tests;
    for (int i = 0; i < tests; i++)
    {
        solve_test(i);
    }
    return 0;
}