class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> seenA(n + 1, 0), seenB(n + 1, 0);
        vector<int> C(n);
        int common = 0;

        for (int i = 0; i < n; i++) {
            seenA[A[i]] = 1;
            seenB[B[i]] = 1;

            if (seenA[A[i]] && seenB[A[i]]) {
                if (seenA[A[i]] == 1 && seenB[A[i]] == 1) {
                    common++;
                    seenA[A[i]] = 2;
                    seenB[A[i]] = 2;
                }
            }

            if (A[i] != B[i] && seenA[B[i]] == 1 && seenB[B[i]] == 1) {
                common++;
                seenA[B[i]] = 2;
                seenB[B[i]] = 2;
            }

            C[i] = common;
        }

        return C;
    }
};