#include "../../.box/testlib.h"
#include <vector>

using namespace std;

const int MAXN = 100;
const int TESTS = 100;

struct TestCase
{
    int n, a, b;

    TestCase() {}
    TestCase(int n, int a, int b) : n(n), a(a), b(b) {}

    void print()
    {
        println(n, a, b);
    }
};

TestCase gen_always_yes()
{
    int n = rnd.next(2, MAXN);
    int a = rnd.next(1, n - 1);
    int b = rnd.next(1, n - a);

    ensure(a >= 1 && b >= 1 && a + b <= n);

    if (rnd.next(2) & 1)
        swap(a, b);

    return TestCase(n, a, b);
}

TestCase gen_always_no()
{
    int n = rnd.next(2, MAXN);
    int a = rnd.next(1, n - 1);
    int b = rnd.next(n - a + 1, n);

    ensure(a + b > n && a >= 1 && a <= n);
    ensure(b >= 1 && b <= n);

    if (rnd.next(2) & 1)
        swap(a, b);

    return TestCase(n, a, b);
}

int main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);

    string mode = argv[2];

    int sumN = 0;
    vector <TestCase> tests;

    while(1) {
        TestCase test = (mode == "always_yes") ? gen_always_yes() : gen_always_no();
        sumN += test.n;

        if(sumN > TESTS)
            break;

        tests.push_back(test);
    }

    cout << tests.size() << "\n";
    for(auto t : tests)
        cout << t.n << " " << t.a << " " << t.b << "\n";

    return 0;
}
