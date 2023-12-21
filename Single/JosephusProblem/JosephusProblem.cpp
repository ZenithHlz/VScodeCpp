#include <iostream>

struct person
{
    int idx;
    person *next;
} *first, *last;

int main()
{
    int n, m;
    std::cin >> n >> m;
    person *p, *q;

    p = new person;
    p->idx = 1;
    p->next = nullptr;
    first = p;
    q = p;

    for (int i = 2; i <= n; i++)
    {
        p = new person;
        p->idx = i;
        p->next = nullptr;
        q->next = p;
        q = p;
    }
    p->next = first;
    last = p;

    person *iter;
    iter = new person;
    iter->next = first;
    while (iter->next != iter)
    {
        for (int i = 0; i < m - 1; i++)
            iter = iter->next;
        std::cout << iter->next->idx << ' ';
        iter->next = iter->next->next;
    }
    std::cout << iter->idx;

    return 0;
}