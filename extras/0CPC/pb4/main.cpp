#include <bits/stdc++.h>
using namespace std;

ifstream f("test01_03_01.txt");

int main() {

    vector<pair<int, int>> intervals;
    vector<pair<int, int>> max;

    int n;
    f >>n;
    for(int i = 0; i < n; i++){
        int x, y;
        f>>x>>y;
        intervals.push_back({x, y});
    }

    sort(intervals.begin(), intervals.end());
    max.push_back({intervals[0].first, intervals[0].second});

    int i = 0;
    
    for(auto it : intervals){
        if(it.first < max[i].first && it.second <= max[i].second && it.second > max[i].first)
            max[i].first = it.first;
        if(it.first > max[i].first && it.first <= max[i].second && it.second > max[i].second )
            max[i].second = it.second;
    }

    cout << max[i].first << " "<< max[i].second;

    return 0;
}
