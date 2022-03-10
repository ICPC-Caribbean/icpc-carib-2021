#include "../../.box/testlib.h"

using namespace std;

const int K = 1 << 20;
const int N = 2 * 100000;

int main(int argc, char *argv[])
{
	registerValidation(argc, argv);

	int n = inf.readInt(1, N, "n");
	inf.readSpace();
	int k = inf.readInt(0, K, "k");
	inf.readEoln();

	for (int i = 1; i <= n; i++)
	{
		inf.readInt(0, K, format("a[%d]", i));

		if (i < n)
			inf.readSpace();
	}

	inf.readEoln();
	inf.readEof();

	return 0;
}
