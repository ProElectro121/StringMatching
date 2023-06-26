// #define long long int __int128_t
//                            Approach
// precomputing powers of prime p and hashvalue of prefix of s
// ietrating all possibel substring
class Solution {
public:
    string longestDupSubstring(string s) {
        int n = s.size();
        long long int p = 31;
        long long int mod = 1e9 + 7;
        long long int mods = 1e9 + 9;


        long long int pow1[n + 1];
        long long int pow2[n + 1];
        pow1[0] = 1;
        pow2[0] = 1;


        for(int i = 1; i <= n; i++) {
            pow1[i] = (pow1[i - 1] * 1ll * p) % mod;
        }
        for(int i = 1; i <= n; i++) {
            pow2[i] = (pow2[i - 1] * 1ll * p) % mods;
        }

        // long long int h[n + 1] = {0};
        vector<long long int> h1(n + 1 , 0);
        vector<long long int> h2(n + 1 , 0);

        for(int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] + (s[i - 1] - 'a' + 1) * pow1[i - 1]) % mod;
        }
        for(int i = 1; i <= n; i++) {
            h2[i] = (h2[i - 1] + (s[i - 1] - 'a' + 1) * pow2[i - 1]) % mods;
        }

        int strlen = -1;
        int index = -1;

        // for(int len = 1; len < n; len++) {
        //     unordered_set<long long int> st;
        //     for(int i = 0; i < n - len + 1; i++) {
        //         long long int currHash = (h[i + len] - h[i] + mod) % mod;
        //         currHash = (currHash * powP[n - i - 1]) % mod;
        //         // if(len == 3)
        //         // cout << s.substr(i , len) << " " << currHash << endl;
        //         if(st.find(currHash) != st.end()) {
        //             index = i;
        //             strlen = len;
        //         }
        //         st.insert(currHash);
        //     }
        // }
        // if(index == -1) return "";
        // return s.substr(index , strlen);

        // Lets optimse this shit with binary search

        int low = 1 , high = n - 1;

        while(low <= high) {
            long long int mid = (low + high) >> 1;

            bool ok = false;
            set<long long int> st;
            set<long long int> sts;
            for(int i = 0; i < n - mid + 1; i++) {
                long long int currHash = (h1[i + mid] - h1[i] + mod) % mod;
                currHash = (currHash * pow1[n - i - 1]) % mod;

                long long int currHashs = (h2[i + mid] - h2[i] + mods) % mods;
                currHashs = (currHashs * pow2[n - i - 1]) % mods;

                if(st.find(currHash) != st.end() and sts.find(currHashs) != sts.end()) {
                    index = i;
                    strlen = mid;
                    ok = true;
                    break;
                }
                st.insert(currHash);
                sts.insert(currHashs);
            }
            if(ok) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        string ans;
        if(index != -1) ans = s.substr(index , strlen);

        return ans;
    }
};
