#include "ios.h"

using namespace std;

namespace bf
{
    string trim_left(string s)
    {
        if (s.empty()) return s;
        string result;
        int i;
        for (i = 0; s[i] == ' '; ++i);
        for (i = i; i < s.length(); ++i)
            result += s[i];
        return result;
    }

    string trim_right(string s)
    {
        if (s.empty()) return s;
        string result;
        int j;
        for (j = s.length() - 1; s[j - 1] == ' '; --j);
        for (int i = 0; i < j; ++i)
            result += s[i];
        return result;
    }

    string trim(string s)
    {
        return trim_left(trim_right(s));
    }

    void lower_case(string &s)
    {
        for (unsigned int i = 0; i < s.length(); i++)
            if ((s[i] >= 'A') && (s[i] <= 'Z'))
                s[i] = 'a' + (s[i] - 'A');
    }

    int str2int(string s)
    {
        int x;
        stringstream ss;
        ss.clear();
        ss << s;
        ss >> x;
        return x;
    }

    string int2str(int x)
    {
        string s;
        stringstream ss;
        ss.clear();
        ss << x;
        ss >> s;
        return s;
    }

    vector<string> get_words(const string s)
    {
        vector<string> result;
        stringstream ss;
        ss.clear();
        ss << s;
        string s1;
        while (ss >> s1)
            result.push_back(s1);
        return result;
    }
//s
    string trim_all(string s)
    {
        string result;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ')
                continue;
            result += s[i];
        }
        return result;
    }
}
