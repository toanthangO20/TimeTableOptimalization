#include <bits/stdc++.h>
#define N 1005
#define M 105

using namespace std;

int n, m; // Số lớp học và phòng học
int t[N], g[N], s[N]; // Số tiết học, giáo viên được phân công dạy lớp và số học sinh của lớp
int c[M]; // Số chỗ ngồi của mỗi phòng học
int above; //Số lớp có chỗ ngồi không vượt quá chỗ ngồi các phòng
int maxRoom; //Số chỗ ngồi nhiều nhất của một lớp

bool markTeacher[105][65]; // markTeacher[i][j] : Giáo viên i đã dạy tiết j
bool markRoom[M][65]; //markRoom[i][j] : Phòng i đã bận vào tiết j

int p[N], r[N]; // Tiết học và phòng học được gán cho mỗi lớp
int countClass; // Đếm số lớp xếp được lịch

int maxClass; // Số lượng lớp lớn nhất có thể xếp
int pmax[N], rmax[N]; // pmax[i], rmax[i]: Ghi nhận cấu hình tốt nhất của tiết học bắt đầu và phòng học

int f; //Biến để sử dụng nhánh và cận

int debug;

void input()
{
    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    above = n;
    maxRoom = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i] >> g[i] >> s[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> c[i];
        maxRoom = maxRoom > c[i] ? maxRoom : c[i];
    }
    for (int i = 1; i <= n; i++)
    {
        if(s[i] > maxRoom) above--;
    }
    f = 0;
    //cout << "above: " << above << endl;
}

void setInitValue()
{
    countClass = 0;
    for (int i = 1; i <= 100; i++)
    {
        for (int j = 1; j <= 60; j++)
        {
            markTeacher[i][j] = false;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= 60; j++)
        {
            markRoom[i][j] = false;
        }
    }
    maxClass = 0;
}

bool check(int k, int v1, int v2)
{
    if (maxClass == above) return false;
    if (v1 == 0 && v2 == 0) return true;
    if((v1 == 0 && v2 > 0) || (v1 > 0 && v2 == 0)) return false;
    // markTeacher[g[k]][v1]
    for (int i = 1; i <= t[k]; i++)
    {
        if (markTeacher[g[k]][v1+i-1]) return false;
        if (markRoom[v2][v1+i-1]) return false;
    }
    if (s[k] > c[v2]) return false;
    if ((60 - v1) % 6 + 1 < t[k]) return false;
    return true;
}

void updateBestSolution()
{
    if (countClass > maxClass)
    {
        maxClass = countClass;
        for (int i = 1; i <= n; i++)
        {
            pmax[i] = p[i];
            rmax[i] = r[i];
        }
    }
}

void printBestSolution()
{
    cout << maxClass << endl;
    for (int i = 1; i <= n; i++)
    {
        if (pmax[i] > 0)
        {
            cout << i << " " << pmax[i] << " " << rmax[i] << endl;
        }
    }
}

void trySolution(int k)
{
    for (int a = 1; a <= 61; a++)
    {
        for (int b = 1; b <= m + 1; b++)
        {
            int v1 = a % 61;
            int v2 = b % (m+1);
            if(check(k, v1, v2))
            {
                p[k] = v1;
                r[k] = v2;
                if (v1 > 0)
                {
                    for (int i = 1; i <= t[k]; i++)
                    {
                        markTeacher[g[k]][v1+i-1] = true;
                        markRoom[v2][v1+i-1] = true;
                    }
                    countClass++;

                    //if (debug == 99 || debug == 100) cout << "Da cong countClass" << endl;
                }
                if (k == n)
                {
                    updateBestSolution();
                    //setInitValue();
                }
                else
                {
                    f = countClass + n - k;
                    if (f > maxClass) trySolution(k+1);
                }
                if (v1 > 0)
                {
                    for (int i = 1; i <= t[k]; i++)
                    {
                        markTeacher[g[k]][v1+i-1] = false;
                        markRoom[v2][v1+i-1] = false;
                    }
                    countClass--;
                    //if (debug == 99 || debug == 100) cout << "Da tru countClass" << endl;
                }
            }
        }
    }
}

int main()
{
    input();
    setInitValue();
    debug = 0;
    trySolution(1);
    printBestSolution();
    return 0;
}
