// // back_tracking

// #include <iostream>

// int like[5][5] = {{0, 0, 1, 1, 0},
//                   {1, 1, 0, 0, 1},
//                   {0, 1, 1, 0, 1},
//                   {1, 0, 0, 1, 0},
//                   {1, 1, 0, 0, 1}};

// int num = 1;
// int assignment[5] = {-1, -1, -1, -1, -1};

// void assign(int person)
// {
//     if (person == 5)
//     {
//         std::cout << "第" << num++ << "种方案: ";
//         for (int i = 0; i < 5; i++)
//             std::cout << assignment[i] << ' ';
//         std::cout << std::endl;
//         return;
//     }
//     for (int book = 0; book < 5; book++)
//     {
//         if (like[person][book] == 0 || assignment[book] != -1)
//             continue;
//         assignment[book] = person;
//         assign(person + 1);
//         assignment[book] = -1;
//     }
// }

// int main()
// {
//     assign(0);
//     return 0;
// }

// avoid back_tracking

#include <iostream>

int like[5][5] = {{0, 0, 1, 1, 0},
                  {1, 1, 0, 0, 1},
                  {0, 1, 1, 0, 1},
                  {1, 0, 0, 1, 0},
                  {1, 1, 0, 0, 1}};

int num = 1;
struct state
{
    int assignment[5];
} statement;

void assign(int person, state statement)
{
    if (person == 5)
    {
        std::cout << "第" << num++ << "种方案: ";
        for (int i = 0; i < 5; i++)
            std::cout << statement.assignment[i] << ' ';
        std::cout << std::endl;
        return;
    }
    for (int book = 0; book < 5; book++)
    {
        if (like[person][book] == 0 || statement.assignment[book] != -1)
            continue;
        auto next_statement = statement;
        next_statement.assignment[book] = person;
        assign(person + 1, next_statement);
    }
}

int main()
{
    for (int i = 0; i < 5; i++)
        statement.assignment[i] = -1;
    assign(0, statement);
    return 0;
}