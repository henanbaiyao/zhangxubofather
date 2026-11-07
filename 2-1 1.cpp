#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    string name;
    double chinese, math, english;
};

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        Student s;
        cin >> s.name >> s.chinese >> s.math >> s.english;
        double avg = (s.chinese + s.math + s.english) / 3.0;
        cout << fixed << setprecision(2);
        cout << s.name << " " << s.chinese << " " << s.math << " " << s.english << " " << avg;
        if (avg >= 90)
        {
            cout << " Excellent";
        }
        cout << endl;
    }
    return 0;
}
