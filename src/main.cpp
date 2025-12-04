// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#include <ncurses.h>

#include "names.h"   // NOLINT(build/include_subdir)
#include "player.h"  // NOLINT(build/include_subdir)
#include "team.h"    // NOLINT(build/include_subdir)

void display_player_row(int row, int num, const Player& p) {
  mvprintw(row, 0,
           "%2d. %-18s %s %-2s  OVR: %2d  "
           "SPD:%2d STR%2d 3PT:%2d FIN:%2d HND:%2d REB:%2d",
           num, p.full_name().c_str(), p.position_str().c_str(),
           p.year_str().c_str(), p.overall, p.attrs.speed, p.attrs.strength,
           p.attrs.three_point, p.attrs.finishing, p.attrs.handles,
           p.attrs.rebounding);
}

void display_team(const Team& t) {
  mvprintw(0, 0, "UNRANKED - Team generation testing");
  mvprintw(1, 0, "-----------------------------------");

  // team info
  mvprintw(3, 0, "%s", t.full_name().c_str());
  mvprintw(4, 0, "Location: %s", t.location.c_str());
  mvprintw(5, 0, "Prestige: %d  Facilities: %d  Budget: %d", t.prestige,
           t.facilities, t.budget);
  mvprintw(6, 0, "Roster average: %d OVR", t.average_overall());

  // Roster
  mvprintw(8, 0,
           "  %-18s %-2s %-2s %-6s  "
           "%-6s %-6s %-6s %-6s %-6s %-6s",
           "NAME", "POS", "YR", "OVR", "SPD", "STR", "3PT", "FIN", "HND",
           "REB");
  mvprintw(9, 0,
           "------------------------------------------"
           "-----------------------------------");
  int row = 10;
  int num = 1;
  for (const auto& p : t.roster) {
    display_player_row(row, num, p);
    row++;
    num++;
  }
  // Position
  auto counts = t.position_counts();
  mvprintw(row + 1, 0, "Position counts: PG:%d, SG:%d, SF:%d, PF:%d, C:%d",
           counts[0], counts[1], counts[2], counts[3], counts[4]);
  mvprintw(row + 3, 0, "Press any key to exit...");
}

int main() {
  // random seed
  init_random();

  // ncurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  Team team = generate_team(3, ConferenceTier::Power);

  display_team(team);

  refresh();
  getch();

  endwin();
  return 0;
}
