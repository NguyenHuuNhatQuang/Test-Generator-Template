#include<bits/stdc++.h>
using namespace std;

long long Rnd() // tra ve mot so ngau nhien
{
    long long ans = 0;
    for(int i = 0; i < 8; i ++) ans ^= ((long long)(rand() % 255) << (8 * i));
    return ans;
}

long long Rand(long long l, long long h)
{ // tra ve so random trong khoang tu l den r
    assert (h >= l);
    return abs(Rnd()) % (h - l + 1) + l;
}
bool bit01() { // tra ve 0 hoac 1
    return rand () %2;
}
char az() { // tra ve ki tu ngau nhien tong ['a' .. 'z']
    return (char)(Rand('a', 'z'));
}
char AZ() { // tra ve ki tu ngau nhien tong ['A' .. 'Z']
    return (char)(Rand('A', 'Z'));
}
char num() { // tra ve ['0' .. '9']
    return '0' + Rand(0, 9);
}
void ShuffleArray(vector<long long> &arr, int n) { // hoan vi n phan tu dau tien cua mot vector arr
    assert (n <= int (arr.size ()));

    int minPosition;
    int maxPosition = n - 1;
    int swapPosition;
    int i = 0;
    while (i < n - 1) {
        minPosition = i + 1;
        swapPosition = Rand(1, 1e7) % (maxPosition - minPosition + 1) + minPosition;
        swap(arr[i], arr[swapPosition]);
        ++i;
    }
}

string bignum(long long l) // sinh mot so lon gom l chu so
{
    assert (l > 0);

    string s = " ";
    s[0] = char (Rand (1, 9) + '0');
    for(int i = 1; i <= l; i ++)
    {
        s += " ";
        s[s.size() - 1] = num();
    }
    return s;
}

vector <pair <int, int>> tree (int ver, int d) // tra ve cac canh cua mot cay co do sau lon
{
    assert (ver > 0 && d >= 0);
    if (d == 0) d = ver;

    vector<pair<int, int> > ans;
    for(int i = 2; i <= ver; i ++)
        ans.push_back(make_pair(i, Rand(max (1, i - d), i - 1)));

    for(int i = 1; i < ver - 1; i ++) swap(ans[i], ans[Rand(0, i)]);

    int secret = 0;
    while(__gcd(secret, ver) != 1) secret = Rand(1, ver);
    for(int i = 0; i < ver - 1; i ++)
    {
        ans[i].first = 1LL * ans[i].first * secret % ver;
        if(ans[i].first == 0) ans[i].first = ver;
        ans[i].second = 1LL * ans[i].second * secret % ver;
        if(ans[i].second == 0) ans[i].second = ver;
    }

    return ans;
}

vector<pair<int, int> > graph(int ver, int edge) // tra ve cac canh cua mot do thi ngau nhien
{
    assert (ver > 0 && edge > 0);

    unordered_map<long long, bool> used;
    used[0] = true;

    vector<pair<int, int> > ans;
    for(int i = 1; i <= edge; i ++)
    {
        int a = 0, b = 0;
        while(a <= b or used[1LL * a * ver + b])
        {
            a = Rand(1, ver);
            b = Rand(1, ver);
        }
        used[1LL * a * ver + b] = true;
        if(Rand(0, 1)) swap(a, b);
        ans.push_back(make_pair(a, b));
    }

    int secret = 0;
    while(__gcd(secret, ver) != 1) secret = Rand(1, ver);
    for(int i = 0; i < edge; i ++)
    {
        ans[i].first = 1LL * ans[i].first * secret % ver;
        if(ans[i].first == 0) ans[i].first = ver;
        ans[i].second = 1LL * ans[i].second * secret % ver;
        if(ans[i].second == 0) ans[i].second = ver;
    }

    return ans;
}

vector<pair<int, int>> connected_graph (int ver, int edge) // tra ve cac canh cua mot do thi lien thong
{
    assert (ver > 0 && edge >= ver - 1 && edge <= ver * (ver - 1) / 2);

    unordered_map<long long, bool> used;
    used[0] = true;

    vector<pair<int, int>> ans = tree (ver, 0);

    for (auto i: ans)
    {
        if (i.first < i.second) swap (i.first, i.second);
        used[1LL * i.first * ver + i.second] = true;
    }

    for(int i = ver; i <= edge; i ++)
    {
        int a = 0, b = 0;
        while(a <= b or used[1LL * a * ver + b])
        {
            a = Rand(1, ver);
            b = Rand(1, ver);
        }
        used[1LL * a * ver + b] = true;
        if(Rand(0, 1)) swap(a, b);
        ans.push_back(make_pair(a, b));
    }

    for(int i = 0; i < edge; i ++) swap(ans[i], ans[Rand(0, i)]);

    int secret = 0;
    while(__gcd(secret, ver) != 1) secret = Rand(1, ver);
    for(int i = 0; i < edge; i ++)
    {
        ans[i].first = 1LL * ans[i].first * secret % ver;
        if(ans[i].first == 0) ans[i].first = ver;
        ans[i].second = 1LL * ans[i].second * secret % ver;
        if(ans[i].second == 0) ans[i].second = ver;
    }

    return ans;
}

long long log_rand(long long t) // sinh mot so ngau nhien tu 1 den t
{
    assert (t > 0);

    int x = 64 - __builtin_clzll(t);
    return Rand(1, min(t, (1LL << Rand(1, x))));
}

string bracket (int n, int d) // tra ve mot day ngoac dung
{
    assert (n > 0 and d >= 0);

    vector <pair <int, int>> edges = tree (n, d);
    vector <int> adj[n + 1], st;
    string ans;

    for (auto i: edges)
    {
        adj[i.first].push_back (i.second);
        adj[i.second].push_back (i.first);
    }

    st.push_back (0);
    st.push_back (1);

    while (int (st.size ()) > 1)
    {
        int t = st.back ();
        if (adj[t].size ())
        {
            if (adj[t].back () != st[st.size () - 2])
            {
                ans += '(';
                st.push_back (adj[t].back ());
            }
            adj[t].pop_back ();
        }
        else
        {
            ans += ')';
            st.pop_back ();
        }
    }

    return ans;
}
