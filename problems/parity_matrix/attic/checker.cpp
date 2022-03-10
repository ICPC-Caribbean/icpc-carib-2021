#include "../../.box/testlib.h"
#include <vector>

using namespace std;

vector<vector<int>> readMatrix(InStream &in, int n, int m)
{
    vector<vector<int>> res(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            res[i][j] = in.readInt();
        }

    return res;
}

int validate_and_difference(vector<vector<int>> &initial, vector<vector<int>> &updated)
{
    int n = initial.size(), m = initial[0].size();
    long long diff = 0;

    vector<int> rows(n), cols(m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            rows[i] ^= updated[i][j] & 1;
            cols[j] ^= updated[i][j] & 1;
            diff += updated[i][j] - initial[i][j];
        }

    if (*max_element(rows.begin(), rows.end()) != 0 ||
        *max_element(cols.begin(), cols.end()) != 0)
    {
        quitf(_wa, "All columns and rows must be even");
    }

    return diff;
}

int main(int argc, char *argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();

    auto initial = readMatrix(inf, n, m);
    auto output = readMatrix(ouf, n, m);
    auto answer = readMatrix(ans, n, m);

    int diff_output = validate_and_difference(initial, output);
    int diff_answer = validate_and_difference(initial, answer);

    if (diff_output != diff_answer)
    {
        quitf(_wa, "Expected difference %d, found %d", diff_answer, diff_output);
    }
    else
    {
        quitf(_ok, "Increased %d times", diff_answer);
    }
}
