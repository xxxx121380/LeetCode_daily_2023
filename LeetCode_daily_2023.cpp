// LeetCode_daily_2023.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

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
    //day 24.OCT.2023 2698 求一个整数的惩罚数1 正经算法
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
    //day 24.OCT.2023 2698 求一个整数的惩罚数2 根据1直接得到为数不多的惩罚数，然后=+
    int punishmentNumber2(int n) {
        int punishmentNum[29] = { 1 ,9 ,10 ,36 ,45 ,55 ,82, 91, 99 ,100 ,235, 297, 369 ,370 ,379 ,414, 657 ,675, 703, 756, 792, 909 ,918 ,945 ,964 ,990 ,991 ,999 ,1000 };
        int total = 0;
        for (int i = 0; i < 29; i++) {
            if (punishmentNum[i] <= n)
                total += punishmentNum[i] * punishmentNum[i];
        }
        return total;
    }
    //day 25.OCT.2023 2520 统计能整除数字的位数
    int countDigits(int num) {
        int canDivide[9] = { 0,0,0,0,0,0,0,0,0 };
        int sum = 0;
        for (int i = 1; i <= 9; i++)
        {
            if (num % i == 0) {
                canDivide[i - 1] = 1;
            }
        }
        while (num > 0) {
            if (canDivide[num % 10 - 1] == 1)sum++;
            num = num / 10;
        }
        return sum;
    }
    //day 26.OCT.2023 1465 切割后面积最大的蛋糕
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        const int mod = 1e9 + 7;
        horizontalCuts.push_back(h);
        verticalCuts.push_back(w);
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        long long height = horizontalCuts[0];
        long long weight = verticalCuts[0];
        for (int i = 0; i < horizontalCuts.size() - 1; i++)
        {
            if (height < horizontalCuts[i + 1] - horizontalCuts[i])height = horizontalCuts[i + 1] - horizontalCuts[i];
        }
        for (int i = 0; i < verticalCuts.size() - 1; i++)
        {
            if (weight < verticalCuts[i + 1] - verticalCuts[i])weight = verticalCuts[i + 1] - verticalCuts[i];
        }
        return weight * height % mod;
    };
    //day 27.OCT.2023 2558 从数量最多的堆取走礼物
    long long pickGifts(vector<int>& gifts, int k) {
        for (int i = 0; i < k; i++)
        {
            auto max_it = max_element(gifts.begin(), gifts.end());
            int position = distance(gifts.begin(), max_it);
            gifts[position] = floor(sqrt(gifts[position]));
        }
        return accumulate(gifts.begin(), gifts.end(), 0LL);
    }
    //day 28.OCT.2023 274 H 指数
    int hIndex(vector<int>& citations) {
        int ci[1000];
        int sizeCi = citations.size();
        fill(ci, ci + 1000, 0);
        for (int i = 0; i < citations.size(); i++) {
            ci[citations[i]]++;
        }
        //t 表示当前选中多少篇 从1000往下，需要保证选中篇数>指数i
        int t = 0;
        for (int i = 999; i >= 0; i--) {
            t += ci[i];
            if (t >= i)
                return i;
        }
        return 1;
    }
    //day 29.OCT.2023 275 H 指数 II
    int hIndex2(vector<int>& citations) {
        int left = 0;
        int right = citations.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            //当前引用值 要比剩余量多
            if (citations[mid] >= citations.size() - mid) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return citations.size() - left;
    }
};
int main()
{
    Solution solution;
    vector<int> citations = { 0,1,3,5,6 };
    cout << solution.hIndex2(citations);
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
