#include <bits/stdc++.h>
#define INF 2000000000

using namespace std;
string s;
string tyler = "tyler";
int dp[1000][1005];
int solve(size_t i, size_t j) {
    if (i >= s.length())
        return min(j%5, 5-j%5);
    if (j >= s.length() + 5)
        return INF;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (s[i] == tyler[j%5])
        return dp[i][j] = solve(i+1,j+1);

    dp[i][j] = min(
        1 + solve(i,j+1),
        1 + solve(i+1,j)
    );
    dp[i][j] = min(
        dp[i][j],
        1 + solve(i+1,j+1)
    );
    return dp[i][j];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin>>s;
    memset(dp, -1, sizeof(dp));

    cout<<solve(0,0)<<'\n';
}