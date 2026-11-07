#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

// ========== 声明部分 ==========
const double FEE_RATE = 0.02;
const double WARNING_BALANCE = 10.0; // 低余额警戒值

struct Card
{
    string id;
    string name;
    double balance;
    int transCount;
};

namespace card
{
    Card* createCards(int n);
    void freeCards(Card* p);
    void inputCard(Card& c);
    void deposit(Card& c, double money, double rate = FEE_RATE);
    void spend(Card& c, double money);
    void spend(Card& c, double money, string item);
    void showBalance(const Card& c);
    void viewStudentID(const Card* p);
    int toCent(double yuan);
    void printReport(Card arr[], int n);
}

// ========== 实现部分 ==========
namespace card
{
    Card* createCards(int n)
    {
        if(n <= 0)
            throw runtime_error("账户数量必须为正整数");
        return new Card[n];
    }

    void freeCards(Card* p)
    {
        delete[] p;
    }

    void inputCard(Card& c)
    {
        cin >> c.id >> c.name >> c.balance;
        if(!cin || c.balance < 0)
            throw runtime_error("输入格式错误或余额为负数");
        c.transCount = 0;
    }

    void deposit(Card& c, double money, double rate)
    {
        if(money <= 0)
            throw runtime_error("充值金额必须大于0");
        double add = money * (1 - rate);
        c.balance += add;
        c.transCount++;
    }

    void spend(Card& c, double money)
    {
        if(money < 0)
            throw runtime_error("消费金额不能为负");
        if(c.balance < money)
            throw runtime_error("余额不足，交易失败");
        c.balance -= money;
        c.transCount++;
    }

    void spend(Card& c, double money, string item)
    {
        spend(c, money);
        cout << "消费项目：" << item << endl;
    }

    void showBalance(const Card& c)
    {
        cout << "当前余额：" << fixed << setprecision(2) << c.balance << " 元";
        if(c.balance < WARNING_BALANCE)
            cout << " 【余额偏低】";
        cout << endl;
    }

    void viewStudentID(const Card* p)
    {
        cout << "学号：" << p->id << endl;
    }

    int toCent(double yuan)
    {
        return static_cast<int>(yuan * 100);
    }

    void printReport(Card arr[], int n)
    {
        cout << left
             << setw(12) << "学号"
             << setw(10) << "姓名"
             << right << setw(10) << "余额(元)"
             << setw(10) << "交易次数"
             << endl;
        cout << "------------------------------------------------------" << endl;
        cout << fixed << setprecision(2);
        for(int i = 0; i < n; i++)
        {
            cout << left
                 << setw(12) << arr[i].id
                 << setw(10) << arr[i].name
                 << right << setw(10) << arr[i].balance
                 << setw(10) << arr[i].transCount
                 << endl;
        }
    }
}

// ========== 主程序部分 ==========
int main()
{
    int n;
    cout << "请输入账户数量：";
    while(!(cin >> n) || n <= 0)
    {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "输入无效，请输入正整数：";
    }

    Card* cards = nullptr;
    try
    {
        cards = card::createCards(n);
        // 循环录入账户
        for(int i = 0; i < n; i++)
        {
            bool ok = false;
            while(!ok)
            {
                cout << "录入第" << i+1 << "个账户（学号 姓名 初始余额）：";
                try
                {
                    card::inputCard(cards[i]);
                    ok = true;
                }
                catch(const runtime_error &e)
                {
                    cin.clear();
                    cin.ignore(1024, '\n');
                    cerr << "错误：" << e.what() << "，请重新录入\n";
                }
            }
        }

        cout << "\n===== 首个账户业务演示 =====" << endl;
        Card &first = cards[0];
        try
        {
            card::deposit(first, 100);
            cout << "充值100元完成\n";
            card::spend(first, 8.5, "食堂午餐");
            card::spend(first, 2, "超市矿泉水");

            card::viewStudentID(&first);
            card::showBalance(first);
            cout << "余额折合：" << card::toCent(first.balance) << " 分\n";
        }
        catch(const runtime_error &e)
        {
            cerr << "业务异常：" << e.what() << endl;
        }

        cout << "\n===== 全部账户报表 =====" << endl;
        card::printReport(cards, n);
    }
    catch(const runtime_error &e)
    {
        cerr << "程序异常：" << e.what() << endl;
    }

    if(cards != nullptr)
        card::freeCards(cards);

    system("pause");
    return 0;
}
