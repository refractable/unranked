// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdint>
#include <string>

// Player positions
enum class Position : std::uint8_t { PG, SG, SF, PF, C };

// Player class
enum class Year : std::uint8_t { Freshman, Sophomore, Junior, Senior };

// Work ethic impacts development of player
enum class WorkEthic : std::uint8_t { Low, Average, High };

// All 16 attributes
struct Attributes {
  // Physical
  int speed;
  int strength;
  int vertical;

  // Shooting
  int three_point;
  int mid_range;
  int finishing;

  // Skills
  int handles;
  int passing;
  int post_game;
  int rebounding;

  // Defense
  int perimeter_d;
  int interior_d;

  // Mental
  int iq;
  int clutch;

  // Meta
  int stamina;
  int potential;
};

struct Player {
  std::string first_name;
  std::string last_name;
  Position position;
  Year year;
  int age;

  Attributes attrs;
  Attributes potential_caps;  // limit for each attribute

  WorkEthic work_ethic;
  int overall;  // is calculated from all attributes

  void calculate_overall();

  // Full name
  [[nodiscard]] std::string full_name() const;

  // Get position from string
  [[nodiscard]] std::string position_str() const;

  // Pull year from string
  [[nodiscard]] std::string year_str() const;
};

Player generate_player(Position pos, Year year, int talent_level);

Player generate_random_player(int talent_level);

#endif  // PLAYER_H_
