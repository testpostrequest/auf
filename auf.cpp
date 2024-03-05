#include <algorithm>
#include <iostream>
#include <map>
#include <set>

using namespace std;

bool check(map<char, int> letterMap, string word1, string word2, string word3)
{
    reverse(word1.begin(), word1.end());
    reverse(word2.begin(), word2.end());
    reverse(word3.begin(), word3.end());

    int i = 0;
    int j = 0;
    int k = 0;
    int carry = 0;
    int val;

    while (i < word1.size() && j < word2.size())
    {
        int n1 = letterMap[word1.at(i)];
        int n2 = letterMap[word2.at(j)];
        int n3 = letterMap[word3.at(k)];
        i++;
        j++;
        k++;

        val = n1 + n2 + carry;

        carry = 0;
        if (val > 9)
        {
            carry = 1;
            val %= 10;
        }

        if (val != n3)
        {
            return 0;
        }
    }
    while (i < word1.size())
    {
        int n1 = letterMap[word1.at(i)];
        int n3 = letterMap[word3.at(k)];
        ++i;
        ++k;

        val = n1 + carry;

        carry = 0;
        if (val > 9)
        {
            carry = 1;
            val %= 10;
        }

        if (val != n3)
        {
            return 0;
        }
    }

    while (j < word2.size())
    {
        int n2 = letterMap[word2.at(i)];
        int n3 = letterMap[word3.at(k)];
        j++;
        k++;

        val = n2 + carry;

        carry = 0;
        if (val > 9)
        {
            carry = 1;
            val %= 10;
        }

        if (val != n3)
        {
            return 0;
        }
    }

    if (carry == 1)
    {
        if (k == word3.size())
        {
            return false;
        }
        if (letterMap[word3.at(k)] != 1)
        {
            return false;
        }
    }
    else
    {
        if (k < word3.size())
        {
            return false;
        }
    }

    return true;
}

void combo(
    map<char, int> &letterMap,
    vector<char> &letterMapKeys,
    const int &letterMapIdx,
    vector<int> &remainingNums,
    string &word1,
    string &word2,
    string &word3,
    bool &foundSolution)
{
    if (foundSolution)
    {
        return;
    }

    if (letterMapKeys.size() <= letterMapIdx)
    {
        if (check(letterMap, word1, word2, word3))
        {
            foundSolution = true;
        }
        return;
    }

    vector<int>::iterator it;
    int i = 0;
    for (i = 0, it = remainingNums.begin(); it != remainingNums.end(); it++, i++)
    {
        if (foundSolution == true)
        {
            return;
        }
        int num = *it;
        remainingNums.erase(remainingNums.begin() + i);
        letterMap[letterMapKeys.at(letterMapIdx)] = num;

        combo(letterMap, letterMapKeys, letterMapIdx + 1, remainingNums, word1, word2, word3, foundSolution);

        remainingNums.insert(remainingNums.begin() + i, num);
    }
}

void solve(string word1, string word2, string word3)
{
    cout << "Solving...\n";
    bool foundSolution = false;
    string word = word1 + word2 + word3;
    map<char, int> letterMap;
    set<char> seen;
    for (int i = 0; i != word.size(); ++i)
    {
        if (seen.find(word.at(i)) == seen.end())
        {
            seen.insert(word.at(i));
            letterMap.insert({word.at(i), -1});
        }
    }

    vector<char> letterMapKeys;
    for (pair<const char, int> const &m : letterMap)
    {
        letterMapKeys.push_back(m.first);
    }
    sort(letterMapKeys.begin(), letterMapKeys.end());
    vector<int> remainingNums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    combo(letterMap, letterMapKeys, 0, remainingNums, word1, word2, word3, foundSolution);

    if (foundSolution)
    {
        map<char, int>::iterator it;
        cout << "{";
        for (it = letterMap.begin(); it != letterMap.end(); it++)
        {
            cout << "'" << it->first << "'"
                 << ": "
                 << it->second;
            if (next(it) != letterMap.end())
            {
                cout << ", ";
            }
        }
        cout << "}\n";
    }
    else
    {
        cout << "No solution.\n";
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Usage: ./auf word1 word2 word3\n";
        return 1;
    }
    try
    {
        string word1 = argv[1];
        string word2 = argv[2];
        string word3 = argv[3];
        solve(word1, word2, word3);
    }
    catch (std::exception e)
    {
        cout << "Error: " << e.what() << "\n";
        return 2;
    }

    return 0;
}
