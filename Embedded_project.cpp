#include <fstream>
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
set<string> para;


//checking the condition in if or else if loop 
string forif(vector<string> &v, int &flag, int &nest)
{ 
    
    string res = "";
    int m = v.size();
    int i = 0;
    for (i = 1; i < m; i++)
    {
        string s = v[i];
        int n = s.size();
        if (s[0] == '(' && s[n - 1] == ')')
        {
            res += " " + s;
            break;
        }
        else if (s[0] == '(')
        {
            res += " " + s;
        }
        else if (s[n - 1] == ')')
        {
            res += " " + s;
            break;
        }
        else
        {
            res += " " + s;
        }
    }

    res += " == 1 ";

    if (i < m - 1)
    {
        for (int j = i + 1; j < m; j++)
        { 
            //  if if condition and the final state in same line we will check for the final state
            string s = v[j];
            int n = s.size();
            if (s[n - 1] == '=')
            {
                string str = v[j + 1];
                nest = 0;
                res += " ------> ";
                res += str.substr(0, str.size());
                flag = 1;
                break;
            }
        }
    }
    return res;
}


//check for = sign .
string checkeq(vector<string> &v)
{ 
    string res = "";
    int m = v.size();
    for (int j = 0; j < m; j++)
    {
        string s = v[j];
        int n = s.size();
        if (s[n - 1] == '=')
        {
            string str = v[j + 1];
            res = str.substr(0, str.size());
            break;
        }
    }

    return res;
}

// the main funtion in which we run all state condition case block
vector<vector<string>> checkcase(vector<vector<string>> &vecstr, int i)
{ 
    int j = i + 1;
    vector<vector<string>> vec;
    vector<string> res;
    res.clear();
    string currcase = "";
    int nest = 0;                               // to check if the string is nested or not
    string resu = "";                           // stores the condition
    while (vecstr[j][0] != "endcase")
    { 
        // stops when detects endcase statement
        if (vecstr[j][0] == "end" || vecstr[j][0] == "default:")
        {
            j++;
            continue;
        }

        if (vecstr[j][0] == "if")
        { 
            // checks for if condition
            res.push_back("------>");
            res.push_back("if");

            int flag = 0;
            nest = 1;
            string ans = forif(vecstr[j], flag, nest);
            res.push_back(ans);
            if (flag == 0)
                resu = ans;
        }
        else if (vecstr[j].size() > 1 && vecstr[j][0] == "else" && vecstr[j][1] == "if")
        { 
            // checks for else if condition

            vec.push_back(res);
            res.clear();
            res.push_back(currcase);
            if (nest == 1)
                res.push_back(resu);
            res.push_back("------>");
            res.push_back("else");
            int flag = 0;
            string ans = forif(vecstr[j], flag, nest);
            res.push_back(ans);
        }
        else if (vecstr[j][0] == "else")
        { 
            // checks for else codition
            vec.push_back(res);
            res.clear();
            res.push_back(currcase);
            if (nest == 1)
                res.push_back(resu);
            res.push_back("------>");
            res.push_back("else :");
            res.push_back("------>");
            string s = "";
            s = checkeq(vecstr[j]);
            if (s.size() > 0)
            {
                res.push_back(s);
            }
        }

        else
        {
            string s = vecstr[j][0];
            int m = s.length();
            if (s[m - 1] == ':')
            { 
                // detects new state
                vec.push_back(res);
                res.clear();

                res.push_back(s.substr(0, m - 1));
                currcase = s.substr(0, m - 1);
            }
            else
            {
                vector<string> po = vecstr[j];
                for (int p = 0; p < po.size(); p++)
                {
                    string fed = po[p];                                     // checks the final state
                    if (para.find(fed) != para.end())
                    {
                        res.push_back("---->");

                        res.push_back(fed);
                        nest = 0;
                        resu.clear();
                    }
                }
            }
        }
        j++;
    }
    vec.push_back(res);

    return vec;
}

int main()
{
     // Verilog input
    cout << "\nEnter The Name of The Verilog File : ";
    string file_name;
    cin >> file_name;
    ifstream file(file_name);
    string curr;
    int line = 1;
    vector<vector<string>> vecstr;
    while (getline(file, curr))
    { 
        // read data from file object and put it into string.
        vector<string> code;
        int num1 = 0;
        while (num1 < curr.size())
        {
            while (num1 < curr.size() && curr[num1] == ' ')
            {
                num1++;
            }
            int num2 = num1;
            string s = "";
            while (num2 < curr.size() && curr[num2] != ' ')
            {
                s.push_back(curr[num2]);
                num2++;
            }
            if (s.size() > 0)
            {
                code.push_back(s);
            }
            num1 = num2;
        }
        vecstr.push_back(code);
    }

    vector<string> out; // stores the outputs
    int i = 1;

    para.clear(); // store the states
    while (i < vecstr.size())
    {

        if (vecstr[i][0] == "parameter")
        {
            vector<string> s = vecstr[i];
            int n = s.size();

            for (int j = 1; j < n; j++)
            {
                string h = s[j];
                int x = h.size();

                for (int k = 0; k < x; k++)
                {
                    if (h[k] == '=')
                    {
                        para.insert(h.substr(0, k));
                        break;
                    }
                }
            }
            break;
        }
        i++;
    }

    /*     while(!para.empty()){
             auto it=para.begin();
             cout<<*it<<" ";
             para.erase(it);
         }
   */

    i = 1;

    while (i < vecstr.size())
    {

        if (vecstr[i][0] == "output")
        {
            vector<string> s = vecstr[i];
            int n = s.size();

            for (int j = 1; j < n; j++)
            {
                string h = s[j];

                if (h.substr(0, 3) == "reg")
                    continue;

                out.push_back(h.substr(0, h.size() - 1));
            }
            break;
        }
        i++;
    }

    i = 1;

    set<string> seto;
    int st = 0, en = 0;

    while (i < vecstr.size())
    {

        if (vecstr[i][0] == "case")
        { 
            // checks case block in which states switching is occuring.
            st = i;

            while (i < vecstr.size() && vecstr[i][0] != "endcase")
            {
                vector<string> vec = vecstr[i];
                for (int k = 0; k < vec.size(); k++)
                {
                    seto.insert(vec[k]);
                }
                i++;
            }
            int fl = 0;
            for (int k = 0; k < out.size(); k++)
            {
                string outvar = out[k];
                if (seto.find(outvar) != seto.end())
                {
                    fl = 1;
                    break;
                }
            }
            if (fl == 0)
            {
                en = i;
                break;
            };
            seto.clear();
        }
        i++;
    }

    vector<vector<string>> ans = checkcase(vecstr, st); // 2-D vector for storing each condition in 1 vector string.
    cout << endl;
    cout << "/*******************************************************************************************************************************" << endl << endl;
    cout << "                            Finite State Machine For " << file_name  << endl << endl;
    cout << "********************************************************************************************************************************/";
    for (auto e : ans)
    {
        for (auto s : e)
        {
            cout << s << " "; // outputs state  with applied condition
        }
        cout << endl;
        cout << endl;
    }

    return 0;
}