#include <iostream>  //getchar cout
#include <cmath>     //sqrt
#include <algorithm> //sort
#include <vector>    //vector
#include <iomanip>   //fixed setprecision

int temp[100001];             // store points close to mid
std::vector<int> rpt[100001]; // divide points in temp
// rpt is an array of vector, means right points

// coordinate of points
struct coordinate
{
    int x, y, z;
} points[100001]; // points stores all points provides

// fast read to improve time complexity
int read()
{
    int sgn = 1, x = 0;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            sgn = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = 10 * x + c - '0';
        c = getchar();
    }
    return x * sgn;
}

// compare by x-coordinate to divide by harf
bool cmpx(coordinate a, coordinate b)
{
    return a.x < b.x;
}

// calculate distance of two points, and a, b are the index of points
// here I don't use sqrt to avoid comparison of double value, as well as the time sqrt consumes
int distance(int a, int b)
{
    int dx = points[a].x - points[b].x;
    int dy = points[a].y - points[b].y;
    int dz = points[a].z - points[b].z;
    return (dx * dx + dy * dy + dz * dz);
}

// find the index of point in a vector of rpt whose y-coordinate >= y( y-coordinate of a point) and is the smallest
// use binary search to reduce time consumed
int find(int y, int idx, int l, int r)
{
    if (l >= r)
        return l;
    int mid = (l + r) >> 1;
    if (points[rpt[idx][mid]].y >= y)
        return find(y, idx, l, mid);
    else
        return find(y, idx, mid + 1, r);
}

// the most important function, mini and maxi are the boundary of the points
// use divide and conquer algorithm
int ShortestDistance(int mini, int maxi)
{

    // when mini and maxi is equal( only one point included), return a large number to avoid mistakes
    if (mini == maxi)
        return INT_MAX;
    // when mini and maxi differ by 1( 2 points) or 2( 3 points), the return value is determined
    if (maxi == mini + 1)
        return distance(mini, maxi);
    if (maxi == mini + 2)
    {
        int d1 = distance(mini, maxi - 1);
        int d2 = distance(mini + 1, maxi);
        int d3 = distance(mini, maxi);
        return std::min(std::min(d1, d2), d3);
    }

    // divide the points into two and calculate them separately
    // dist is the distance and d is the square of dist
    int mid = (mini + maxi) >> 1;
    int dl = ShortestDistance(mini, mid);
    int dr = ShortestDistance(mid + 1, maxi);
    int d = std::min(dl, dr);
    double dist = sqrt(d);

    //----------------------------------------------------------------------------------------------|
    // to avoid array or vector out-of-range, all arrays and vectors are assigned from index 1, not 0|
    //----------------------------------------------------------------------------------------------|

    // points close to mid( whose x-coordinate is different mid no more than d) are stored in temp
    int cnt = 0;
    for (int i = mini; i <= mid; i++)
    {
        if (points[mid].x - points[i].x < dist)
            temp[++cnt] = i;
    }
    // midn is a boundary line. points to the left of mid are of index less than midn, right in the contrary
    int midn = cnt;
    for (int i = mid + 1; i <= maxi; i++)
    {
        if (points[i].x - points[mid].x < dist)
            temp[++cnt] = i;
    }

    // culculate the maximun and minimum of z and divide z-coordinate by minz, maxz, and d
    int minz = 100000, maxz = -100000;
    for (int i = 1; i <= cnt; i++)
    {
        minz = std::min(points[temp[i]].z, minz);
        maxz = std::max(points[temp[i]].z, maxz);
    }
    int snum = (maxz - minz) / dist / 2 + 2;

    // clear all vectors as they are global
    for (int i = 1; i <= snum; i++)
        rpt[i].clear();

    // store the index of points in the right in its own rpt
    for (int i = midn + 1; i <= cnt; i++)
        rpt[(int)((points[temp[i]].z - minz) / dist / 2 + 1.5)].push_back(temp[i]);
    // for all points in the left, calculate the distance of all posible points in the right and the left point
    // explaind in the PDF file
    for (int i = 1; i <= midn; i++)
    {

        int idx = (points[temp[i]].z - minz) / dist / 2 + 1,
            idx1 = rpt[idx].size(), idx2 = rpt[idx + 1].size();

        if (idx1)
        {
            int num = find(points[temp[i]].y, idx, 0, idx1 - 1);
            for (int j = std::max(0, num - 12); j < std::min(idx1, num + 12); j++)
                d = std::min(d, distance(temp[i], rpt[idx][j]));
        }
        if (idx2)
        {
            int num = find(points[temp[i]].y, idx + 1, 0, idx2 - 1);
            for (int j = std::max(0, num - 12); j < std::min(idx2, num + 12); j++)
                d = std::min(d, distance(temp[i], rpt[idx + 1][j]));
        }
    }

    return d;
}
int main()
{

    // fast read to get n and the coordinate of points
    int n;
    n = read();

    for (int i = 1; i <= n; i++)
    {
        points[i].x = read();
        points[i].y = read();
        points[i].z = read();
    }
    // sort them by x-coordinate
    std::sort(points + 1, points + n + 1, cmpx);

    // print the result with 6 decimal places after dot
    std::cout << std::fixed << std::setprecision(6) << sqrt(ShortestDistance(1, n));

    return 0;
}