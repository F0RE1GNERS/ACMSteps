// [Auto Archived]
// Submit: 2016-10-23 14:09:38
// Time: 0MS
// Memory: 1656K

#include <bits/stdc++.h>
using namespace std;

struct Node {
    string name;
    int val;
    int rank1;
    int rank2;
};

int n,m;
string query;
Node rk[300];

bool cmp(Node a, Node b) {
    return a.val > b.val || (a.val == b.val && a.name < b.name);
}

int main()
{
    while ((cin >> n) && n) {
        for (int i = 0; i < n; ++i)
            cin >> rk[i].name >> rk[i].val;
        sort(rk,rk+n,cmp);
        int cr1 = 0, cr2 = 0;
        for (int i = 0; i < n; ++i) {
            if (i == 0 || rk[i].val != rk[i-1].val) {
                cr2 = 0;
                cr1 = i+1;
            }
            cr2++;
            rk[i].rank1 = cr1;
            rk[i].rank2 = cr2;
        }
        for (int i = 0; i < n; ++i)
            cout << rk[i].name << " " << rk[i].val << endl;
        cin >> m;
        while (m--) {
            cin >> query;
            int i = 0;
            for (; i < n; ++i)
                if (rk[i].name == query)
                    break;
            if (rk[i].rank2 == 1)
                cout << rk[i].rank1 << endl;
            else cout << rk[i].rank1 << " " << rk[i].rank2 << endl;
    }
    }
    return 0;
}