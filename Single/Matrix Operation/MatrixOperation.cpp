#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

void printMatrix(int array[4][4])
{
	for (int m = 0; m < 4; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			if (array[m][n] / 10)
				cout << ' ' << array[m][n];
			else
				cout << ' ' << ' ' << array[m][n];
		}
		cout << endl;
	}
} // print a 4*4 matrix

void printMatrix2(int array[2][2])
{
	for (int m = 0; m < 2; m++)
	{
		for (int n = 0; n < 2; n++)
		{
			if (array[m][n] / 10)
				cout << ' ' << array[m][n];
			else
				cout << ' ' << ' ' << array[m][n];
		}
		cout << endl;
	}
} // print a 2*2 matrix

void compressionw(int array[4][4])
{
	for (int m = 0; m < 4; m++)
	{
		array[0][m] = array[0][m] + array[1][m] + array[2][m] + array[3][m];
	} // line 1
	for (int m = 1; m < 4; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			array[m][n] = 0;
		}
	} // line 2, 3, 4
} // to implement the compression operation
void compressiona(int array[4][4])
{
	for (int m = 0; m < 4; m++)
	{
		array[m][0] = array[m][0] + array[m][1] + array[m][2] + array[m][3];
	}
	for (int m = 1; m < 4; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			array[n][m] = 0;
		}
	}
}
void compressions(int array[4][4])
{
	for (int m = 0; m < 4; m++)
	{
		array[3][m] = array[0][m] + array[1][m] + array[2][m] + array[3][m];
	}
	for (int m = 0; m < 3; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			array[m][n] = 0;
		}
	}
}
void compressiond(int array[4][4])
{
	for (int m = 0; m < 4; m++)
	{
		array[m][3] = array[m][0] + array[m][1] + array[m][2] + array[m][3];
	}
	for (int m = 0; m < 3; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			array[n][m] = 0;
		}
	}
}
void rotate(int array[4][4])
{
	int rotatearray[4][4];
	for (int m = 0; m < 4; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			rotatearray[m][n] = array[3 - n][m];
		}
	}
	for (int m = 0; m < 4; m++)
	{
		for (int n = 0; n < 4; n++)
		{
			array[m][n] = rotatearray[m][n];
		}
	}
} // to implement the rotate operation

int main()
{
	mt19937 generator(random_device{}());
	uniform_int_distribution<int> distribution(0, 20);

	// generate a random 4*4 matrix
	int matrix[4][4] = {{distribution(generator), distribution(generator), distribution(generator), distribution(generator)},
						{distribution(generator), distribution(generator), distribution(generator), distribution(generator)},
						{distribution(generator), distribution(generator), distribution(generator), distribution(generator)},
						{distribution(generator), distribution(generator), distribution(generator), distribution(generator)}};
	printMatrix(matrix);
	cout << "Please choose the operation order :" << endl;
	cout << "compression(c) or rotate(r) or max_pooling(m)" << endl;
	char order;
	cin >> order;
	if (order == 'c')
	{
		cout << "Please choose the direction" << endl;
		char direction;
		cin >> direction;
		if (direction == 'w')
			compressionw(matrix);
		if (direction == 'a')
			compressiona(matrix);
		if (direction == 's')
			compressions(matrix);
		if (direction == 'd')
			compressiond(matrix);
		printMatrix(matrix);
	}
	if (order == 'r')
	{
		rotate(matrix);
		printMatrix(matrix);
	}
	if (order == 'm')
	{
		int result[2][2];
		result[0][0] = max({matrix[0][0], matrix[0][1], matrix[1][0], matrix[1][1]});
		result[0][1] = max({matrix[0][2], matrix[0][3], matrix[1][2], matrix[1][3]});
		result[1][0] = max({matrix[2][0], matrix[2][1], matrix[3][0], matrix[3][1]});
		result[1][1] = max({matrix[2][2], matrix[2][3], matrix[3][2], matrix[3][3]});
		printMatrix2(result);
	} // implement the max_pooling operation and print the result
	return 0;
}