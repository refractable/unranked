// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#ifndef TEAM_H_
#define TEAM_H_

#include <array>
#include <string>
#include <vector>

#include "player.h"  // NOLINT(build/include_subdir)

// Conference tier impacts schedules, tournament bids, and recruiting
enum class ConferenceTier : std::uint8_t {
  Power,     // Elite conferences, 5-8 tournament bids
  UpperMid,  // Solid conferences, 2-4 bids
  LowerMid,  // Only one good team typically, 1-2 bids
  LowMajor,  // Autobid only
};

// Team identity and resources
struct Team {
  // Identity
  std::string name;      // ex: "State University"
  std::string nickname;  // ex: "Bears"
  std::string location;  // ex: "Columbus, OH"

  // Roster (13 players typically)
  std::vector<Player> roster;

  // Program power (1-100)
  int prestige;
  int facilities;
  int budget;

  // Conference info
  ConferenceTier conference_tier;
  std::string conference_name;

  // Season record
  int wins;
  int losses;

  [[nodiscard]] std::string full_name() const;

  // Get player count for each pos
  [[nodiscard]] std::array<int, 5> position_counts() const;

  [[nodiscard]] int average_overall() const;

  void sort_roster();
};

Team generate_team(int prestige_level, ConferenceTier tier);

[[nodiscard]] std::string generate_team_name();
[[nodiscard]] std::string generate_nickname();
[[nodiscard]] std::string generate_location();

#endif  // TEAM_H_
