
class Solution {
    string s;
    int i = 0;

    set<string> parse() {
        set<string> result;
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {
            if (s[i] == ',') {
                result.insert(current.begin(), current.end());
                current = {""};
                i++;
            } else {
                set<string> next;

                if (s[i] == '{') {
                    i++;
                    next = parse();
                    i++;
                } else {
                    next.insert(string(1, s[i]));
                    i++;
                }

                set<string> temp;

                for (const string& a : current) {
                    for (const string& b : next) {
                        temp.insert(a + b);
                    }
                }

                current = move(temp);
            }
        }

        result.insert(current.begin(), current.end());
        return result;
    }

public:
    vector<string> braceExpansionII(string expression) {
        s = expression;
        i = 0;

        set<string> ans = parse();
        return vector<string>(ans.begin(), ans.end());
    }
};