#include "../../.box/testlib.h"

using namespace std;

const int K = 1e9;
const int N = 1e5;

int main(int argc, char *argv[])
{
   registerValidation(argc, argv);

   int n = inf.readInt(2, N, "n");
   inf.readEoln();

   for (int i = 1; i <= n; i++)
   {
      inf.readInt(1, K, format("a[%d]", i));

      if (i < n)
         inf.readSpace();
   }

   inf.readEoln();
   inf.readEof();

   return 0;
}
