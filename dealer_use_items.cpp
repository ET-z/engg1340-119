#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <ncurses.h>

using namespace std;

string use_random_item(vector<vector<string>> *inventory)
{
  srand(time(0));
  while (true)
  {
    int randomRow = rand() % 2;
    int randomCol = rand() % 5;
    if ((*inventory)[randomRow][randomCol] == "")
    {
      continue;
    }
    return (*inventory)[randomRow][randomCol];
  }
}
