#include <header.h>

using namespace std;

vector<wstring> locals;

BOOL CALLBACK MyFuncLocaleEx(LPWSTR pStr, DWORD dwFlags, LPARAM lparam)
{
    locals.push_back(pStr);
    return TRUE;
}

void solve() {
    EnumSystemLocalesEx(MyFuncLocaleEx, LOCALE_ALL, NULL, NULL);

    for (vector<wstring>::const_iterator str = locals.begin(); str != locals.end(); ++str)
        wcout << *str << endl;

    wcout << "Total " << locals.size() << " locals found." << endl;
}

int main() {
    solve();
}