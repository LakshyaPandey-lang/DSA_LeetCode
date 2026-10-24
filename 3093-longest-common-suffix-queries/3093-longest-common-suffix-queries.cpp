
class Solution {
public:
    struct Node {
        int child[26];
        int idx;

        Node() {
            fill(child, child + 26, -1);
            idx = -1;
        }
    };

    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        vector<Node> trie(1);
        int best = 0;

        for (int i = 1; i < wordsContainer.size(); i++) {
            if (wordsContainer[i].size() < wordsContainer[best].size())
                best = i;
        }

        trie[0].idx = best;

        for (int i = 0; i < wordsContainer.size(); i++) {
            int node = 0;

            for (int j = wordsContainer[i].size() - 1; j >= 0; j--) {
                int c = wordsContainer[i][j] - 'a';

                if (trie[node].child[c] == -1) {
                    trie[node].child[c] = trie.size();
                    trie.emplace_back();
                }

                node = trie[node].child[c];

                if (trie[node].idx == -1 ||
                    wordsContainer[i].size() < wordsContainer[trie[node].idx].size()) {
                    trie[node].idx = i;
                }
            }
        }

        vector<int> ans;

        for (string& q : wordsQuery) {
            int node = 0;
            int res = trie[0].idx;

            for (int j = q.size() - 1; j >= 0; j--) {
                int c = q[j] - 'a';

                if (trie[node].child[c] == -1)
                    break;

                node = trie[node].child[c];
                res = trie[node].idx;
            }

            ans.push_back(res);
        }

        return ans;
    }
};

