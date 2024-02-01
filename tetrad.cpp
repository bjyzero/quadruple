//前缀 min 指 min(a_1, a_2, ... ,a_i)=min(min(a_1, a_2, ...,a{i-1}), a_i)

//先考虑二元组，即是否存在 a < b,使得 nums[a] < nums[b]
//预处理前缀 min,枚举 b，我们知道 b 之前的最小的 nums 是多少

//再考虑三元组，即是否存在 a < b < c,使得 nums[a] < nums[b] < nums[c]
//两种思路，第一种思路，预处理前缀 min 和后缀 max，仍然枚举 b   ----> 不在二元组基础上做
//第二种思路，延续二元组已经做好的问题---->此时我们已经知道哪些 b 会存在 a < b 且 nums[a] < nums[b],我们称之为合法的 b
//如果枚举 c ，对于那些合法的 b，维护前缀 min,此时我们知道 c 之前最小的 nums[b] 满足存在 a < b 且 nums[a] < nums[b] 是多少

//最后考虑四元组，即是否存在 a < b < c < d,使得nums[a] < nums[b] <nums[c] < nums[d]
//利用三元组的信息，对于那些合法的 c,维护前缀 min,枚举 d
//总结：每次去找上一个合法的数值中最小的那一个


//回到原问题
//是否存在 a < b < c < d，使得 nums[d] < nums[c] < nums[a] < nums[b]
//分别维护二元组 (a,b) 和 (c,d), 对合法 a 维护前缀 max 的 nums[a],枚举 c ,则需要知道 c 之前存在 a 满足 nums[a] > nums[c]
//所以要对 "每个" b 找到最大的 nums[a] 使得 a < b 且 nums[a] < nums[b]

#include <bits/stdc++.h>
using namespace std;

#define inf 1'000'000'000

void solve(const int &Case)
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &x : arr)
        cin >> x;

    vector<int> pre(n, -inf - 1), suf(n);   //这个值是因为 -10^9 < nums[i] < 10^9
    int mn = inf + 1;
    set<int> s;                             //维护前缀的 nums[a] 的值

    for (int i = 0; i < n; ++i)
    {
        auto it = s.lower_bound(arr[i]);    //找大于等于 nums[b] 的 nums[a] 中的最小值
        if (it == s.begin());               //意味着前面所有的 a 都大于当前的 b,则 b 不可能合法
        else
        {
            it = prev(it);  //获得小于 nums[b] 的nums[a] 中的最大值 (prev 就是 -1 的意思)
            int p = *it;    //获得 nums[a] 的值
            pre[i] = p;     //pre[i] 记录的是合法 b 的值的 nums[a] 的前缀 max -----> "每个"合法 b
        }
        s.insert(arr[i]);    // s 的作用----> 将 b 位置之前的 nums[a] 都插入进去并且排好顺序
    }

    for (int i = n - 1; i >= 0; --i)    // c 和 d 的下标最大，从 i = n - 1 开始
    {
        if (arr[i] > mn)    // nums[c] > nums[d], d > c,  mn = inf + 1
        {                   // 这里 mn --> d, arr[i] --> c
            suf[i] = 1;     // suf[i] 表示 c = i 时是否存在合法的 d 满足
        }
        mn = min(mn, arr[i]);    // nums[d] 取满足条件的最小值
    }

    //该问题的复杂在于 nums[a] > nums[c]
    for (int i = 1; i < n - 1; ++i)     // 枚举 c = i + 1
    {
        if (pre[i] > arr[i + 1] && suf[i + 1])
        {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(void)
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    solve(t);
    return 0;
}

//前后缀结构处理  ---->  总思路梳理
//是否存在 a < b < c < d，使得 nums[d] < nums[c] < nums[a] < nums[b]
//考虑分别维护二元组信息 (a,b) 和 (c,d)，即对于每个 b,求出是否存在合法的 a 满足 a < b 且 nums[a] < nums[b]
//同理对 (c,d) 求出类似的
//这些信息只需要求出前缀最小值和后缀最小值即可

//但条件还有 nums[c] < nums[a],所以我们需要对每个前缀获得最大的nums[a]
//即，对于每个 i ，对 nums[1], nums[2],..., nums[i] 求出最大的 nums[a],满足 a < b < i, nums[a] < nums[b]
//得到这个信息后，只需要枚举 c = i,即可判断是否存在 (a,b,c,d) 四元组了
//而得到这个信息需要在求出 (a,b) 的情况下再求出 nums[a] 的前缀最大值
//时间复杂度 O(n)