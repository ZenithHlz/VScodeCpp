// // back_tracking

// #include <iostream>

// int num = 0;
// int arrangement[9] = {0};
// bool left[15] = {0}, right[15] = {0}, vertical[9] = {0};

// void arrange(int row)
// {
//     if (row == 9)
//     {
//         std::cout << "第" << ++num << "种摆放方式为：" << std::endl;
//         for (int i = 1; i < 9; i++)
//             std::cout << arrangement[i] << ' ';
//         std::cout << std::endl;
//         return;
//     }
//     for (int col = 1; col < 9; col++)
//     {
//         if (left[col + row - 2] || right[7 + col - row] || vertical[col])
//             continue;

//         left[col + row - 2] = 1;
//         right[7 + col - row] = 1;
//         vertical[col] = 1;
//         arrangement[row] = col;

//         arrange(row + 1);
//         left[col + row - 2] = 0;
//         right[7 + col - row] = 0;
//         vertical[col] = 0;
//         arrangement[row] = 0;
//     }
// }

// int main()
// {
//     arrange(1);
//     return 0;
// }

// avoid back_tracking
#include <iostream>

int num = 0;
struct arrange_state
{
    int arrangement[9];
    bool left[15], right[15], vertical[9];
} state;

void arrange(int row, arrange_state state)
{
    if (row == 9)
    {
        std::cout << "第" << ++num << "种摆放方式为：" << std::endl;
        for (int i = 1; i < 9; i++)
            std::cout << state.arrangement[i] << ' ';
        std::cout << std::endl;
        return;
    }
    for (int col = 1; col < 9; col++)
    {
        if (state.left[col + row - 2] || state.right[7 + col - row] || state.vertical[col])
            continue;

        auto next_state = state;
        next_state.arrangement[row] = col;

        next_state.left[col + row - 2] = 1;
        next_state.right[7 + col - row] = 1;
        next_state.vertical[col] = 1;
        arrange(row + 1, next_state);
    }
}

int main()
{
    for (int i = 0; i < 9; i++)
    {
        state.arrangement[i] = 0;
        state.vertical[i] = 0;
    }
    for (int i = 0; i < 15; i++)
    {
        state.left[i] = 0;
        state.right[i] = 0;
    }
    arrange(1, state);
    return 0;
}