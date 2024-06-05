#include <bits/stdc++.h>
using namespace std;



int main() {

    int n;
    cin >> n;

    vector<long long> v = {1};
    vector<long long>u;
    for(int i = 0; i < 13; i++){
        v.push_back(v.back()*10 + 1);
    }

    for(int i = 0; i < v.size(); i++){
        for(int j = i; j < v.size(); j++) {
            for(int k = j; k < v.size(); k++){
                u.push_back(v[i]+v[j]+v[k]);
            }
        }
    }
    sort(u.begin(), u.end());

    cout<<u[n-1];

    return 0;
}
