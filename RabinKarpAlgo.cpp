// motivation problem copied from cp algorithm
// Determining different numbers of substring of a given string
// don't forget to define int as long long int or use other data type instead bceause int goint to over flow for sure
int RabinKarp(string& s) {
	int n = s.size();
	// int p[n + 1];
	int mod = 1e9 + 9; // probability of collision -> 1/m
	int p = 31; // prime greater then number of unique characters string contain

	int powP[n];
	powP[0] = 1;

	for(int i = 1; i < n; i++) {
		powP[i] = (powP[i - 1] * 1ll * p) % mod;
	}

	// precomputing hash function for the whole string

	int h[n + 1];
	memset(h , 0 , sizeof(h));
	for(int i = 0; i < n; i++) {
		h[i + 1] = (h[i] + (s[i] - 'a' + 1) * powP[i]) % mod;
	}

	int ans = 0;

	for(int len = 1; len <= n; len++) {
		set<int> s;
		for(int i = 0; i < n - len + 1; i++) {
			int curH = (h[i + len] - h[i] + mod) % mod;
			curH = (curH * powP[n - i - 1]) % mod;
			s.insert(curH);
		}
		ans += s.size();
	}
	return ans;
}

