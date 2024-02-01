//ǰ׺ min ָ min(a_1, a_2, ... ,a_i)=min(min(a_1, a_2, ...,a{i-1}), a_i)

//�ȿ��Ƕ�Ԫ�飬���Ƿ���� a < b,ʹ�� nums[a] < nums[b]
//Ԥ����ǰ׺ min,ö�� b������֪�� b ֮ǰ����С�� nums �Ƕ���

//�ٿ�����Ԫ�飬���Ƿ���� a < b < c,ʹ�� nums[a] < nums[b] < nums[c]
//����˼·����һ��˼·��Ԥ����ǰ׺ min �ͺ�׺ max����Ȼö�� b   ----> ���ڶ�Ԫ���������
//�ڶ���˼·��������Ԫ���Ѿ����õ�����---->��ʱ�����Ѿ�֪����Щ b ����� a < b �� nums[a] < nums[b],���ǳ�֮Ϊ�Ϸ��� b
//���ö�� c ��������Щ�Ϸ��� b��ά��ǰ׺ min,��ʱ����֪�� c ֮ǰ��С�� nums[b] ������� a < b �� nums[a] < nums[b] �Ƕ���

//�������Ԫ�飬���Ƿ���� a < b < c < d,ʹ��nums[a] < nums[b] <nums[c] < nums[d]
//������Ԫ�����Ϣ��������Щ�Ϸ��� c,ά��ǰ׺ min,ö�� d
//�ܽ᣺ÿ��ȥ����һ���Ϸ�����ֵ����С����һ��


//�ص�ԭ����
//�Ƿ���� a < b < c < d��ʹ�� nums[d] < nums[c] < nums[a] < nums[b]
//�ֱ�ά����Ԫ�� (a,b) �� (c,d), �ԺϷ� a ά��ǰ׺ max �� nums[a],ö�� c ,����Ҫ֪�� c ֮ǰ���� a ���� nums[a] > nums[c]
//����Ҫ�� "ÿ��" b �ҵ����� nums[a] ʹ�� a < b �� nums[a] < nums[b]

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

    vector<int> pre(n, -inf - 1), suf(n);   //���ֵ����Ϊ -10^9 < nums[i] < 10^9
    int mn = inf + 1;
    set<int> s;                             //ά��ǰ׺�� nums[a] ��ֵ

    for (int i = 0; i < n; ++i)
    {
        auto it = s.lower_bound(arr[i]);    //�Ҵ��ڵ��� nums[b] �� nums[a] �е���Сֵ
        if (it == s.begin());               //��ζ��ǰ�����е� a �����ڵ�ǰ�� b,�� b �����ܺϷ�
        else
        {
            it = prev(it);  //���С�� nums[b] ��nums[a] �е����ֵ (prev ���� -1 ����˼)
            int p = *it;    //��� nums[a] ��ֵ
            pre[i] = p;     //pre[i] ��¼���ǺϷ� b ��ֵ�� nums[a] ��ǰ׺ max -----> "ÿ��"�Ϸ� b
        }
        s.insert(arr[i]);    // s ������----> �� b λ��֮ǰ�� nums[a] �������ȥ�����ź�˳��
    }

    for (int i = n - 1; i >= 0; --i)    // c �� d ���±���󣬴� i = n - 1 ��ʼ
    {
        if (arr[i] > mn)    // nums[c] > nums[d], d > c,  mn = inf + 1
        {                   // ���� mn --> d, arr[i] --> c
            suf[i] = 1;     // suf[i] ��ʾ c = i ʱ�Ƿ���ںϷ��� d ����
        }
        mn = min(mn, arr[i]);    // nums[d] ȡ������������Сֵ
    }

    //������ĸ������� nums[a] > nums[c]
    for (int i = 1; i < n - 1; ++i)     // ö�� c = i + 1
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

//ǰ��׺�ṹ����  ---->  ��˼·����
//�Ƿ���� a < b < c < d��ʹ�� nums[d] < nums[c] < nums[a] < nums[b]
//���Ƿֱ�ά����Ԫ����Ϣ (a,b) �� (c,d)��������ÿ�� b,����Ƿ���ںϷ��� a ���� a < b �� nums[a] < nums[b]
//ͬ��� (c,d) ������Ƶ�
//��Щ��Ϣֻ��Ҫ���ǰ׺��Сֵ�ͺ�׺��Сֵ����

//���������� nums[c] < nums[a],����������Ҫ��ÿ��ǰ׺�������nums[a]
//��������ÿ�� i ���� nums[1], nums[2],..., nums[i] ������� nums[a],���� a < b < i, nums[a] < nums[b]
//�õ������Ϣ��ֻ��Ҫö�� c = i,�����ж��Ƿ���� (a,b,c,d) ��Ԫ����
//���õ������Ϣ��Ҫ����� (a,b) ������������ nums[a] ��ǰ׺���ֵ
//ʱ�临�Ӷ� O(n)