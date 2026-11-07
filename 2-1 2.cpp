#include <iostream>
#include <cstring>
using namespace std;

int countVowels(const char* p)
{
    int cnt = 0;
    while (*p != '\0')
    {
        char ch = *p;
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'
            || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
        {
            cnt++;
        }
        p++;
    }
    return cnt;
}

int main()
{
    char str[1000];
    cin.getline(str, 1000);
    int num = countVowels(str);
    cout << "Number of vowels: " << num << endl;
    return 0;
}
