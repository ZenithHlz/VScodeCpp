#include <iostream>

int num = 0;

struct answer
{
    int m;
    bool updown;
    int n;
    int y;
} way[9];

void print_answer(answer a)
{
    using std::cout;
    std::cout << "马";
    switch (a.m)
    {
    case 1:
        cout << "九";
        break;
    case 2:
        cout << "八";
        break;
    case 3:
        cout << "七";
        break;
    case 4:
        cout << "六";
        break;
    case 5:
        cout << "五";
        break;
    case 6:
        cout << "四";
        break;
    case 7:
        cout << "三";
        break;
    case 8:
        cout << "二";
        break;
    case 9:
        cout << "一";
        break;
    }
    if (a.updown)
        cout << "进";
    else
        cout << "退";
    switch (a.n)
    {
    case 1:
        cout << "九";
        break;
    case 2:
        cout << "八";
        break;
    case 3:
        cout << "七";
        break;
    case 4:
        cout << "六";
        break;
    case 5:
        cout << "五";
        break;
    case 6:
        cout << "四";
        break;
    case 7:
        cout << "三";
        break;
    case 8:
        cout << "二";
        break;
    case 9:
        cout << "一";
        break;
    }
    cout << " ( " << a.n << " , " << a.y << " )\n";
}

void go(int m, int n, int s)
{
    if (m == 9 && n == 5)
    {
        std::cout << "第" << ++num << "种走法\n";
        for (int i = 1; i < s; i++)
        {
            print_answer(way[i]);
        }
    }
    if (m + 1 <= 9 && n + 2 <= 5)
    {
        way[s] = {m, 1, m + 1, n + 2};
        go(m + 1, n + 2, s + 1);
    }
    if (m + 1 <= 9 && n - 2 >= 1)
    {
        way[s] = {m, 0, m + 1, n - 2};
        go(m + 1, n - 2, s + 1);
    }
    if (m + 2 <= 9 && n + 1 <= 5)
    {
        way[s] = {m, 1, m + 2, n + 1};
        go(m + 2, n + 1, s + 1);
    }
    if (m + 2 <= 9 && n - 1 >= 1)
    {
        way[s] = {m, 0, m + 2, n - 1};
        go(m + 2, n - 1, s + 1);
    }
}

int main()
{
    for (int i = 1; i < 9; i++)
        way[i] = {0, 0, 0};

    go(1, 1, 1);
}