#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <ncurses.h>
#include <utility>

using namespace std;

pair<int, int> use_random_item(vector<vector<string>> *inventory)
{
  // Count non-empty slots
  int total_items = 0;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (!(*inventory)[i][j].empty())
      {
        total_items++;
      }
    }
  }

  if (total_items == 0)
  {
    return make_pair(-1, -1); // Return if no items
  }

  // Select random item
  while (true)
  {
    int randomRow = rand() % 2;
    int randomCol = rand() % 4;
    if (!(*inventory)[randomRow][randomCol].empty())
    {
      return make_pair(randomRow, randomCol);
    }
  }
}
