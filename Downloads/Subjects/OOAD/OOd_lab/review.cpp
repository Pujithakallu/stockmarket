#include <iostream>
using namespace std;
int main()
{
    int var1=5, var2=10;
    for(int i=1; i <=2; i++)
    {
        cout << var1++ << '\t' << --var2 <<endl;
        cout << var2-- << '\t' << ++var1 <<endl;
    }
return 0;
}
