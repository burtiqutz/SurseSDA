#include <bits/stdc++.h>
using namespace std;
ifstream f("test01_01_01.txt");


int main() {
    vector<pair<int, int>> v;
    int n, k;
    f >> n;
    f >> k;
    for(int i = 0; i < n; i++) {
        int x;
        f >> x;
        v.push_back({x, i});
    }

    sort(v.begin(), v.end());

    cout<<v[k].second;

    return 0;
}
