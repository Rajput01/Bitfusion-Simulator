#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define rep(i, a, b) for (int i = a; i < b; i++)
#define fr(a, b) for (int i = a; i < b; i++)

int binaryproduct(int binary1, int binary2)

{

    int i = 0, remainder = 0, sum[20];

    int binaryprod = 0;

    while (binary1 != 0 || binary2 != 0)

    {

        sum[i++] = (binary1 % 10 + binary2 % 10 + remainder) % 2;

        remainder = (binary1 % 10 + binary2 % 10 + remainder) / 2;

        binary1 = binary1 / 10;

        binary2 = binary2 / 10;
    }

    if (remainder != 0)

        sum[i++] = remainder;

    --i;

    while (i >= 0)

        binaryprod = binaryprod * 10 + sum[i--];

    return binaryprod;
}

long long int traditional(long long int binary1, long long int binary2)
{
    long long int multiply = 0;

    int digit, factor = 1;

    while (binary2 != 0)

    {

        digit = binary2 % 10;

        if (digit == 1)

        {

            binary1 = binary1 * factor;

            multiply = binaryproduct(binary1, multiply);
        }

        else

            binary1 = binary1 * factor;

        binary2 = binary2 / 10;

        factor = 10;
    }
    return multiply;
}

pair<int, int> Full_Adder(int A, int B, int C_In)
{
    int Sum, C_Out;
    // Calculating value of sum
    Sum = C_In ^ (A ^ B);

    // Calculating value of C-Out
    C_Out = (A & B) | (B & C_In) | (A & C_In);

    // printing the values
    // cout<<"Sum = "<< Sum <<endl;
    // cout<<"C-Out = "<< C_Out <<endl;
    return {Sum, C_Out};
}

pair<int, int> Half_Adder(int A, int B)
{
    // initialize the variables Sum and Carry
    int Sum, Carry;

    // Calculating value of sum by applying A XOR B
    Sum = A ^ B;

    // Calculating value of Carry by applying A AND B
    Carry = A & B;

    // printing the values
    // cout<<"Sum = "<< Sum << endl;
    // cout<<"Carry = "<<Carry<< endl;
    return {Sum, Carry};
}
vector<int> bitbrick(int x[], int y[])
{

    x[0] = x[0] & x[1];
    y[0] = y[0] & y[1];
    // p0
    int x2 = x[0], x1 = x[1], x0 = x[2];
    int y2 = y[0], y1 = y[1], y0 = y[2];

    int p0 = x0 & y0;

    int x1_y0 = x1 & y0;
    int x0_y1 = x0 & y1;
    auto ha1 = Half_Adder(x1_y0, x0_y1);

    // p1
    int p1 = ha1.first;

    int x1_y1 = (x1 & y1);
    int x0_y2 = (x0 & y2) ? 0 : 1;
    auto fa1 = Full_Adder(x1_y1, x0_y2, ha1.second);

    int x2_y0 = (x2 & y0) ? 0 : 1;

    auto ha2 = Half_Adder(x2_y0, fa1.first);

    // p2
    int p2 = ha2.first;

    int x2_y1 = (x2 & y1) ? 0 : 1;
    int x1_y2 = (x1 & y2) ? 0 : 1;

    auto fa2 = Full_Adder(x2_y1, x1_y2, fa1.second);

    auto ha3 = Half_Adder(fa2.first, ha2.second);

    // p3
    int p3 = ha3.first;

    int x2_y2 = (x2 & y2);
    auto fa3 = Full_Adder(x2_y2, fa2.second, ha3.second);

    // p4
    int p4 = fa3.first;

    // p5
    int p5 = fa3.second;

    vector<int> p(6);
    p[0] = p5;
    p[1] = p4;
    p[2] = p3;
    p[3] = p2;
    p[4] = p1;
    p[5] = p0;

    return p;
}

