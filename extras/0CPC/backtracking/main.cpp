//C++
#include <bits/stdc++.h>
using namespace std;

int n = 3 ;
int k = 2;
int m = 1;
long long int count = 0;
char s[m][n];
void bt(int k1, string& X) {
    if (k == n) {
        count++;
        return;
    }
    for (int x = 1; x <= k1; x++) {
        X[k] = 'a' + x - 1;

        bool ok = true;
        for(int i=0; ok && i<k1; i++)
            if (strstr(s[i], X))
                ok = false;

        if (ok)
            bt(k1 + 1, X);
    }
}
int main()
{
    string X(n);
    for(int i = 0; i < m; i++){
        cin >>s[i];
    }
    bt(0, X);
    return 0;
}
