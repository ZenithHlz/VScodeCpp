#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <random>
#include <algorithm>

int num(std::string s)
{
	std::regex check("\\b(\\d+)\\b");
	std::smatch match;
	int number = 0;
	if (std::regex_search(s, match, check))
		number = std::stoi(match[1].str());
	return number;
} // This function is used to convert a string in the form as "STRING = N" to an int N

void printM(std::vector<std::vector<char>> matrix)
{
	std::ofstream cmd("cmd.txt", std::ios::app);
	if (cmd.is_open())
	{
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix.size(); j++)
			{
				if (matrix[i][j] != '*')
					cmd << int(matrix[i][j]) << ' ';
				else
					cmd << '*' << ' ';
			}
			cmd << '\n';
		}
		cmd.close();
	}
	else
		std::cout << "Failed to create/open the file \"cmd.txt\"" << std::endl;
} /*The function is used to write the matrix to the file cmd.txt
 If there is no cmd.txt, it will create a new one. If failed, it will remind the user*/

int randomtf()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 2);
	int number = dis(gen);
	int random = number * 2;
	return random;
} // a function to generate randomly 2 or 4 (t or f)

int randomr(int n)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, n * n - 1);
	int num = dis(gen);
	return num;
}

std::vector<int> random(int n, int r)
{
	int size = n * n * r / 100;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<int> v;
	for (int i = 0; i < n * n; i++)
	{
		v.push_back(i);
	}
	std::shuffle(v.begin(), v.end(), gen);
	std::vector<int> result(v.begin(), v.begin() + size);
	return result;
} /*a function to generate some random numbers different from each other
  and the number of the numbers is decided by n and r*/

int main()
{
	std::ifstream config("config.txt");
	int N = 4, R = 0;

	if (config.is_open())
	{
		std::string s, n_check = "NONE";
		/*The string n_check is used to check whether the N in the last line
		with the pattern "FILESIZE = N" is negetive or positive. */

		std::regex np("^FILESIZE = (\\d+) ");
		std::regex nps("^FILESIZE = -(\\d+) "), np0("^FILESIZE = 0(\\d+) ");
		std::regex rp("^RANDNUM = (\\d+) "), rp0("^RANDNUM = 0(\\d+) ");

		while (std::getline(config, s))
		{
			if ((std::regex_search(s, np) || std::regex_search(s, nps)) && !std::regex_search(s, np0))
			{
				N = num(s);
				n_check = s;
			} // find N
			if (std::regex_search(s, rp) && !std::regex_search(s, rp0))
			{
				int temp = num(s);
				if (temp >= 0 && temp < 100)
					R = temp;
			} // find an R in the range [0,100)
		}
		if (std::regex_search(n_check, nps) || N == 0 || n_check == "NONE")
		{
			std::cout << "配置文件格式不对" << std::endl
					  << std::endl;
			N = 4;
		} // if N is a negetive integer or 0
		config.close();
	}
	else
	{
		std::cout << "配置文件格式不对" << std::endl
				  << std::endl;
	}

	std::cout << "The execution result of step 1 is: N = " << N << std::endl;
	std::cout << "The execution result of step 2 is: R = " << R << std::endl
			  << std::endl;
	// print the result of step 1 and 2

	std::vector<std::vector<char>> matrix;
	for (int i = 0; i < N; i++)
	{
		std::vector<char> v;
		for (int j = 0; j < N; j++)
		{
			v.push_back('*');
		}
		matrix.push_back(v);
	} // generate a matrix with the size N*N filled with *

	std::cout << "The location(s) of the random numbers in the matrix is(are): " << std::endl;

	if (R != 0)
	{
		std::cout << "(There are N*N*R/100 =  " << N * N * R / 100 << " numbers to be inserted to the matrix)";
		std::cout << " (round down)" << std::endl
				  << std::endl;
		std::vector<int> randnum_position = random(N, R);
		for (int mem : randnum_position)
			matrix[mem / N][mem % N] = randomtf();
		/*generate N*N*R/100 random numbers and use each of them to specify a position in the matrix
		and assign a value of 2 or 4 to the element */

		std::sort(randnum_position.begin(), randnum_position.end());
		int cout_check = randnum_position[1] / N;
		for (int i : randnum_position)
		{
			if (cout_check / N != i / N)
				std::cout << std::endl;
			std::cout << '(' << i / N << ',' << i % N << ')' << ' ';
			cout_check = i;
		}
		std::cout << std::endl; // print the location of random numbers(2/4) in the matrix
	}
	else
	{
		int idx = randomr(N);
		std::cout << '(' << idx / N << ',' << idx % N << ')' << ' ' << std::endl;
		matrix[idx / N][idx % N] = randomtf();
	}

	printM(matrix);
	std::cout << std::endl
			  << "Successfully print a matrix." << std::endl
			  << std::endl;

	std::cout << "If you want to end this program, please tap Q and enter \"enter\"   ";

	char to_end = 0;
end:
	std::cin >> to_end;
	if (to_end == 'Q')
		return 0;
	else
	{
		std::cout << "Don't want to end? Please tap Q and enter \"enter\"   ";
		goto end;
	}
}