vector<int> shift(vector<int> v, int k)
{

    vector<int> res(k + v.size(), 0);

    for (int i = 0; i < v.size(); i++)
    {
        res[i] = v[i];
    }

    return res;
}
vector<int> add(vector<int> v1, vector<int> v2)
{
    string A = "", B = "";

    for (int i = 0; i < v1.size(); i++)
    {
        A += (v1[i] + '0');
    }

    for (int i = 0; i < v2.size(); i++)
    {
        B += (v2[i] + '0');
    }

    if (A.length() > B.length())
    {
        return add(v2, v1);
    }

    int diff = B.length() - A.length();

    string padding;

    for (int i = 0; i < diff; i++)
    {
        padding.push_back('0');
    }

    A = padding + A;
    string res;
    char carry = '0';

    for (int i = A.length() - 1; i >= 0; i--)
    {

        if (A[i] == '1' && B[i] == '1')
        {
            if (carry == '1')
            {
                res.push_back('1');
                carry = '1';
            }
            else
            {
                res.push_back('0');
                carry = '1';
            }
        }

        else if (A[i] == '0' && B[i] == '0')
        {
            if (carry == '1')
            {
                res.push_back('1');
                carry = '0';
            }
            else
            {
                res.push_back('0');
                carry = '0';
            }
        }

        else if (A[i] != B[i])
        {
            if (carry == '1')
            {
                res.push_back('0');
                carry = '1';
            }
            else
            {
                res.push_back('1');
                carry = '0';
            }
        }
    }

    if (carry == '1')
    {
        res.push_back(carry);
    }

    reverse(res.begin(), res.end());

    int index = 0;

    while (index + 1 < res.length() && res[index] == '0')
    {
        index++;
    }

    vector<int> ans;

    for (int i = index; i < res.size(); i++)
    {

        ans.push_back(res[i] - '0');
    }

    return ans;
}

vector<int> decomposing4_bit_cross_4bit_to_2_bit_cross_2_bit(int a[], int b[])
{

    int x1[3] = {0, a[0], a[1]};
    int y1[3] = {0, b[0], b[1]};
    int y2[3] = {0, b[2], b[3]};
    int x2[3] = {0, a[2], a[3]};

    vector<int> bb1 = bitbrick(x1, y2);
    vector<int> bb2 = bitbrick(x2, y2);
    vector<int> bb3 = bitbrick(x1, y1);
    vector<int> bb4 = bitbrick(x2, y1);

    // discarding 3bits because of sign issues

    vector<int> res1(3), res2(3), res3(3), res4(3);

    for (int i = 3; i < 6; i++)
    {
        res1[i - 3] = bb1[i];
        res2[i - 3] = bb2[i];
        res3[i - 3] = bb3[i];
        res4[i - 3] = bb4[i];
    }

    vector<int> op1 = shift(res1, 2);
    vector<int> op2 = shift(res2, 0);
    vector<int> op3 = shift(res3, 4);
    vector<int> op4 = shift(res4, 2);

    vector<int> res;

    res = add(op1, op2);
    res = add(res, op3);
    res = add(res, op4);

    return res;
}

// Temporal design
vector<int> temporal_design(int a[], int b[], int left_shift, vector<int> existing_output)
{

    vector<int> op1 = bitbrick(a, b);

    op1 = shift(op1, left_shift);

    return add(op1, existing_output);
}
vector<int> multiply_8_2_bit(vector<int> ip1, vector<int> ip2)
{

    int v1[3] = {0, ip1[0], ip1[1]};
    int v2[3] = {0, ip1[2], ip1[3]};
    int v3[3] = {0, ip1[4], ip1[5]};
    int v4[3] = {0, ip1[6], ip1[7]};

    int v5[3] = {0, ip2[0], ip2[1]};

    vector<int> bb1 = bitbrick(v1, v5);
    vector<int> bb2 = bitbrick(v2, v5);
    vector<int> bb3 = bitbrick(v3, v5);
    vector<int> bb4 = bitbrick(v4, v5);

    // discarding 3bits because of sign issues

    vector<int> res1(3), res2(3), res3(3), res4(3);

    for (int i = 3; i < 6; i++)
    {
        res1[i - 3] = bb1[i];
        res2[i - 3] = bb2[i];
        res3[i - 3] = bb3[i];
        res4[i - 3] = bb4[i];
    }

    vector<int> op1 = shift(res1, 6);
    vector<int> op2 = shift(res2, 4);
    vector<int> op3 = shift(res3, 2);
    vector<int> op4 = shift(res4, 0);

    vector<int> res;

    res = add(op1, op2);
    res = add(res, op3);
    res = add(res, op4);

    return res;
}

