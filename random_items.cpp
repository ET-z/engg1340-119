#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <ncurses.h>

using namespace std;

void random_items(vector<vector<string>> *inventory, int seed_offset = 0)
{
  srand(time(0) + seed_offset);
  vector<string> items = {"magnifyingGlass", "handcuff", "beer", "knife", "apple"};
  int inserted = 0;

  while (inserted < 3)
  {
    // Rnaomd between 0 - 4
    int random = rand() % 5;
    bool insertedThisRound = false;

    for (int j = 0; j < inventory->size(); j++)
    {
      for (int k = 0; k < (*inventory)[j].size(); k++)
      {
        if ((*inventory)[j][k] == "")
        {
          (*inventory)[j][k] = items[random];
          inserted++;
          insertedThisRound = true;
          break;
        }
      }
      if (insertedThisRound)
        break;
    }

    if (insertedThisRound == false)
      break;
  }
}