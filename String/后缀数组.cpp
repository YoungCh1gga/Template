#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, mx, mn;
int a[N];
char s[N];
int SA[N], rnk[N], height[N], sum[N], tp[N];
//rnk[i] ��i����׺������, SA[i] ����Ϊi�ĺ�׺��λ��, Height[i] ����Ϊi�ĺ�׺������Ϊ(i-1)�ĺ�׺��LCP
//sum[i] ��������������, �洢С��i��Ԫ���ж��ٸ�, tp[i] rnk�ĸ�������(���ڶ��ؼ�������Ľ��),��SA����һ��

bool cmp(int *f, int x, int y, int w)
{
    return f[x] == f[y] && f[x + w] == f[y + w];
}

void get_SA(char *s, int n, int m)
{
    //��Ԥ������Ϊ1�����
    for (int i = 0; i < m; i++)
        sum[i] = 0; //��0
    for (int i = 0; i < n; i++)
        sum[rnk[i] = s[i]]++; //ͳ��ÿ���ַ����ֵĴ���
    for (int i = 1; i < m; i++)
        sum[i] += sum[i - 1]; //sum[i]ΪС�ڵ���i��Ԫ�ص���Ŀ
    for (int i = n - 1; i >= 0; i--)
        SA[--sum[rnk[i]]] = i; //�±��0��ʼ,�������Լ�
    //SA[i]�洢������i�ĺ�׺�±�,SA[--sum[rnk[i]]] = i ���±�Ϊi�ĺ�׺����Ϊ--sum[rnk[i]],�����Ȼ
    for (int len = 1; len <= n; len <<= 1)
    {
        int p = 0;
        //ֱ����SA����Եڶ��ؼ�������
        for (int i = n - len; i < n; i++)
            tp[p++] = i; //����i����û�еڶ��ؼ���,���ڶ��ؼ���Ϊ��,������С
        for (int i = 0; i < n; i++)
        {
            if (SA[i] >= len)
                tp[p++] = SA[i] - len;
        }
        //tp[i]�洢���ڶ��ؼ��������i���±�
        //�Եڶ��ؼ�������Ľ���ٰ���һ�ؼ�������,�ͳ���Ϊ1���������
        for (int i = 0; i < m; i++)
            sum[i] = 0;
        for (int i = 0; i < n; i++)
            sum[rnk[tp[i]]]++;
        for (int i = 1; i < m; i++)
            sum[i] += sum[i - 1];
        for (int i = n - 1; i >= 0; i--)
            SA[--sum[rnk[tp[i]]]] = tp[i];
        //����SA��rnk�������¼���rnk����
        swap(rnk, tp); //������tpָ��ɵ�rnk����
        p = 1;
        rnk[SA[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            rnk[SA[i]] = cmp(tp, SA[i - 1], SA[i], len) ? p - 1 : p++; //ע���ж�rnk[i]��rnk[i-1]�Ƿ����
        }
        if (p >= n)
            break;
        m = p; //�´λ�����������ֵ
    }
    //��height
    int k = 0;
    n--;
    for (int i = 0; i <= n; i++)
        rnk[SA[i]] = i;
    for (int i = 0; i < n; i++)
    {
        if (k)
            k--;
        int j = SA[rnk[i] - 1];
        while (s[i + k] == s[j + k])
            k++;
        height[rnk[i]] = k;
    }
}

void check()
{
    // getchar();//����û��ʲô��
    scanf("%s", s);
    int n = strlen(s);
    get_SA(s, n + 1, 'z' + 1);
    ll res = 0;
    for (int i = 1; i <= n; ++i)
        res += n - SA[i] - height[i];
    printf("%lld\n", res);
}
//�����ַ����������ͬ�Ӵ�������

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
        check();
}