void traditionalmultiplier()
{
    cout << "Enter the 1st input" << endl;
    string s1, s2;
    cin >> s1;
    cout << "Enter the 2nd input" << endl;
    cin >> s2;
    int m = s1.length();
    int n = s2.length();

    int k = 0;
    // char x;
    int q;
    for (int i = n - 1; i >= 0; i--)
    {
        q = s1[i] - 48;
        k = k + pow(2, n - 1 - (i)) * q;
    }
    int l = 0;
    for (int i = m - 1; i >= 0; i--)
    {
        q = s2[i] - 48;
        l = l + pow(2, m - 1 - (i)) * q;
    }
    cout << l * k << endl;
}

// Figure 4
// ibuf 1st dimension = N , second dimension = 4, 3rd dimesion = 8 (for 8 bit number)
// wbuf 1st dimension = M , second dimension = N, 3rd dimesion = 4 , 4th dimension = 2 (for 2 bit number)

vector<vector<vector<vector<int>>>> bit_fusion_execution_model2(vector<vector<vector<int>>> ibuf, vector<vector<vector<vector<int>>>> wbuf)
{

    int N = ibuf.size();
    int M = wbuf.size();

    vector<vector<vector<vector<int>>>> obuf(M, vector<vector<vector<int>>>(N, vector<vector<int>>(4)));

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < 4; k++)
            {

                obuf[i][j][k] = multiply_8_2_bit(ibuf[j][k], wbuf[i][j][k]);
            }
        }
    }
    return obuf;
}

vector<vector<vector<long long int>>> bit_fusion_execution_model1(vector<vector<long long int>> ibuf, vector<vector<vector<long long int>>> wbuf)
{

    int N = ibuf.size();
    int M = wbuf.size();

    vector<vector<vector<long long int>>> obuf(M, vector<vector<long long int>>(N, vector<long long int>(4)));

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < 4; k++)
            {

                obuf[i][j][k] = traditional(ibuf[j][k], wbuf[i][j][k]);
            }
        }
    }
    return obuf;
}

