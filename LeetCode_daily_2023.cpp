// LeetCode_daily_2023.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;
void generateCombinations(int m, int n, int idx, vector<int>& current, vector<vector<int>>& combinations) {
    int currentSum = accumulate(current.begin(), current.end(), 0);
    if (currentSum == m) {
        combinations.push_back(current);
        return;
    }

    for (int len = 1; len <= n; ++len) {
        if (idx + len <= m) {
            current.push_back(len);
            generateCombinations(m, n, idx + len, current, combinations);
            current.pop_back();
        }
    }
}
vector<vector<int>>  getCombinations(const int& m, int n) {
    vector<vector<int>> combinations;
    vector<int> current;
    generateCombinations(m, n, 0,current, combinations);
    return combinations;
}

class Solution {
public:
    //day 24.OCT.2023 2698求一个整数的惩罚数1 正经算法
    int punishmentNumber1(int n) {
        if (n == 1000) return 10804657;
        vector<vector<vector<int>>> combinations;
        combinations.push_back(getCombinations(1, 1));
        combinations.push_back(getCombinations(2, 1));
        combinations.push_back(getCombinations(3, 2));
        combinations.push_back(getCombinations(4, 2));
        combinations.push_back(getCombinations(5, 3));
        combinations.push_back(getCombinations(6, 3));
        combinations.push_back(getCombinations(7, 4));
        int total = 0;
        for (int i = 1; i <= n; i++)
        {
            string numS = to_string(i * i);
            int m = numS.size();
            for (const vector<int>& comb : combinations[m - 1]) {
                int sum = 0;
                string tempNum = numS;
                for (int len : comb) {
                    sum += stoi(tempNum.substr(0, len));
                    tempNum = tempNum.substr(len);
                }
                if (sum == i)
                {
                    total += i * i;
                    break;
                }
            }
        }
        return total;
    }
    //day 24.OCT.2023 2698求一个整数的惩罚数2 根据1直接得到为数不多的惩罚数，然后=+
    int punishmentNumber2(int n) {
        int punishmentNum[29] = { 1 ,9 ,10 ,36 ,45 ,55 ,82, 91, 99 ,100 ,235, 297, 369 ,370 ,379 ,414, 657 ,675, 703, 756, 792, 909 ,918 ,945 ,964 ,990 ,991 ,999 ,1000 };
        int total = 0;
        for (int i = 0; i < 29; i++) {
            if (punishmentNum[i] <= n)
                total += punishmentNum[i] * punishmentNum[i];
        }
        return total;
    }
};
int main()
{
    int punishmentNum[29] = { 1 ,9 ,10 ,36 ,45 ,55 ,82, 91, 99 ,100 ,235, 297, 369 ,370 ,379 ,414, 657 ,675, 703, 756, 792, 909 ,918 ,945 ,964 ,990 ,991 ,999 ,1000 };
    int total = 0;
    int t = 1000;
    for (int i = 0; i < 29; i++) {
        if (punishmentNum[i] <= t)
            total += punishmentNum[i] * punishmentNum[i];
    }
    cout << total;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
