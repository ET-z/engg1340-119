while (true)
{
    werase(game_win);
    box(game_win, 0, 0);

    vector<string> lines = {
        "🎮 Buckshot Roulette: Tutorial",
        "",
        "Welcome to Buckshot Roulette.",
        "A psychological shootout between you and the dealer.",
        "Your life depends on a chambered round.",
        "",
        "You’ll take turns with the dealer — spin the cylinder and pull the trigger.",
        "Each round could be a blank... or a live shot.",
        "",
        "🎯 Goal: Survive and outlast the dealer.",
        "Each shootout has 9 rounds. If one of you reaches 0 HP, game over."
    };

    int start_y = (HEIGHT - static_cast<int>(lines.size())) / 2;

    for (size_t i = 0; i < lines.size(); ++i) {
        print_centered_animated(game_win, start_y + i, lines[i]);
    }

    // Draw instruction and arrow
    string escape = "Press ESC to return";
    mvwprintw(game_win, HEIGHT - 3, (WIDTH - static_cast<int>(escape.size())) / 2, "%s", escape.c_str());

    string arrow = "-->";
    mvwprintw(game_win, HEIGHT - 3, WIDTH - 10, "%s", arrow.c_str());

    wrefresh(game_win);

    // Input
    ch = wgetch(game_win);
    if (ch == KEY_RIGHT) {
        tutorial2(game_win);
        break;
    } else if (ch == 27) {
        return 1;
    }
}
return 0;