vector<vector<vector<int>>> convolution_with_1_color_1_filter(vector<vector<vector<int>>> &ibuf, vector<vector<vector<int>>> &wbuf)
{

    //  vector<vector<vector<vector<int>>>> (3,filter);

    // vector<vector<vector<vector<int>>>> obuf = bit_fusion_execution_model2(ibuf , wbuf);

    int start_row = 0;
    int end_row = wbuf.size() - 1;

    int N = ibuf.size();
    int M = ibuf[0].size();
    int mx = 0;
    vector<vector<vector<int>>> ans;
    while (end_row < N)
    {
        int start_col = 0;
        int end_col = wbuf[0].size() - 1;
        vector<vector<int>> out;
        while (end_col < M)
        {
            int p, q;
            p = 0;
            vector<int> res;
            for (int i = start_row; i <= end_row; i++)
            {
                q = 0;
                for (int j = start_col; j <= end_col; j++)
                {
                    // multiplication here
                    vector<int> temp = multiply_8_2_bit(ibuf[i][j], wbuf[p][q]);
                    res = add(res, temp);
                    q++;
                }
                p++;
            }
            mx = max(mx, (int)res.size()); // finding largest bitwidht size
            out.push_back(res);
            start_col += 1;
            end_col += 1;
        }
        ans.push_back(out);
        start_row += 1;
        end_row += 1;
    }

    int n = ans.size();
    int m = ans[0].size();
    // for(auto i : ans)
    // {
    //     for(auto j : i)
    //     {
    //         // cout<<j;
    //         int check = mx - j.size();
    //         for(int i=0;i<check;i++)
    //         cout<<0;
    //         for(auto a : j)
    //         {
    //             cout<<a;
    //         }
    //         cout<<" ";
    //     }
    //     cout<<endl;
    // }
    return ans;
}
vector<vector<vector<int>>> pooling(vector<vector<vector<int>>> ibuf)
{
    // Filter size 2x2
    int start_row = 0;
    int end_row = 1;

    int N = ibuf.size();
    int M = ibuf[0].size();
    int mx_size = 0;
    vector<vector<vector<int>>> ans;
    while (end_row < N)
    {
        int start_col = 0;
        int end_col = 1;
        vector<vector<int>> out;
        while (end_col < M)
        {
            int p, q;
            p = 0;
            vector<int> res;
            int mx = 0;
            for (int i = start_row; i <= end_row; i++)
            {
                q = 0;
                for (int j = start_col; j <= end_col; j++)
                {
                    // Find Max of selected feature map here
                    vector<int> curr = ibuf[i][j];
                    int sz = curr.size();
                    int val = 0;
                    for (int k = sz - 1; k >= 0; k--)
                    {
                        val = val + curr[k] * pow(2, sz - 1 - k);
                    }
                    if (mx < val)
                    {
                        mx = val;
                        res = curr;
                    }
                    q++;
                }
                p++;
            }
            mx = max(mx, (int)res.size()); // finding largest bitwidht size
            out.push_back(res);
            start_col += 2; // stride of 2
            end_col += 2;   // stride of 2
        }
        ans.push_back(out);
        start_row += 2;
        end_row += 2;
    }
    for (auto i : ans)
    {
        for (auto j : i)
        {
            mx_size = max(mx_size, (int)j.size());
        }
    }
    int n = ans.size();
    int m = ans[0].size();
    cout << "\nPOOLED FEATURE MAP\n"
         << endl;
    for (auto i : ans)
    {
        for (auto j : i)
        {
            // cout<<j;
            int check = mx_size - j.size();
            for (int i = 0; i < check; i++)
                cout << 0;
            for (auto a : j)
            {
                cout << a;
            }
            cout << " ";
        }
        cout << endl;
    }
    return ans;
}
vector<vector<int>> flattening(vector<vector<vector<int>>> ibuf)
{
    vector<vector<int>> ans;
    int mx_size = 0;
    for (auto i : ibuf)
    {
        for (auto j : i)
        {
            mx_size = max(mx_size, (int)j.size());
        }
    }
    for (auto i : ibuf)
    {
        for (auto j : i)
        {
            vector<int> curr;
            int check = mx_size - j.size();
            for (int i = 0; i < check; i++)
                curr.push_back(0);
            for (auto a : j)
            {
                curr.push_back(a);
                // cout<<a;
            }
            // cout<<" ";
            ans.push_back(curr);
        }
    }

    cout<<"\nFLATTENED OUTPUT IS\n"<<endl;
    for(auto i : ans)
    {
        for(auto j : i)
        cout<<j;
        cout<<endl;
    }
    return ans;

}
int main()
{

    cout << "\t\t\t--------- BTP -----------\t\t\t\n";
    while (1)
    {
        cout << endl;
        cout << "Enter the key for desired fucntion" << endl;
        cout << "1. Traditional Multiplication" << endl;
        cout << "2. 8 bit * 2bit" << endl;
        cout << "3. bit_fusion_execution_model" << endl;
        cout << "4. 4bit*4bit" << endl;
        cout << "5. Traditional Model Execution" << endl;
        cout << "6. For Convolutional Operation" << endl;
        cout << "7. Exit" << endl;
        cout << endl;
        int x;
        cin >> x;
        if (x == 1)
        {
            time_t start1, end1;

            time(&start1);
            ios_base::sync_with_stdio(false);
            traditionalmultiplier();
            cout << endl;
            time(&end1);

            // Calculating total time taken by the program.
            double time_taken = double(end1 - start1);
            cout << "Time taken by program is : " << fixed
                 << time_taken << setprecision(5);
            cout << " * 10^(-3) sec" << endl;
        }
        else if (x == 2)
        {
            time_t start2, end2;

            time(&start2);
            ios_base::sync_with_stdio(false);
            string t1, t2;
            vector<int> ip1(8), ip2(2);
            cout << "Enter the 8bit number" << endl;
            cin >> t1;
            for (int i = 0; i < 8; i++)
            {
                ip1[i] = t1[i];
            }
            cout << "Enter the 2bit number" << endl;
            cin >> t2;
            for (int i = 0; i < 2; i++)
            {
                ip2[i] = t2[i];
            }
            vector<int> res = multiply_8_2_bit(ip1, ip2);
            for (int i = 0; i < res.size(); i++)
            {
                cout << res[i] << " ";
            }
            cout << endl;
            time(&end2);
            double time_taken = double(end2 - start2);
            cout << "Time taken by program is : " << fixed
                 << time_taken << setprecision(5);
            cout << " * 10^(-3) sec" << endl;
        }
        else if (x == 3)
        {
            time_t start2, end2;

            time(&start2);
            ios_base::sync_with_stdio(false);
            vector<int> a = {1, 1, 1, 1, 1, 1, 1, 1}; // 255
            vector<int> b = {1, 1, 1, 1, 1, 1, 1, 1}; // 255
            vector<vector<vector<int>>> ibuf = {{a, b, a, b}, {a, b, a, b}, {a, b, a, b}};

            vector<int> c = {1, 0};

            vector<vector<vector<vector<int>>>> wbuf = {{{c, c, c, c}, {c, c, c, c}, {c, c, c, c}}, {{c, c, c, c}, {c, c, c, c}, {c, c, c, c}}};

            vector<vector<vector<vector<int>>>> obuf = bit_fusion_execution_model2(ibuf, wbuf);

            int N = ibuf.size();
            int M = wbuf.size();

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    for (int k = 0; k < 4; k++)
                    {
                        int sz = obuf[j][i][k].size();
                        for (int l = 0; l < sz; l++)
                        {
                            cout << obuf[j][i][k][l];
                        }
                        cout << " ";
                    }
                }
                cout << "\n";
            }
            time(&end2);
            double time_taken = double(end2 - start2);
            cout << "Time taken by program is : " << fixed
                 << time_taken << setprecision(13);
            cout << " * 10^(-3) sec" << endl;
        }
        else if (x == 4)
        {
            time_t start2, end2;

            time(&start2);
            ios_base::sync_with_stdio(false);
            int a[4], b[4];
            cout << "Enter the 1st 4bit number" << endl;
            for (int i = 0; i < 4; i++)
            {
                cin >> a[i];
            }
            cout << "Enter the 2nd 4bit number" << endl;
            for (int i = 0; i < 4; i++)
            {
                cin >> b[i];
            }
            vector<int> res = decomposing4_bit_cross_4bit_to_2_bit_cross_2_bit(a, b);
            for (int i = 0; i < res.size(); i++)
            {
                cout << res[i] << " ";
            }
            cout << endl;
            int q, l = 0;
            for (int i = res.size() - 1; i >= 0; i--)
            {
                q = res[i];
                l = l + pow(2, res.size() - 1 - (i)) * q;
            }
            cout << l << endl;
            time(&end2);
            double time_taken = double(end2 - start2);
            cout << "Time taken by program is : " << fixed
                 << time_taken << setprecision(13);
            cout << " sec * 10^(-3)" << endl;
        }
        else if (x == 5)
        {
            time_t start2, end2;

            time(&start2);
            ios_base::sync_with_stdio(false);
            long long int a = 11111111; // 255
            long long int b = 11111111; // 255
            vector<vector<long long int>> ibuf = {{a, b, a, b}, {a, b, a, b}, {a, b, a, b}};

            long long int c = 10;

            vector<vector<vector<long long int>>> wbuf = {{{c, c, c, c}, {c, c, c, c}, {c, c, c, c}}, {{c, c, c, c}, {c, c, c, c}, {c, c, c, c}}};

            vector<vector<vector<long long int>>> obuf = bit_fusion_execution_model1(ibuf, wbuf);

            int N = ibuf.size();
            int M = wbuf.size();

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    for (int k = 0; k < 4; k++)
                    {

                        cout << obuf[j][i][k];

                        cout << " ";
                    }
                }
                cout << "\n";
            }
            time(&end2);
            double time_taken = double(end2 - start2);
            cout << "Time taken by program is : " << fixed
                 << time_taken << setprecision(13);
            cout << " * 10^(-3) sec" << endl;
        }
        else if (x == 6)
        {
            time_t start2, end2;

            time(&start2);
            ios_base::sync_with_stdio(false);

            vector<int> a = {0, 0, 0, 0, 0, 0, 0, 0}; // 0
            vector<int> b = {0, 0, 0, 0, 0, 0, 0, 1}; // 1
            vector<int> c = {0, 0, 0, 0, 0, 0, 1, 0}; // 2
            vector<int> d = {0, 0, 0, 0, 0, 0, 1, 1}; // 3

            vector<vector<vector<int>>> image = {{a, d, a, b, a, a}, {c, a, b, a, b, b}, {a, b, d, c, a, b}, {b, b, b, b, a, b}, {a, a, a, b, a, b}, {a, b, b, a, a, a}};

            vector<vector<vector<vector<int>>>> ibuf(3, image);

            vector<int> x = {0, 0};
            vector<int> y = {0, 1};

            vector<vector<vector<int>>> wbuf = {{x, y, y}, {x, y, x}, {y, x, x}};

            vector<vector<vector<vector<int>>>> ans;
            for (int i = 0; i < ibuf.size(); i++)
            {
                ans.push_back(convolution_with_1_color_1_filter(ibuf[i], wbuf));
            }
            int n = ans[0].size();
            int m = ans[0][0].size();
            vector<vector<vector<int>>> final_ans(n, vector<vector<int>>(m, a));

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    for (int k = 0; k < m; k++)
                    {
                        final_ans[j][k] = add(final_ans[j][k], ans[i][j][k]);
                    }
                }
            }
            int mx = 0;
            for (auto i : final_ans)
            {
                for (auto j : i)
                {
                    mx = max(mx, (int)j.size());
                }
            }
            cout<<"\nCONVOLUTED IMAGE\n"<<endl;
            for (auto i : final_ans)
            {
                for (auto j : i)
                {
                    // cout<<j;
                    int check = mx - j.size();
                    for (int i = 0; i < check; i++)
                        cout << 0;
                    for (auto t : j)
                    {
                        cout << t;
                    }
                    cout << " ";
                }
                cout << endl;
            }
            // Perform Pooling Operation
            final_ans = pooling(final_ans);
            // Perform Flattening of PooledFeatureMap
            vector<vector<int>> flattened_ans;
            flattened_ans = flattening(final_ans);
            time(&end2);
            double time_taken = double(end2 - start2);
            cout << "Time taken by program is : " << fixed
                 << time_taken << setprecision(13);
            cout << " * 10^(-3) sec" << endl;
        }
        else
        {
            cout << "Exit Successfully" << endl;
            break;
        }
    }
}