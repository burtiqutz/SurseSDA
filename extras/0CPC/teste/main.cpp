#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<pair<int, int>> v;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.push_back({x, i + 1});
    }
    sort(v.begin(), v.end());

    cout<<v[n - 2].second;

    return 0;
}
