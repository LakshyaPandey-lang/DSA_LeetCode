class Solution {
public:
    bool checkString(string s) {
        bool b = false;
        for(int i=0; i<s.size(); i++){
            if(s[i] == 'b'){
                b = true;
            }
            if(s[i] == 'a' && b){
                return false;
            }
        }
        return true;
    }
};