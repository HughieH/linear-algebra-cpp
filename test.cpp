#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
   vector<int> matrix {1, 2, 3, 4};

   for (const int& word : matrix)
   {
      cout << word << " ";
   }
   cout << endl;
}