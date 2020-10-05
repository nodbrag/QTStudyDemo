#include <QCoreApplication>
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

class Operation
{
public:
    static int getValue(const string& oper)
    {
        static int ADD = 1;
        static int SUB = 1;
        static int MUL = 2;
        static int DIV = 2;

        int res = 0;
        if (oper == "+")
        {
            res = ADD;
        }
        else if (oper == "-")
        {
            res = SUB;
        }
        else if (oper == "*")
        {
            res = MUL;
        }
        else if (oper == "/")
        {
            res = DIV;
        }
        return res;
    }

};

bool isNum(const string& str)
{
    stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d))
        return false;
    if (sin >> c)
        return false;
    return true;
}

// 中缀表达式转后缀表达式;12+(23-6)*16=>12 23 6 - 16 * +
vector<string> infixToPostfixExpression(vector<string>& exp)
{
    stack<string> s1;
    vector<string> s2;

    for (int i = 0; i < exp.size(); i++)
    {
        string item = exp[i];

        if (isNum(item))  // 操作数
        {
            s2.push_back(item);
        }
        else if (item == "(")
        {
            s1.push(exp[i]);
        }
        else if (item == ")")
        {
            while (s1.top() != "(")
            {
                s2.push_back(s1.top());
                s1.pop();
            }
            s1.pop();
        }
        else  // 操作符+，-，*，/
        {
            while (s1.size() != 0 && Operation::getValue(s1.top()) >= Operation::getValue(item))
            {
                s2.push_back(s1.top());
                s1.pop();
            }
            s1.push(item);
        }
    }

    while (s1.size() != 0)
    {
        s2.push_back(s1.top());
        s1.pop();
    }
    return s2;
}

//"12+(23-6)*16"，将中缀表达式各个对象进行分割
// 12,+,(,23,-,6,),*,16
vector<string> toInfixExpression(const string& str)
{
    vector<string> infix;
    int i = 0;
    while (i < str.length())
    {
        char chr = str[i];
        if (chr < '0' || chr > '9')
        {
            infix.push_back(string(1, chr));
            i++;
        }
        else
        {
            string temp;
            while (i < str.length() && str[i] >= '0' && str[i] <= '9')
            {
                temp.push_back(str[i]);
                i++;
            }
            infix.push_back(temp);
        }
    }
    return infix;
}

void printVector(const vector<string>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}

int calculate(const vector<string>& postfix)
{
    stack<string> tempStack;
    for (int i = 0; i < postfix.size(); i++)
    {
        string item = postfix[i];
        if (isNum(item))
        {
            tempStack.push(item);
        }
        else
        {
            int num2 = atoi(tempStack.top().c_str());
            tempStack.pop();
            int num1 = atoi(tempStack.top().c_str());
            tempStack.pop();

            int res = 0;
            if (item == "+")
                res = num1 + num2;
            else if (item == "-")
                res = num1 - num2;
            else if (item == "*")
                res = num1 * num2;
            else if (item == "/")
                res = num1 / num2;
            else
                res = -1;

            stringstream r;
            string ss;
            r << res;
            r >> ss;
            tempStack.push(ss);
        }
    }

    string str = tempStack.top();
    tempStack.pop();
    int res = atoi(str.c_str());

    return res;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string str = "12+(23-6)*16";

    vector<string> infix = toInfixExpression(str);
    printVector(infix);

    vector<string> postfix = infixToPostfixExpression(infix);
    printVector(postfix);

    int result = calculate(postfix);
    cout << result;

    return a.exec();
}

