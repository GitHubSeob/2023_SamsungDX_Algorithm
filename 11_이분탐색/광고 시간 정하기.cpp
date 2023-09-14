#include <iostream>
#include <vector>
#include <cstring>
#define MAX 100001
using namespace std;

int s[MAX], e[MAX], sum[MAX];

int main(){    
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T(0), L(0), N(0);
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case)
    {
        cin >> L >> N;
        memset(s, 0, sizeof(s));
        memset(e, 0, sizeof(e));
        memset(sum, 0, sizeof(sum));       

        for (int idx = 0; idx < N; ++idx) {
            cin >> s[idx] >> e[idx];            
        }
        

        sum[0] = e[0] - s[0];
        for (int idx = 1; idx <= N; ++idx)
            sum[idx] = sum[idx - 1] + e[idx - 1] - s[idx - 1];

        int start(0), end(0);        
        int answer(0);

        while (end < N) {
            while (start <= end && s[start] + L <= e[end]) {
                int sub = s[start] + L - s[end];
                if (sub > 0)
                    answer = max(answer, sum[end] - sum[start] + sub);
                else 
                    answer = max(answer, sum[end] - sum[start]);
                ++start;
            }
            ++end;
        }
        answer = max(answer, sum[N] - sum[start]);
        cout << "#" << test_case << " " << answer << '\n';
    }

    return 0;
}