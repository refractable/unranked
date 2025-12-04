// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#include <ncurses.h>

#include "names.h"  // NOLINT(build/include_subdir)
#include "player.h"  // NOLINT(build/include_subdir)

void display_player(int row, const Player& p) {
  mvprintw(row, 0, "%-20s %s %s  OVR:%2d  SPD:%2d STR:%2d VRT:%2d",
           p.full_name().c_str(), p.position_str().c_str(),
           p.year_str().c_str(), p.overall, p.attrs.speed, p.attrs.strength,
           p.attrs.vertical);

  mvprintw(
      row + 1, 2, "3PT:%2d MID:%2d FIN:%2d HND:%2d PAS: %2d PST:%2d REB:%2d",
      p.attrs.three_point, p.attrs.mid_range, p.attrs.finishing,
      p.attrs.handles, p.attrs.passing, p.attrs.post_game, p.attrs.rebounding);

  mvprintw(row + 2, 2, "PER:%2d INT:%2d IQ:%2d CLU:%2d STA:%2d POT:%2d",
           p.attrs.perimeter_d, p.attrs.interior_d, p.attrs.iq, p.attrs.clutch,
           p.attrs.stamina, p.attrs.potential);
}

int main() {
  // random seed
  init_random();

  // ncurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Title
  mvprintw(0, 0, "UNRANKED - generating players test");
  mvprintw(1, 0, "-----------------------------------");
  mvprintw(3, 0, "Generating 5 random players (3 star talent):");
  mvprintw(4, 0, "---------------------------------------------");

  // Generate and display players
  int row = 6;
  for (int i = 0; i < 5; i++) {
    Player p = generate_random_player(3);
    display_player(row, p);
    row += 4;
  }

  mvprintw(row + 1, 0, "Press any key to exit...");

  refresh();
  getch();

  endwin();
  return 0;
}
