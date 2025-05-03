#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>
#include "game.h"
#include "shell.h"
#include "draw_healthbar.h"
#include "player.h"
#include "dealerAI.h"
#include "items.h"
#include <ctime>

extern DealerAILevel currentDealerAILevel;
using namespace std;

GameWindows initGameWindows(WINDOW *game_win)
{
	GameWindows windows; // create an instance of our struct

	int HEIGHT, WIDTH;
	getmaxyx(game_win, HEIGHT, WIDTH);

	// Height + width for inventory item boxes
	int inventory_height = 10, inventory_width = 20;

	// Dealer's inventory
	int dealer_start_y = HEIGHT - 2 * HEIGHT / 5 - 1;
	int dealer_start_x = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			windows.dealer_items[i][j] = derwin(game_win, inventory_height, inventory_width,
																					dealer_start_y + i * inventory_height,
																					dealer_start_x + j * inventory_width);
		}
	}
	// Player's inventory

	int player_start_y = HEIGHT - 2 * HEIGHT / 5 - 1;
	int player_start_x = WIDTH - 4 * inventory_width - 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			windows.player_items[i][j] = derwin(game_win, inventory_height, inventory_width,
																					player_start_y + i * inventory_height,
																					player_start_x + j * inventory_width);
		}
	}

	// Height and width for health bars
	int health_height = 3, health_width = 72;

	// Dealer health bar
	int dealer_health_start_y = 1;
	int dealer_health_start_x = 2;
	windows.dealer_health = derwin(game_win, health_height, health_width, dealer_health_start_y, dealer_health_start_x);

	// Player health bar
	int player_health_start_y = 1;
	int player_health_start_x = WIDTH - health_width - 2;
	windows.player_health = derwin(game_win, health_height, health_width, player_health_start_y, player_health_start_x);

	// Window dimensions
	int draw_height = 19, draw_width = 60;

	// Dealer draw window
	int dealer_draw_start_y = 10;
	int dealer_draw_start_x = 1;
	windows.dealer_draw = derwin(game_win, draw_height, draw_width, dealer_draw_start_y, dealer_draw_start_x);

	// Player draw window
	int player_draw_start_y = 10;
	int player_draw_start_x = WIDTH - draw_width - 1;
	windows.player_draw = derwin(game_win, draw_height, draw_width, player_draw_start_y, player_draw_start_x);

	// Bullet table
	int bullet_table_height = 20, bullet_table_width = 30;
	int bullets_start_y = HEIGHT - bullet_table_height - 1;
	int bullets_start_x = (WIDTH - bullet_table_width) / 2;
	windows.bullets_table = derwin(game_win, bullet_table_height, bullet_table_width, bullets_start_y, bullets_start_x);

	return windows;
}

void deleteGameWindows(GameWindows &windows)
{
	// Delete player inventory windows
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (windows.player_items[i][j])
			{ // Check if the pointer is not null
				delwin(windows.player_items[i][j]);
				windows.player_items[i][j] = nullptr; // Set to nullptr after deleting
			}
		}
	}

	// Delete dealer inventory windows
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (windows.dealer_items[i][j])
			{
				delwin(windows.dealer_items[i][j]);
				windows.dealer_items[i][j] = nullptr;
			}
		}
	}

	// Delete other windows
	if (windows.player_health)
	{
		delwin(windows.player_health);
		windows.player_health = nullptr;
	}
	if (windows.dealer_health)
	{
		delwin(windows.dealer_health);
		windows.dealer_health = nullptr;
	}
	if (windows.player_draw)
	{
		delwin(windows.player_draw);
		windows.player_draw = nullptr;
	}
	if (windows.dealer_draw)
	{
		delwin(windows.dealer_draw);
		windows.dealer_draw = nullptr;
	}
	if (windows.bullets_table)
	{
		delwin(windows.bullets_table);
		windows.bullets_table = nullptr;
	}
}
// Declare healthbar
void healthbar(WINDOW *bar, int health);

void printCentered(WINDOW *win, const std::string &message, int y_center)
{
	int HEIGHT, WIDTH;
	getmaxyx(win, HEIGHT, WIDTH);

	int x_center = (WIDTH - message.length()) / 2;

	mvwprintw(win, y_center, x_center, "%s", message.c_str());
	wrefresh(win);
}

