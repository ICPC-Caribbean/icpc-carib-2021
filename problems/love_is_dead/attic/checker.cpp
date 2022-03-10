#include "../../.box/testlib.h"
#include <string>
#include <vector>
 
using namespace std;
 
const string YES = "YES";
const string NO = "NO";
 
void readAndCheckAnswer(int n, int a, int b, InStream& in)
{
    vector<vector<int>> f_men(n, vector<int>(n));
    auto f_women = f_men;
    for (int i = 0; i < n; ++i)
        for (int it = a; it--; )
        {
            int j = in.readInt(1, n, format("%d-th man wants a woman that is outside [1, %d]", i + 1, n)) - 1;
            ++f_men[i][j];
        }
    for (int i = 0; i < n; ++i)
        for (int it = b; it--; )
        {
            int j = in.readInt(1, n, format("%d-th woman wants a man that is outside [1, %d]", i + 1, n)) - 1;
            ++f_women[j][i];
        }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (f_men[i][j] > 1)
                in.quitf(_wa, "%d men wants woman number %d", f_men[i][j], j+1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (f_women[i][j] > 1)
                in.quitf(_wa, "%d women wants men number %d", f_women[i][j], i+1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (f_men[i][j] + f_women[i][j] > 1)
                in.quitf(_wa, "man %d and woman %d loves each other", i+1, j+1);
}
 
int main(int argc, char * argv[])
{
    setName("%s", ("multiple " + YES + "/" + NO + " (case insensetive)").c_str());
    registerTestlibCmd(argc, argv);
 
    int test = inf.readInt();
 
    int index = 0, yesCount = 0, noCount = 0;
    std::string pa;
    while (test--)
    {
        int n = inf.readInt();
        int a = inf.readInt();
        int b = inf.readInt();
 
        index++;
        std::string ja = upperCase(ans.readToken());
        pa = upperCase(ouf.readToken());
 
        if (ja != YES && ja != NO)
            quitf(_fail, "%s or %s expected in answer, but %s found [%d%s token]",
                YES.c_str(), NO.c_str(), compress(ja).c_str(), index, englishEnding(index).c_str());
 
        if (pa == YES)
            yesCount++;
        else if (pa == NO)
            noCount++;
        else
            quitf(_pe, "%s or %s expected, but %s found [%d%s token]",
                YES.c_str(), NO.c_str(), compress(pa).c_str(), index, englishEnding(index).c_str());
 
        if (ja != pa)
            quitf(_wa, "expected %s, found %s [%d%s token]",
                compress(ja).c_str(), compress(pa).c_str(), index, englishEnding(index).c_str());
 
        if (ja == YES)
        {
            readAndCheckAnswer(n, a, b, ans);
            readAndCheckAnswer(n, a, b, ouf);
        }
    }
 
    int extraInAnsCount = 0;
    while (!ans.seekEof())
    {
        ans.readToken();
        extraInAnsCount++;
    }
    
    int extraInOufCount = 0;
    while (!ouf.seekEof())
    {
        ouf.readToken();
        extraInOufCount++;
    }
 
    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements", index + extraInAnsCount, index);
    
    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements", index + extraInOufCount, index);
 
    if (index == 0)
        quitf(_ok, "Empty output");
    else if (index == 1)
        quitf(_ok, "%s", pa.c_str());
    else
        quitf(_ok, "%d token(s): yes count is %d, no count is %d", index, yesCount, noCount);
 
    quitf(_fail, "Impossible case");
}
