#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long S;
        int q;
        cin >> S >> q;
        vector<long long> d;
        for (long long i = 1; i * i <= S; i++) {
            if (S % i == 0) {
                d.push_back(i);
                if (i * i != S) d.push_back(S / i);
            }
        }
        sort(d.begin(), d.end());
        vector<long long> pref(d.size());
        long long last = 0;
        for (int i = 0; i < (int)d.size(); i++) {
            long long len = d[i] - last;
            long long height = S / d[i];
            pref[i] = len * height;
            if (i > 0) pref[i] += pref[i - 1];
            last = d[i];
        }
        auto sum = [&](long long x) {
            if (x == 0) return 0LL;
            int id = lower_bound(d.begin(), d.end(), x) - d.begin();
            long long ans = (id ? pref[id - 1] : 0);
            long long last = (id ? d[id - 1] : 0);
            ans += (x - last) * (S / d[id]);
            return ans;
        };
        while (q--) {
            long long x, y;
            cin >> x >> y;
            long long need = (S + y - 1) / y;
            int id = lower_bound(d.begin(), d.end(), need) - d.begin();
            long long full = (id ? d[id - 1] : 0);
            full = min(full, x);
            long long ans = full * y + sum(x) - sum(full);
            cout << ans << "\n";
        }
    }
}