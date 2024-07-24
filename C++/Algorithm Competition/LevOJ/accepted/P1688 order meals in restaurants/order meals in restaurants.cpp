#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;

        vector<int> soup(a);
        for (int i = 0; i < a; i++)
        {
            cin >> soup[i];
        }

        vector<int> rice(b);
        for (int i = 0; i < b; i++)
        {
            cin >> rice[i];
        }

        vector<int> noodle(c);
        for (int i = 0; i < c; i++)
        {
            cin >> noodle[i];
        }

        vector<int> meat(d);
        for (int i = 0; i < d; i++)
        {
            cin >> meat[i];
        }

        vector<int> vegetable(e);
        for (int i = 0; i < e; i++)
        {
            cin >> vegetable[i];
        }

        meat.push_back(0);
        vegetable.push_back(0);

        int min_price, max_price;
        cin >> min_price >> max_price;

        int count = 0;
        for (int i = 0; i < d; i++)
        {
            for (int j = i + 1; j <= d; j++)
            {
                for (int k = 0; k < e; k++)
                {
                    for (int l = k + 1; l <= e; l++)
                    {
                        int price = meat[i] + meat[j] + vegetable[k] + vegetable[l];
                        for (int m = 0; m < a; m++)
                        {
                            for (int n = 0; n < b; n++)
                            {
                                price += soup[m] + rice[n];
                                if (price >= min_price && price <= max_price)
                                {
                                    count++;
                                }
                                price -= soup[m] + rice[n];
                            }
                        }
                        for (int p = 0; p < c; p++)
                        {
                            price += noodle[p];
                            if (price >= min_price && price <= max_price)
                            {
                                count++;
                            }
                            price -= noodle[p];
                        }
                    }
                }
            }
        }

        cout << count << endl;
    }

    return 0;
}
