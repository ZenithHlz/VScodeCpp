#include <iostream>

int ring[9] = {0};

void change(int idx, int pos)
{
    if (ring[idx] == pos)
        return;
    if (idx > 0)
        change(idx - 1, 0);
    for (int i = idx - 2; i >= 0; i--)
        change(i, -1);
    ring[idx] = pos;
    std::cout << "operate on " << idx + 1 << "  NOW ";
    for (int i = 0; i < 9; i++)
        std::cout << ring[i] << ' ';
    std::cout << std::endl;
}

int main()
{
    for (int i = 0; i < 9; i++)
        ring[i] = 0;
    ring[6] = -1;
    ring[8] = -1;
    for (int i = 8; i > 0; i--)
        change(i, -1);
    return 0;
}