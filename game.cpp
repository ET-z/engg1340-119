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
	int HEIGHT, WIDTH;
	getmaxyx(game_win, HEIGHT, WIDTH);

	// Color pair
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(9, COLOR_MAGENTA, COLOR_BLACK);

	int ch;

	// Height + width for inventory item boxes
	int inventory_height = 10, inventory_width = 20;

	// Dealer's inventory
	vector<vector<WINDOW *>> dealer_items(2, vector<WINDOW *>(4));
	vector<vector<string>> dealer_item_texts(2, vector<string>(4, ""));

	int dealer_start_y = HEIGHT - 2 * HEIGHT / 5 - 1;
	int dealer_start_x = 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dealer_items[i][j] = derwin(game_win, inventory_height, inventory_width,
																	dealer_start_y + i * inventory_height,
																	dealer_start_x + j * inventory_width);
		}
	}
	// Player's inventory
	vector<vector<WINDOW *>> player_items(2, vector<WINDOW *>(4));
	vector<vector<string>> player_item_texts(2, vector<string>(4, ""));

	int player_start_y = HEIGHT - 2 * HEIGHT / 5 - 1;
	int player_start_x = WIDTH - 4 * inventory_width - 1;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			player_items[i][j] = derwin(game_win, inventory_height, inventory_width,
																	player_start_y + i * inventory_height,
																	player_start_x + j * inventory_width);
		}
	}

	// Height and width for health bars
	int health_height = 3, health_width = 72;

	// Dealer health bar
	int dealer_health_start_y = 1;
	int dealer_health_start_x = 2;
	WINDOW *dealer_health = derwin(game_win, health_height, health_width, dealer_health_start_y, dealer_health_start_x);

	// Player health bar
	int player_health_start_y = 1;
	int player_health_start_x = WIDTH - health_width - 2;
	WINDOW *player_health = derwin(game_win, health_height, health_width, player_health_start_y, player_health_start_x);

	// Window dimensions
	int draw_height = 19, draw_width = 60;

	// Dealer draw window
	int dealer_draw_start_y = 10;
	int dealer_draw_start_x = 1;
	WINDOW *dealer_draw = derwin(game_win, draw_height, draw_width, dealer_draw_start_y, dealer_draw_start_x);

	// Player draw window
	int player_draw_start_y = 10;
	int player_draw_start_x = WIDTH - draw_width - 1;
	WINDOW *player_draw = derwin(game_win, draw_height, draw_width, player_draw_start_y, player_draw_start_x);

	// Bullet table
	int bullet_table_height = 20, bullet_table_width = 30;
	int bullets_start_y = HEIGHT - bullet_table_height - 1;
	int bullets_start_x = (WIDTH - bullet_table_width) / 2;
	WINDOW *bullets_table = derwin(game_win, bullet_table_height, bullet_table_width, bullets_start_y, bullets_start_x);

	// Game state variables and initiate players, shells
	int selectedRow = 0, selectedCol = 0;
	bool itemPicked = false;
	string pickedItemText = "";
	Player player("ENGG1340", 100, true);
	Opponent AI("S1mple", 100, false);
	int playerHealth = player.health;
	int dealerHealth = AI.health;
	int playerDamage = 20;
	ShellGenerator gen;
	vector<bool> rounds;
	int currentRound = 0;
	bool playerTurn = true;
	bool handcuffAlreadyUsed = false;

	// generate bullets before game starts
	string initialShells = gen.getShells();
	for (char c : initialShells)
		rounds.push_back(c == '1');

	healthbar(player_health, playerHealth);
	healthbar(dealer_health, dealerHealth);

	int animCount = 0;
	// Main loop
	while (inGame)
	{
		wclear(game_win);
		box(game_win, 0, 0);
		healthbar(player_health, playerHealth);
		healthbar(dealer_health, dealerHealth);
		box(bullets_table, 0, 0);

		// Display picked item if one is picked
		if (!pickedItemText.empty())
		{
			mvwprintw(game_win, 14, (WIDTH - pickedItemText.length()) / 2, pickedItemText.c_str());
		}

		// Draw shell boxes in bullets table ifbullets not empty
		if (!rounds.empty())
		{
			int shell_height = 2;
			int shell_width = 9;
			int shells_per_row = 1;
			int start_y = 1;
			int start_x = (bullet_table_width - (shells_per_row * shell_width)) / 2;

			printCentered(bullets_table, "Shells", 0);
			for (size_t i = currentRound; i < rounds.size(); i++)
			{
				int row = (i - currentRound) / shells_per_row;
				int col = (i - currentRound) % shells_per_row;
				int y = start_y + (row * shell_height);
				int x = start_x + (col * shell_width);

				// Draw box for each shell
				wattron(bullets_table, COLOR_PAIR(9));
				for (int h = 0; h < shell_height; h++)
				{
					mvwaddch(bullets_table, y + h, x, ACS_VLINE);
					mvwaddch(bullets_table, y + h, x + shell_width - 1, ACS_VLINE);
				}
				for (int w = 0; w < shell_width; w++)
				{
					mvwaddch(bullets_table, y, x + w, ACS_HLINE);
					mvwaddch(bullets_table, y + shell_height - 1, x + w, ACS_HLINE);
				}
				// Add corners
				mvwaddch(bullets_table, y, x, ACS_ULCORNER);
				mvwaddch(bullets_table, y, x + shell_width - 1, ACS_URCORNER);
				mvwaddch(bullets_table, y + shell_height - 1, x, ACS_LLCORNER);
				mvwaddch(bullets_table, y + shell_height - 1, x + shell_width - 1, ACS_LRCORNER);
				wattroff(bullets_table, COLOR_PAIR(9));
			}
		}

		wrefresh(bullets_table);

		// Bullet info
		int remainingLiveShells = count(rounds.begin() + currentRound, rounds.end(), true);
		int remainingBlankShells = count(rounds.begin() + currentRound, rounds.end(), false);
		string liveText = "Live shells: " + to_string(remainingLiveShells);
		string blankText = "Blank shells: " + to_string(remainingBlankShells);

		if (currentRound == 0 && animCount == 0)
		{
			// Add random items to inevntories
			random_items(&dealer_item_texts, 0);
			random_items(&player_item_texts, 1);

			// Display live and blank
			mvwprintw(game_win, 5, WIDTH / 2 - liveText.length() / 2, "%s", liveText.c_str());
			mvwprintw(game_win, 6, WIDTH / 2 - blankText.length() / 2, "%s", blankText.c_str());
			wrefresh(game_win);
		}

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
			{
				box(dealer_items[i][j], 0, 0);
				draw_item(dealer_items[i][j], dealer_item_texts[i][j]);
				wrefresh(dealer_items[i][j]);
			}

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 4; j++)
			{
				if (i == selectedRow && j == selectedCol)
					wattron(player_items[i][j], A_REVERSE);
				box(player_items[i][j], 0, 0);
				if (i == selectedRow && j == selectedCol)
					wattroff(player_items[i][j], A_REVERSE);
				draw_item(player_items[i][j], player_item_texts[i][j]);
				wrefresh(player_items[i][j]);
			}

		mvwprintw(game_win, 1, (WIDTH - 18) / 2, "Press ESC to pause");

		draw_player(player_draw);
		if (animCount == 0)
		{
			draw_dealer(dealer_draw);
			napms(2000);
			// Delete the live and blank display after aybe 4-5 seconds (including dealer animation time)
			mvwprintw(game_win, 5, WIDTH / 2 - liveText.length() / 2, "%*s", liveText.length(), "");
			mvwprintw(game_win, 6, WIDTH / 2 - blankText.length() / 2, "%*s", blankText.length(), "");
			wrefresh(game_win);
		}
		else
		{
			draw_dealer_single(dealer_draw);
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
			int result = ::pause();
			if (result == 0)
				continue;
			else if (result == 1)
				inGame = false;
			else if (result == 2)
			{
				inGame = false;
				break;
			}
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
			if (!player_item_texts[selectedRow][selectedCol].empty() && pickedItemText == "")
			{
				itemPicked = true;
				if (player_item_texts[selectedRow][selectedCol] == "apple" && playerHealth <= 100)
				{
					pickedItemText = "You ate an apple";
					player_item_texts[selectedRow][selectedCol] = "";
					playerHealth += 20;
					itemPicked = false;
				}
				else if (player_item_texts[selectedRow][selectedCol] == "knife")
				{
					pickedItemText = "You will now deal double damage";
					player_item_texts[selectedRow][selectedCol] = "";
					playerDamage = 40;
					itemPicked = false;
				}
				else if (player_item_texts[selectedRow][selectedCol] == "magnifyingGlass")
				{
					if (currentRound < rounds.size())
					{
						string bulletType = rounds[currentRound] ? "LIVE" : "BLANK";
						pickedItemText = "The current shell is: " + bulletType;
						player_item_texts[selectedRow][selectedCol] = "";
					}
					itemPicked = false;
				}
				else if (player_item_texts[selectedRow][selectedCol] == "beer")
				{
					bool result = rounds[currentRound++];
					pickedItemText = "You discarded of a shell";
					player_item_texts[selectedRow][selectedCol] = "";
					itemPicked = false;
				}
				else if (player_item_texts[selectedRow][selectedCol] == "handcuff")
				{
					itemPicked = false;
					pickedItemText = "Dealer's turn will be skipped";
					player_item_texts[selectedRow][selectedCol] = "";
					handcuffAlreadyUsed = true;
				}
				wrefresh(game_win);
				wrefresh(player_items[selectedRow][selectedCol]);
				continue;
			}
			break;

		case 10:
		case ' ':
		{
			pickedItemText = "";
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

			if (playerTurn)
			{
				if (action == '1')
				{
					bool result = rounds[currentRound++];
					if (result)
					{
						dealerHealth = max(dealerHealth - playerDamage, 0);
						printCentered(game_win, "A live shell! Dealer takes " + to_string(playerDamage) + " damage.", 6);
						playerDamage = 20;
						if (dealerHealth <= 0)
						{
							printCentered(game_win, "Game Over! You win!", 7);
							napms(3000);
							inGame = false;
							break;
						}
						napms(3000);
						playerTurn = false;
						// Add refresh and delay before dealer's move
						wclear(game_win);
						box(game_win, 0, 0);
						wrefresh(game_win);
					}
					else
					{
						printCentered(game_win, "Oops! Blank! Your turn ends.", 6);
						napms(3000);
						playerDamage = 20;
						playerTurn = false;
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
						playerHealth = max(playerHealth - playerDamage, 0);
						playerDamage = 20;
						printCentered(game_win, "You shot yourself with a live shell! -20 HP.", 6);
						if (playerHealth <= 0)
						{
							printCentered(game_win, "Game Over! Dealer wins!", 7);
							napms(3000);
							inGame = false;
							break;
						}
						napms(3000);
						playerTurn = false;
						// Add refresh and delay before dealer's move
						wclear(game_win);
						box(game_win, 0, 0);
						wrefresh(game_win);
					}
					else
					{
						printCentered(game_win, "Blank! Lucky! Shoot again.", 6);
						napms(3000);
						playerTurn = true;
					}
				}

				if (!playerTurn)
				{
					if (handcuffAlreadyUsed)
					{
						handcuffAlreadyUsed = false;
						wclear(game_win);
						box(game_win, 0, 0);
						wrefresh(game_win);
						printCentered(game_win, "Dealer has skipped their turn!", 26);
						napms(3000);
						continue;
					}
					int remainingLiveShells = count(rounds.begin() + currentRound, rounds.end(), true);
					int remainingTotalShells = rounds.size() - currentRound;
					dealerAI(game_win, playerHealth, dealerHealth, rounds[currentRound++],
									 remainingLiveShells, remainingTotalShells, currentDealerAILevel);
					if (playerHealth <= 0)
					{
						inGame = false;
						break;
					}
					playerTurn = true;
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

	delwin(game_win);
	endwin();
	return 0;
}
