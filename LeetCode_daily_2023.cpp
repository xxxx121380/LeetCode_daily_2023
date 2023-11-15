// LeetCode_daily_2023.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <queue>
#include <stack>
#include <set>
#include <map>
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
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
private:
    map<int, int> intervals;
    vector<int> sum; // sum[i] 表示第 i 个块的元素和
    int size; // 块的大小
    vector<int>& nums;

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
    //day 30.OCT.2003 每棵子树内缺失的最小基因值
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size();
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; i++) {
            tree[parents[i]].push_back(i);
        }

        unordered_set<int> values;
        vector<int> visited(n, 0);
        function<void(int)> dfs = [&](int node) {
            if (visited[node]) {
                return;
            }
            visited[node] = 1;
            values.insert(nums[node]);
            for (auto child : tree[node]) {
                dfs(child);
            }
        };

        vector<int> res(n, 1);
        int iNode = 1, node = -1;
        for (int i = 0; i < n; i++) {
            if (nums[i] == 1) {
                node = i;
                break;
            }
        }
        while (node != -1) {
            dfs(node);
            while (values.count(iNode)) {
                iNode++;
            }
            res[node] = iNode;
            node = parents[node];
        }
        return res;
    }
    //day 31.OCT.2023 
    int maximumInvitations(vector<int>& favorite) {
        unordered_map<int, int> adjList;
        pair<int, int> cycleNodes = { -1, -1 };
        vector<bool> visited;
        set<int> pathSet;
        vector<int> path;
        int maxCycleLength = 2, maxChainLength = 0;
        int n = favorite.size();
        for (int i = 0; i < n; i++) {
            adjList[i] = favorite[i];
        }

        function<void(int)> dfs = [&](int node) {
            if (pathSet.find(node) != pathSet.end()) {
                if (path.back() == adjList[node]) {
                    cycleNodes = { node, path.back() };
                }
                maxCycleLength = std::max(maxCycleLength, (int)(path.size() - distance(path.begin(), find(path.begin(), path.end(), node))));
                return;
            }
            if (visited[node]) {
                return;
            }
            visited[node] = true;
            path.push_back(node);
            pathSet.insert(node);
            if (adjList.find(node) != adjList.end()) {
                dfs(adjList[node]);
            }
            path.pop_back();
            pathSet.erase(node);
        };

        function<int(int)> getLongestSubchainLength = [&](int node) {
            vector<bool> localVisited(adjList.size(), false);
            localVisited[adjList[node]] = true;
            queue<pair<int, int>> q;
            q.push({ node, 0 });
            int maxLength = 0;

            while (!q.empty()) {
                int currentNode = q.front().first;
                int currentDepth = q.front().second;
                q.pop();

                if (localVisited[currentNode]) {
                    continue;
                }
                localVisited[currentNode] = true;
                maxLength = max(maxLength, currentDepth);

                // Just check the nodes that point to the current node.
                for (auto& pair : adjList) {
                    if (pair.second == currentNode && !localVisited[pair.first]) {
                        q.push({ pair.first, currentDepth + 1 });
                    }
                }
            }
            return maxLength;
        };

        visited.assign(adjList.size(), false);
        for (auto& pair : adjList) {
            if (!visited[pair.first]) {
                path.clear();
                pathSet.clear();
                dfs(pair.first);
                if (cycleNodes.first != -1 && cycleNodes.second != -1) {
                    maxChainLength += 2 + getLongestSubchainLength(cycleNodes.first) + getLongestSubchainLength(cycleNodes.second);
                    cycleNodes = { -1, -1 };
                }
            }
        }
        return max(maxCycleLength, maxChainLength);
    }
    //01.Nov.2023 2103 环和杆
    int countPoints(string rings) {
        int t[300] = { 0 };
        for (int i = 0; i < rings.size() / 2; i++)
        {
            int ring = rings[i * 2 + 1] - '0';
            switch (rings[i * 2])
            {
            case 'R':
                t[ring * 3] = 1;
                break;
            case 'G':
                t[ring * 3 + 1] = 1;
                break;
            case 'B':
                t[ring * 3 + 2] = 1;

                break;
            default:
                break;
            }

        }
        int sum = 0;
        for (int i = 0; i < 100; i++)
        {
            if (t[i * 3] + t[i * 3 + 1] + t[i * 3 + 2] == 3)
                sum++;
        }
        return sum;
    }
    //02.Nov.2023 117 填充每个节点的下一个右侧节点指针 II
    Node* connect(Node* root) {
        Node* now = root;
        Node* nl = NULL;
        Node* previous = NULL;
        while (now != NULL) {
            do {
                if (nl == NULL) {
                    nl = now->left != NULL ? now->left : now->right;
                }
                if (previous != NULL) {
                    previous->next = now->left != NULL ? now->left : now->right;
                }
                if (now->left != NULL && now->right != NULL) {
                    now->left->next = now->right;
                }
                if (now->left != NULL || now->right != NULL) {
                    previous = now->right != NULL ? now->right : now->left;
                }
                now = now->next;
            } while (now != NULL);
            now = nl;
            previous = NULL;
            nl = NULL;
        };
        return root;
    }
    //03.Nov.2023 421 数组中两个数的最大异或值
    int findMaximumXOR(vector<int>& nums) {
        int x = 0;
        for (int k = 30; k >= 0; --k) {
            unordered_set<int> seen;
            // 将所有的 pre^k(a_j) 放入哈希表中
            for (int num : nums) {
                // 如果只想保留从最高位开始到第 k 个二进制位为止的部分
                // 只需将其右移 k 位
                seen.insert(num >> k);
            }

            // 目前 x 包含从最高位开始到第 k+1 个二进制位为止的部分
            // 我们将 x 的第 k 个二进制位置为 1，即为 x = x*2+1
            int x_next = x * 2 + 1;
            bool found = false;

            // 枚举 i
            for (int num : nums) {
                if (seen.count(x_next ^ (num >> k))) {
                    found = true;
                    break;
                }
            }

            if (found) {
                x = x_next;
            }
            else {
                // 如果没有找到满足等式的 a_i 和 a_j，那么 x 的第 k 个二进制位只能为 0
                // 即为 x = x*2
                x = x_next - 1;
            }
        }
        return x;
    }
    //04.Nov.2023 187 重复的DNA序列
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> all;
        if (s.length() <= 10)return all;
        unordered_map<string, int> substringCount;

        for (int i = 0; i <= s.length() - 10; i++) {
            string sub = s.substr(i, 10); // 截取从位置i开始的10个字符
            substringCount[sub]++;

            // 只有在子串第二次出现时才将其加入到结果数组中
            if (substringCount[sub] == 2) {
                all.push_back(sub);
            }
        }
        return all;
    }
    //05.Nov.2023 318 最大单词长度乘积
    int maxProduct(vector<string>& words) {
        int maxProduct = 0;
        std::vector<int> masks(words.size(), 0);  // Bitmasks for each word
        // Preparing the bitmasks. Each bit in the mask represents whether
        // a character 'a' to 'z' is in the word.
        for (int i = 0; i < words.size(); i++) {
            for (char c : words[i]) {
                masks[i] |= 1 << (c - 'a');
            }
        }
        // Compare each pair of words
        for (int i = 0; i < words.size(); i++) {
            for (int j = i + 1; j < words.size(); j++) {
                if ((masks[i] & masks[j]) == 0) {  // No common letters
                    maxProduct = std::max(maxProduct, int(words[i].size() * words[j].size()));
                }
            }
        }
        return maxProduct;
    }
    //06.Nov.2023 2586 统计范围内的元音字符串数
    int vowelStrings(vector<string>& words, int left, int right) {
        int sum = 0;
        char vowels[5] = { 'a','e','i','o','u' };
        for (int i = left; i <= right; i++) {
            char a = words[i][0];
            char b = words[i][words[i].length()-1];
            int t = 0;
            for (int j = 0; j < 5; j++) {
                if (a == vowels[j])
                {
                    t++;
                    break;
                }
            }
            for (int j = 0; j < 5; j++) {
                if (b == vowels[j])
                {
                    t++;
                    break;
                }
            }
            if (t==2) {
                sum++;
            }
        }
        return sum;
    }
    //07.Nov.2023 2609 最长平衡子字符串
    int findTheLongestBalancedSubstring(string s) {

        int balance = 0;
        int maxLength = 0;
        int tempLength = 0;
        for (int i = 0; i < s.length(); i++)
        {
            balance = 0;
            tempLength = 0;
            string ss = s.substr(i);
            char last = ss[0];
            for (char c : ss) {
                if (c == '0' && last == '1')
                {
                    balance = 1;
                    tempLength = 1;
                    last = c;
                }
                else {
                    balance += (c == '0') ? 1 : -1;
                    if (balance == 0) {
                        tempLength += 1;
                        maxLength = std::max(maxLength, tempLength);
                        balance = 0;
                        tempLength = 0;
                    }
                    else if (balance < 0) {
                        balance = 0;
                        tempLength = 0;
                    }
                    else {
                        tempLength++;
                    }
                }
                last = c;
            }
        }
        return maxLength;
    }
    //08.Nov.2023 2258 逃离火灾
    int maximumMinutes(vector<vector<int>>& grid) {
        const int dirs[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        int m = grid.size(), n = grid[0].size();
        // 返回三个数，分别表示到达安全屋/安全屋左边/安全屋上边的最短时间
        auto bfs = [&](vector<pair<int, int>>& q) -> tuple<int, int, int> {
            vector<vector<int>> time(m, vector<int>(n, -1)); // -1 表示未访问
            for (auto& [i, j] : q) {
                time[i][j] = 0;
            }
            for (int t = 1; !q.empty(); t++) { // 每次循环向外扩展一圈
                vector<pair<int, int>> nq;
                for (auto& [i, j] : q) {
                    for (auto& [dx, dy] : dirs) { // 枚举上下左右四个方向
                        int x = i + dx, y = j + dy;
                        if (0 <= x && x < m && 0 <= y && y < n && grid[x][y] == 0 && time[x][y] < 0) {
                            time[x][y] = t;
                            nq.emplace_back(x, y);
                        }
                    }
                }
                q = move(nq);
            }
            return { time[m - 1][n - 1], time[m - 1][n - 2], time[m - 2][n - 1] };
        };

        vector<pair<int, int>> q = { {0, 0} };
        auto [man_to_house_time, m1, m2] = bfs(q);
        if (man_to_house_time < 0) { // 人无法到安全屋
            return -1;
        }

        vector<pair<int, int>> fire_pos;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fire_pos.emplace_back(i, j);
                }
            }
        }
        auto [fire_to_house_time, f1, f2] = bfs(fire_pos); // 多个着火点同时跑 BFS
        if (fire_to_house_time < 0) { // 火无法到安全屋
            return 1'000'000'000;
        }

        int d = fire_to_house_time - man_to_house_time;
        if (d < 0) { // 火比人先到安全屋
            return -1;
        }

        if (m1 != -1 && m1 + d < f1 || // 安全屋左边相邻格子，人比火先到
            m2 != -1 && m2 + d < f2) { // 安全屋上边相邻格子，人比火先到
            return d; // 图中第一种情况
        }
        return d - 1; // 图中第二种情况
    }
    //09.Nov.2023 2300 咒语和药水的成功对数
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        vector<int> res;
        for (auto& i : spells) {
            long long t = (success + i - 1) / i - 1;
            res.push_back(potions.size() - (upper_bound(potions.begin(), potions.end(), t) - potions.begin()));
        }
        return res;
    }
    //10.Nov.2023 765 情侣牵手
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        int tot = n / 2;

        vector<vector<int>> graph(tot);
        for (int i = 0; i < n; i += 2) {
            int l = row[i] / 2;
            int r = row[i + 1] / 2;
            if (l != r) {
                graph[l].push_back(r);
                graph[r].push_back(l);
            }
        }
        vector<int> visited(tot, 0);
        int ret = 0;
        for (int i = 0; i < tot; i++) {
            if (visited[i] == 0) {
                queue<int> q;
                visited[i] = 1;
                q.push(i);
                int cnt = 0;

                while (!q.empty()) {
                    int x = q.front();
                    q.pop();
                    cnt += 1;

                    for (int y : graph[x]) {
                        if (visited[y] == 0) {
                            visited[y] = 1;
                            q.push(y);
                        }
                    }
                }
                ret += cnt - 1;
            }
        }
        return ret;
    }
    void RangeModule() {};
    void addRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it != intervals.begin()) {
            auto start = prev(it);
            if (start->second >= right) {
                return;
            }
            if (start->second >= left) {
                left = start->first;
                intervals.erase(start);
            }
        }
        while (it != intervals.end() && it->first <= right) {
            right = max(right, it->second);
            it = intervals.erase(it);
        }
        intervals[left] = right;
    }
    bool queryRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it == intervals.begin()) {
            return false;
        }
        it = prev(it);
        return right <= it->second;
    }
    void removeRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it != intervals.begin()) {
            auto start = prev(it);
            if (start->second >= right) {
                int ri = start->second;
                if (start->first == left) {
                    intervals.erase(start);
                }
                else {
                    start->second = left;
                }
                if (right != ri) {
                    intervals[right] = ri;
                }
                return;
            }
            else if (start->second > left) {
                if (start->first == left) {
                    intervals.erase(start);
                }
                else {
                    start->second = left;
                }
            }
        }
        while (it != intervals.end() && it->first < right) {
            if (it->second <= right) {
                it = intervals.erase(it);
            }
            else {
                intervals[right] = it->second;
                intervals.erase(it);
                break;
            }
        }
    }
    /*
    NumArray(vector<int>& nums) : nums(nums) {
        int n = nums.size();
        size = sqrt(n);
        sum.resize((n + size - 1) / size); // n/size 向上取整
        for (int i = 0; i < n; i++) {
            sum[i / size] += nums[i];
        }
    }
    */
    void update(int index, int val) {
        sum[index / size] += val - nums[index];
        nums[index] = val;
    }

    int sumRange(int left, int right) {
        int b1 = left / size, i1 = left % size, b2 = right / size, i2 = right % size;
        if (b1 == b2) { // 区间 [left, right] 在同一块中
            return accumulate(nums.begin() + b1 * size + i1, nums.begin() + b1 * size + i2 + 1, 0);
        }
        int sum1 = accumulate(nums.begin() + b1 * size + i1, nums.begin() + b1 * size + size, 0);
        int sum2 = accumulate(nums.begin() + b2 * size, nums.begin() + b2 * size + i2 + 1, 0);
        int sum3 = accumulate(sum.begin() + b1 + 1, sum.begin() + b2, 0);
        return sum1 + sum2 + sum3;
    }
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        pair<int, int> ans(INT_MAX / 2, -1);
        vector<vector<int>> mp(n, vector<int>(n, INT_MAX / 2));
        for (auto& eg : edges) {
            int from = eg[0], to = eg[1], weight = eg[2];
            mp[from][to] = mp[to][from] = weight;
        }
        for (int k = 0; k < n; ++k) {
            mp[k][k] = 0;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if (mp[i][j] <= distanceThreshold) {
                    cnt++;
                }
            }
            if (cnt <= ans.first) {
                ans = { cnt, i };
            }
        };
        return ans.second;
    }
    int maximizeSum(vector<int>& nums, int k) {
        auto max_it = std::max_element(nums.begin(), nums.end());
        return ((*max_it + *max_it + k - 1) * k / 2);
    }
};
int main()
{
    Solution solution;
    vector<string> words = { "hey","aeo","mu","ooo","artro" };
    cout<<solution.findTheLongestBalancedSubstring("001011");
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
