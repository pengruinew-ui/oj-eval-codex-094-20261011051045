#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    if(!(cin >> m >> n)) return 0;
    vector<vector<int>> a(m, vector<int>(n));
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            cin >> a[i][j];
        }
    }
    int M = m*3, N = n*3;
    vector<vector<int>> out(M, vector<int>(N, 0));

    auto avg_vec = [&](const vector<int>& v)->int{
        long long sum=0; for(int x: v) sum+=x;
        return (int)(sum / v.size());
    };

    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            int br = i/3, bc = j/3;
            int di = i%3, dj = j%3;
            if(di==1 && dj==1){
                out[i][j] = a[br][bc];
                continue;
            }
            vector<int> A, B;
            for(int dr=-2; dr<=2; ++dr){
                for(int dc=-2; dc<=2; ++dc){
                    int nr = br + dr;
                    int nc = bc + dc;
                    if(nr<0||nr>=m||nc<0||nc>=n) continue;
                    int ci = nr*3 + 1;
                    int cj = nc*3 + 1;
                    int dist = abs(ci - i) + abs(cj - j);
                    if(dist==1) A.push_back(a[nr][nc]);
                    else if(dist==2) B.push_back(a[nr][nc]);
                }
            }
            int value=0;
            if(A.empty()){
                int avgB = avg_vec(B);
                value = avgB;
            }else if(B.empty()){
                int avgA = avg_vec(A);
                value = avgA;
            }else{
                int avgA = avg_vec(A);
                int avgB = avg_vec(B);
                double calc = avgA * 0.8 + avgB * 0.2;
                value = (int) floor(calc);
            }
            if(value<0) value=0; if(value>100) value=100;
            out[i][j] = value;
        }
    }

    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            cout << out[i][j] << ' ';
        }
        if(i+1<M) cout << '\n';
    }
    return 0;
}
