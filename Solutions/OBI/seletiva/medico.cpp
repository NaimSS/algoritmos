#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
#include <algorithm>
 
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
 
struct Range {
	int l, r, a, b;
};
 
const int ms = 1001000;
const unsigned long long MOD = (1LL << 30);
 
std::vector<long long> transition(std::vector<long long> a, unsigned long long v0, unsigned long long v1) {
	int n = (int) a.size();
	a.push_back(0);
	for(int i = n-1; i >= 0; i--) {
		a[i+1] = (a[i+1] + (unsigned long long) a[i] * v1 % MOD) % MOD;
		a[i] = (unsigned long long) a[i] * v0 % MOD;
	}
	return a;
}
 
unsigned long long values[ms];
int n, m;
 
long long solve(int l, int r, std::vector<Range> &ranges, std::vector<long long> dp) {
	int mid = (l + r) / 2;
	std::vector<Range> left, right;
	for(auto range : ranges) {
		if(range.l <= l && r <= range.r) {
			dp = transition(dp, range.a, range.b);
			//std::cout << "at [" << l << ", " << r << ") got " << "[" << range.l << ", " << range.r << "), " << range.a << ", " << range.b << std::endl;
		} else {
			if(std::min(mid, range.r) > std::max(l, range.l)) {
				left.push_back(range);
			}
			if(std::min(r, range.r) > std::max(mid, range.l)) {
				right.push_back(range);
			}
		}
	}
	if(l + 1 == r) {
		/*assert((int) dp.size() == n);
		std::cout << "ending at value " << values[l] << '\n';
		for(int i = 0; i < n; i++) {
			std::cout << dp[i] << (i + 1 == n ? '\n' : ' ');
		}*/
		long long ans = 0;
		for(int i = 0; i < (int) dp.size(); i++) {
			if(i > n / 2) {
				ans = (ans - dp[i] + MOD) % MOD;
			} else if(i < n / 2) {
				ans = (ans + dp[i]) % MOD;
			}
		}
		//std::cout << "ans is " << ans << std::endl;
		return (ans * values[l]) % MOD;
	}
	return (solve(l, mid, left, dp) + solve(mid, r, right, dp)) % MOD;
}
 
int main() {
	std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
	std::cin >> n ;
	m = n;
	std::vector<Range> ranges;
	std::vector<std::vector<int>> mat(n, std::vector<int>(m));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			std::cin >> mat[i][j];
			values[i * m + j] = mat[i][j];
		}
		std::sort(mat[i].begin(), mat[i].end());
	}
	std::sort(values, values + n * m);
	for(int i = 0; i < n; i++) {
		int last = -1;
		int coef = 0;
		for(auto val : mat[i]) {
			val = std::lower_bound(values, values + n * m, val) - values;
			ranges.push_back({last+1, val, coef, m - coef});
			last = val;
			coef++;
		}
		ranges.push_back({last+1, n*m, coef, m - coef});
	}
	std::cout << solve(0, n*m, ranges, std::vector<long long>(1, 1)) << '\n';
}