int game(WINDOW *game_win)
{
	bool inGame = true;

	// Color pair
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(9, COLOR_MAGENTA, COLOR_BLACK);

	int ch;
	// init the GameWindows
	int HEIGHT, WIDTH;
	getmaxyx(game_win, HEIGHT, WIDTH);

	GameWindows windows = initGameWindows(game_win);
	// Game state variables and initiate players, shells
	int selectedRow = 0, selectedCol = 0;
	string pickedItemText = "";
	string dealerPicked = "";
	Player player("ENGG1340", 100, true);
	Opponent AI("S1mple", 100, true);
	player.damage = 20;
	AI.damage = 20;
	ShellGenerator gen;
	vector<bool> rounds;
	int currentRound = 0;
	bool handcuffAlreadyUsed = false;

	// generate bullets before game starts
	string initialShells = gen.getShells();
	for (char c : initialShells)
		rounds.push_back(c == '1');

	healthbar(windows.player_health, player.health);
	healthbar(windows.dealer_health, AI.health);

	int animCount = 0;
	// Main loop
	while (inGame)
	{
		// Check health status at the start of each loop
		if (player.health <= 0)
		{
			wclear(game_win);
			printCentered(game_win, "Game Over! Dealer wins!", 15);
			napms(3000);
			inGame = false;
			break;
		}
		else if (AI.health <= 0)
		{
			wclear(game_win);
			printCentered(game_win, "Game Over! You win!", 15);
			napms(3000);
			inGame = false;
			break;
		}

		wclear(game_win);
		box(game_win, 0, 0);
		healthbar(windows.player_health, player.health);
		healthbar(windows.dealer_health, AI.health);
		box(windows.bullets_table, 0, 0);

		// Display picked item if one is picked
		if (!pickedItemText.empty())
		{
			mvwprintw(game_win, 14, (WIDTH - pickedItemText.length()) / 2, pickedItemText.c_str());
		}

		string playerTurnstring = "Player turn? " + to_string(player.isTurn);
		mvwprintw(game_win, 3, (WIDTH - playerTurnstring.length()) / 2, playerTurnstring.c_str());
		// Draw shell boxes in bullets table ifbullets not empty
		if (!rounds.empty())
		{
			int shell_height = 2;
			int shell_width = 9;
			int shells_per_row = 1;
			int start_y = 1;
			int start_x = (30 - (shells_per_row * shell_width)) / 2;

			printCentered(windows.bullets_table, "Shells", 0);
			for (size_t i = currentRound; i < rounds.size(); i++)
			{
				int row = (i - currentRound) / shells_per_row;
				int col = (i - currentRound) % shells_per_row;
				int y = start_y + (row * shell_height);
				int x = start_x + (col * shell_width);

				// Draw box for each shell
				wattron(windows.bullets_table, COLOR_PAIR(9));
				for (int h = 0; h < shell_height; h++)
				{
					mvwaddch(windows.bullets_table, y + h, x, ACS_VLINE);
					mvwaddch(windows.bullets_table, y + h, x + shell_width - 1, ACS_VLINE);
				}
				for (int w = 0; w < shell_width; w++)
				{
					mvwaddch(windows.bullets_table, y, x + w, ACS_HLINE);
					mvwaddch(windows.bullets_table, y + shell_height - 1, x + w, ACS_HLINE);
				}
				// Add corners
				mvwaddch(windows.bullets_table, y, x, ACS_ULCORNER);
				mvwaddch(windows.bullets_table, y, x + shell_width - 1, ACS_URCORNER);
				mvwaddch(windows.bullets_table, y + shell_height - 1, x, ACS_LLCORNER);
				mvwaddch(windows.bullets_table, y + shell_height - 1, x + shell_width - 1, ACS_LRCORNER);
				wattroff(windows.bullets_table, COLOR_PAIR(9));
			}
		}

		wrefresh(windows.bullets_table);

		// Bullet info
		int remainingLiveShells = count(rounds.begin() + currentRound, rounds.end(), true);
		int remainingBlankShells = count(rounds.begin() + currentRound, rounds.end(), false);
		string liveText = "Live shells: " + to_string(remainingLiveShells);
		string blankText = "Blank shells: " + to_string(remainingBlankShells);

		if (currentRound == 0 && animCount == 0)
		{
			// Add random items to inevntories
			random_items(&windows.dealer_item_texts, 0);
			random_items(&windows.player_item_texts, 1);

			// Display live and blank
			mvwprintw(game_win, 5, WIDTH / 2 - liveText.length() / 2, "%s", liveText.c_str());
			mvwprintw(game_win, 6, WIDTH / 2 - blankText.length() / 2, "%s", blankText.c_str());
			wrefresh(game_win);
		}

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
			{
				box(windows.dealer_items[i][j], 0, 0);
				draw_item(windows.dealer_items[i][j], windows.dealer_item_texts[i][j]);
				wrefresh(windows.dealer_items[i][j]);
			}

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
			{
				if (i == selectedRow && j == selectedCol)
					wattron(windows.player_items[i][j], A_REVERSE);
				box(windows.player_items[i][j], 0, 0);
				if (i == selectedRow && j == selectedCol)
					wattroff(windows.player_items[i][j], A_REVERSE);
				draw_item(windows.player_items[i][j], windows.player_item_texts[i][j]);
				wrefresh(windows.player_items[i][j]);
			}

		mvwprintw(game_win, 1, (WIDTH - 18) / 2, "Press ESC to pause");

		draw_player(windows.player_draw);
		if (animCount == 0)
		{
			draw_dealer(windows.dealer_draw);
			napms(2000);
			// Delete the live and blank display after aybe 4-5 seconds (including dealer animation time)
			mvwprintw(game_win, 5, WIDTH / 2 - liveText.length() / 2, "%*s", liveText.length(), "");
			mvwprintw(game_win, 6, WIDTH / 2 - blankText.length() / 2, "%*s", blankText.length(), "");
			wrefresh(game_win);
		}
		else
		{
			draw_dealer_single(windows.dealer_draw);
		}

		wrefresh(game_win);
		animCount += 1;
		if (animCount > 100)
		{
			animCount = 1;
		}

		ch = wgetch(game_win);

		switch (ch)
		{
		case 27: // ESC
		{
			return 1;
			break;
		}

		case KEY_UP:
			if (selectedRow > 0)
				selectedRow--;
			break;

		case KEY_DOWN:
			if (selectedRow < 1)
				selectedRow++;
			break;

		case KEY_LEFT:
			if (selectedCol > 0)
				selectedCol--;
			break;

		case KEY_RIGHT:
			if (selectedCol < 3)
				selectedCol++;
			break;

		case 'e':
		case 'E':
			if (!windows.player_item_texts[selectedRow][selectedCol].empty())
			{
				if (windows.player_item_texts[selectedRow][selectedCol] == "apple" && player.health <= 100)
				{
					pickedItemText = "You ate an apple";
					windows.player_item_texts[selectedRow][selectedCol] = "";
					if (player.health + 20 <= 100)
						player.health += 20;
				}
				else if (windows.player_item_texts[selectedRow][selectedCol] == "knife")
				{
					pickedItemText = "You will now deal double damage";
					windows.player_item_texts[selectedRow][selectedCol] = "";
					player.damage = 40;
				}
				else if (windows.player_item_texts[selectedRow][selectedCol] == "magnifyingGlass")
				{
					if (currentRound < rounds.size())
					{
						string bulletType = rounds[currentRound] ? "LIVE" : "BLANK";
						pickedItemText = "The current shell is: " + bulletType;
						windows.player_item_texts[selectedRow][selectedCol] = "";
					}
				}
				else if (windows.player_item_texts[selectedRow][selectedCol] == "beer")
				{
					bool result = rounds[currentRound++];
					pickedItemText = "You discarded of a shell";
					windows.player_item_texts[selectedRow][selectedCol] = "";
				}
				else if (windows.player_item_texts[selectedRow][selectedCol] == "handcuff")
				{
					pickedItemText = "Dealer's turn will be skipped";
					windows.player_item_texts[selectedRow][selectedCol] = "";
					handcuffAlreadyUsed = true;
				}
				wrefresh(game_win);
				wrefresh(windows.player_items[selectedRow][selectedCol]);
				continue;
			}
			break;

		case 10:
		case ' ':
		{
			pickedItemText = "";
			dealerPicked = "";
			if (rounds.empty() || currentRound >= rounds.size())
			{
				string shellStr = gen.getShells();
				rounds.clear();
				for (char c : shellStr)
					rounds.push_back(c == '1');
				currentRound = 0;
			}

			int x_center = (WIDTH - 56) / 2;

			mvwprintw(game_win, 5, x_center, "Choose your action: [1] Shoot Dealer  [2] Shoot Yourself");

			wrefresh(game_win);
			int action = wgetch(game_win);

			if (player.isTurn)
			{
				if (action == '1')
				{
					bool result = rounds[currentRound++];
					if (result)
					{
						AI.health = max(AI.health - player.damage, 0);
						string damageMessage = "A live shell! Dealer takes " + to_string(player.damage) + " damage.";
						printCentered(game_win, damageMessage, 6);
						player.damage = 20;
						if (AI.health <= 0)
						{
							napms(2000);
							continue;
						}
						napms(3000);
						player.isTurn = false;
						// Add refresh and delay before dealer's move
						wclear(game_win);
						box(game_win, 0, 0);
						wrefresh(game_win);
					}
					else
					{
						printCentered(game_win, "Oops! Blank! Your turn ends.", 6);
						napms(3000);
						player.damage = 20;
						player.isTurn = false;
						// Add refresh and delay before dealer's move
						wclear(game_win);
						box(game_win, 0, 0);
						wrefresh(game_win);
					}
				}
				else if (action == '2')
				{
					bool result = rounds[currentRound++];
					if (result)
					{
						player.health = max(player.health - player.damage, 0);
						player.damage = 20;
						printCentered(game_win, "You shot yourself with a live shell! -20 HP.", 6);
						if (player.health <= 0)
						{
							napms(2000);
							continue;
						}
						napms(3000);
						player.isTurn = false;
						// Add refresh and delay before dealer's move
						wclear(game_win);
						box(game_win, 0, 0);
						wrefresh(game_win);
					}
					else
					{
						printCentered(game_win, "Blank! Lucky! Shoot again.", 6);
						napms(3000);
						player.isTurn = true;
					}
				}

				if (!player.isTurn)
				{
					if (handcuffAlreadyUsed)
					{
						handcuffAlreadyUsed = false;
						player.isTurn = true;
						wclear(game_win);
						box(game_win, 0, 0);
						wrefresh(game_win);
						printCentered(game_win, "Dealer has skipped their turn!", 26);
						napms(3000);
						continue;
					}
					int remainingLiveShells = count(rounds.begin() + currentRound, rounds.end(), true);
					int remainingTotalShells = rounds.size() - currentRound;

					// Check if dealer has any items before trying to use them
					bool hasItems = false;
					int itemCount = 0;
					for (const auto &row : windows.dealer_item_texts)
					{
						for (const auto &item : row)
						{
							if (!item.empty())
							{
								itemCount++;
								if (itemCount > 2)
								{
									hasItems = true;
									break;
								}
							}
						}
						if (hasItems)
							break;
					}

					// Dealer uses random items only if they have any
					if (hasItems)
					{
						srand(time(0) + 1);
						int randomNumberItems = rand() % 2 + 1;
						int Y = 27;
						for (int i = 0; i < randomNumberItems; i++)
						{
							pair<int, int> coords = use_random_item(&windows.dealer_item_texts);
							if (coords.first != -1 && coords.second != -1)
							{
								string item = windows.dealer_item_texts[coords.first][coords.second];
								if (item == "apple" && AI.health <= 100)
								{
									dealerPicked = "Dealer ate an apple";
									if (AI.health + 20 <= 100)
										AI.health += 20;
									windows.dealer_item_texts[coords.first][coords.second] = "";
								}
								else if (item == "knife")
								{
									dealerPicked = "Dealer will now deal double damage";
									AI.damage = 40;
									windows.dealer_item_texts[coords.first][coords.second] = "";
								}
								else if (item == "magnifyingGlass")
								{
									dealerPicked = "Dealer threw away an item";
									windows.dealer_item_texts[coords.first][coords.second] = "";
								}
								else if (item == "beer")
								{
									bool result = rounds[currentRound++];
									dealerPicked = "Dealer discarded of a shell";
									windows.dealer_item_texts[coords.first][coords.second] = "";
								}
								else if (item == "handcuff")
								{
									dealerPicked = "Dealer threw away an item";
									windows.dealer_item_texts[coords.first][coords.second] = "";
								}
							}
							if (!dealerPicked.empty())
							{
								mvwprintw(game_win, Y + i * 2, (WIDTH - dealerPicked.length()) / 2, dealerPicked.c_str());
							}
							wrefresh(game_win);
							wrefresh(windows.dealer_items[coords.first][coords.second]);
							napms(2000);
						}
					}
					bool currentShell = rounds[currentRound++];
					dealerAI(game_win, player.health, AI.health, currentShell,
									 remainingLiveShells, remainingTotalShells, currentDealerAILevel, player.isTurn, AI.damage, AI.isTurn);
					while (AI.isTurn == true && currentRound < rounds.size())
					{
						currentShell = rounds[currentRound++];
						dealerAI(game_win, player.health, AI.health, currentShell,
										 remainingLiveShells, remainingTotalShells, currentDealerAILevel, player.isTurn, AI.damage, AI.isTurn);
					}
					player.isTurn = true;
					if (player.health <= 0)
					{
						inGame = false;
						break;
					}
				}
			}

			if (currentRound >= rounds.size())
			{
				string shellString = gen.getShells();
				rounds.clear();
				for (char c : shellString)
					rounds.push_back(c == '1');
				currentRound = 0;
				animCount = 0;
				printCentered(game_win, "Reloading...", 9);
				napms(500);
				wrefresh(game_win);
				break;
			}
		}
		break;

		default:
			mvwprintw(game_win, 1, 2, "Unknown key: ch = %d", ch);
			wrefresh(game_win);
			break;
		} // end switch
	} // end while

	deleteGameWindows(windows);

	delwin(game_win);
	endwin();
	return 0;
}
