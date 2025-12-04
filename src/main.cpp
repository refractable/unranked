// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#include <ncurses.h>

#include <vector>

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

void display_team_list(const std::vector<Team>& teams) {
  mvprintw(0, 0, "UNRANKED - Multiple team generation testing");
  mvprintw(1, 0, "-------------------------------------------");

  // team info
  mvprintw(3, 0, "%-4s, %-35s, %-12s, %4s, %4s, %4s, %4s", "#", "TEAM",
           "LOCATION", "PRES", "FAC", "BUD", "OVR");
  mvprintw(4, 0,
           "------------------------------------------"
           "-----------------------------------");
  int row = 5;
  int num = 1;
  for (const auto& t : teams) {
    mvprintw(row, 0, "%-4d %-35s %-12s %4d %4d %4d %4d", num,
             t.full_name().c_str(), t.location.c_str(), t.prestige,
             t.facilities, t.budget, t.average_overall());
    row++;
    num++;
  }

  mvprintw(row + 2, 0, "Press number to view roster, 'q' to quit..");
  refresh();
}

void display_team_roster(const Team& t) {
  clear();
  mvprintw(0, 0, "UNRANKED - Team Roster");
  mvprintw(1, 0, "======================");

  mvprintw(3, 0, "%s", t.full_name().c_str());
  mvprintw(4, 0, "Location: %s", t.location.c_str());
  mvprintw(5, 0, "Prestige: %d  Facilities: %d  Budget: %d", t.prestige,
           t.facilities, t.budget);
  mvprintw(6, 0, "Roster average: %d OVR", t.average_overall());

  mvprintw(8, 0, "  %-18s %3s %2s %6s %6s %6s %6s %6s %6s %6s", "NAME", "POS",
           "YR", "OVR", "SPD", "STR", "3PT", "FIN", "HND", "REB");
  mvprintw(9, 0,
           "--------------------------------------------------------------"
           "-----------");

  int row = 10;
  int num = 1;
  for (const auto& p : t.roster) {
    display_player_row(row, num, p);
    row++;
    num++;
  }
  auto counts = t.position_counts();
  mvprintw(row + 1, 0, "Position counts: PG:%d, SG:%d, SF:%d, PF:%d, C:%d",
           counts[0], counts[1], counts[2], counts[3], counts[4]);
  mvprintw(row + 3, 0, "Press any key to return to team list..");
  refresh();
}

int main() {
  init_random();

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Generate teams - mix of prestige levels
  std::vector<Team> teams;

  // Power conference teams (higher prestige)
  for (int i = 0; i < 4; i++) {
    teams.push_back(generate_team(random_int(3, 5), ConferenceTier::Power));
  }

  // Upper-mid teams
  for (int i = 0; i < 4; i++) {
    teams.push_back(generate_team(random_int(2, 4), ConferenceTier::UpperMid));
  }

  // Lower-mid teams
  for (int i = 0; i < 4; i++) {
    teams.push_back(generate_team(random_int(2, 3), ConferenceTier::LowerMid));
  }

  // Low-major teams
  for (int i = 0; i < 4; i++) {
    teams.push_back(generate_team(random_int(1, 2), ConferenceTier::LowMajor));
  }

  bool running = true;
  while (running) {
    display_team_list(teams);

    int ch = getch();
    if (ch == 'q' || ch == 'Q') {
      running = false;
    } else if (ch >= '1' && ch <= '9') {
      int idx = ch - '1';
      if (idx < static_cast<int>(teams.size())) {
        display_team_roster(teams[idx]);
        getch();
      }
    } else if (ch == '0') {
      // '0' = team 10
      if (teams.size() >= 10) {
        display_team_roster(teams[9]);
        getch();
      }
    }
  }

  endwin();
  return 0;
}
