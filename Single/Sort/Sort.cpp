#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int a[1000];

using std::cin;
using std::cout;
using std::endl;

void select_sort(int a[], int n)
{
	if (n == 1)
		return;

	int m = 0;
	for (int i = 1; i < n; i++)
		if (a[i] < a[m])
			m = i;

	if (m)
	{
		int temp = a[m];
		a[m] = a[0];
		a[0] = temp;
	}

	select_sort(a + 1, n - 1);
}

void merge_sort(int a[], int start, int end)
{
	if (start == end - 1)
		return;

	int mid = (start + end) / 2;
	merge_sort(a, start, mid);
	merge_sort(a, mid, end);

	int *tmp = new int[end - start];
	int left = start, right = mid, cnt = 0;
	while (left < mid && right < end)
	{
		if (a[left] < a[right])
			tmp[cnt++] = a[left++];
		else
			tmp[cnt++] = a[right++];
	}

	while (left < mid)
		tmp[cnt++] = a[left++];
	while (right < end)
		tmp[cnt++] = a[right++];

	cnt = 0;
	for (int i = start; i < end; i++)
		a[i] = tmp[cnt++];

	delete[] tmp;
}

void merge_sort_updated(int a[], int tmp[], int start, int end)
{
	if (start == end - 1)
		return;

	int mid = (start + end) / 2;
	merge_sort_updated(a, tmp, start, mid);
	merge_sort_updated(a, tmp, mid, end);

	int left = start, right = mid, cnt = 0;
	while (left < mid && right < end)
	{
		if (a[left] < a[right])
			tmp[cnt++] = a[left++];
		else
			tmp[cnt++] = a[right++];
	}

	while (left < mid)
		tmp[cnt++] = a[left++];
	while (right < end)
		tmp[cnt++] = a[right++];

	cnt = 0;
	for (int i = start; i < end; i++)
		a[i] = tmp[cnt++];
}

void quick_sort(int a[], int start, int end, int n)
{
	if (start >= end)
		return;

	int left = start, right = end, k = a[left];
	do
	{
		while (left < right && a[right] > k)
			right--;
		if (left < right)
			a[left++] = a[right];

		while (left < right && a[left] <= k)
			left++;
		if (left < right)
			a[right--] = a[left];
	} while (left < right);
	a[left] = k;

	quick_sort(a, start, left - 1, n);
	quick_sort(a, left + 1, end, n);
}

void quick_sort(int start, int end, int n)
{
	if (end - start <= 0)
		return;
	int left = start + 1, right = end, pivot = a[start];
	do
	{
		while (right >= left && a[right] > pivot)
			right--;
		while (right >= left && a[left] <= pivot)
			left++;
		if (right >= left)
			std::swap(a[left], a[right]);
	} while (right >= left);
	std::swap(a[start], a[right]);

	for (int i = 0; i < n; i++)
		std::cout << a[i] << ' ';
	std::cout << '\n';

	quick_sort(start, right - 1, n);
	quick_sort(right + 1, end, n);
}

int main()
{
	int a[100] = {0}, b[100] = {0}, c[100] = {0}, d[100] = {0};

	// Use the Mersenne Twister as the random number engine
	std::mt19937 rng(std::random_device{}());

	// Define a uniform distribution for integers
	std::uniform_int_distribution<int> dist(1, 100);

	// Generate and store 100 random numbers
	for (int i = 0; i < 100; ++i)
	{
		a[i] = dist(rng);
		b[i] = dist(rng);
		c[i] = dist(rng);
		d[i] = dist(rng);
	}

	select_sort(a, 100);
	for (int i = 0; i < 100; i++)
		cout << a[i] << ' ';
	cout << endl;

	merge_sort(b, 0, 100);
	for (int i = 0; i < 100; i++)
		cout << b[i] << ' ';
	cout << endl;

	int *tmp = new int[100];
	merge_sort_updated(c, tmp, 0, 100);
	delete[] tmp;
	for (int i = 0; i < 100; i++)
		cout << c[i] << ' ';
	cout << endl;

	quick_sort(d, 0, 99, 100);
	for (int i = 0; i < 100; i++)
		cout << d[i] << ' ';
	cout << endl;

	return 0;
}