// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#include "player.h"  // NOLINT(build/include_subdir)

#include <algorithm>
#include <string>

#include "names.h"  // NOLINT(build/include_subdir)

std::string Player::full_name() const { return first_name + " " + last_name; }

std::string Player::position_str() const {
  switch (position) {
    case Position::PG:
      return "PG";
    case Position::SG:
      return "SG";
    case Position::SF:
      return "SF";
    case Position::PF:
      return "PF";
    case Position::C:
      return "C";
  }
  return "??";
}

std::string Player::year_str() const {
  switch (year) {
    case Year::Freshman:
      return "Fr";
    case Year::Sophomore:
      return "So";
    case Year::Junior:
      return "Jr";
    case Year::Senior:
      return "Sr";
  }
  return "??";
}

void Player::calculate_overall() {
  // Weight attributes based on position
  int sum = 0;

  switch (position) {
    case Position::PG:
      // Point guards: handling, passing, speed, iq matter most here
      sum = (attrs.handles * 3) + (attrs.passing * 3) + (attrs.speed * 2) +
            (attrs.iq * 2) + (attrs.three_point * 2) + (attrs.perimeter_d * 2) +
            attrs.mid_range + attrs.finishing + attrs.clutch;
      overall = sum / 17;
      break;

    case Position::SG:
      // Shooting guards: shooting, handling, perimeter defense
      sum = (attrs.three_point * 3) + (attrs.mid_range * 2) +
            (attrs.handles * 2) + (attrs.finishing * 2) +
            (attrs.perimeter_d * 2) + (attrs.speed * 2) + attrs.passing +
            attrs.iq + attrs.clutch;
      overall = sum / 17;
      break;

    case Position::SF:
      // Small forwards: versatility
      sum = (attrs.finishing * 2) + (attrs.three_point * 2) +
            (attrs.mid_range * 2) + (attrs.perimeter_d * 2) +
            (attrs.rebounding * 2) + attrs.speed + attrs.strength +
            attrs.handles + attrs.iq + attrs.vertical;
      overall = sum / 16;
      break;

    case Position::PF:
      // Power forwards: inside game, rebounding, strength
      sum = (attrs.rebounding * 3) + (attrs.finishing * 2) +
            (attrs.post_game * 2) + (attrs.strength * 2) +
            (attrs.interior_d * 2) + (attrs.vertical * 2) + attrs.mid_range +
            attrs.iq;
      overall = sum / 15;
      break;

    case Position::C:
      // Centers: interior everything man
      sum = (attrs.interior_d * 3) + (attrs.rebounding * 3) +
            (attrs.post_game * 2) + (attrs.strength * 2) +
            (attrs.vertical * 2) + (attrs.finishing * 2) + attrs.iq;
      overall = sum / 15;
      break;
  }

  overall = std::clamp(overall, 1, 99);
}

// Helper function to generate attribute in range based on talent
static int gen_attr(int talent_level, int base_min, int base_max) {
  // Talent level impacts range
  // 1 star: roughly 30-50
  // 2 star: rough 45-70
  // 3 star: 65-90
  // you get the idea

  int shift = (talent_level - 1) * 10;
  int min_val = base_min + shift;
  int max_val = base_max + shift;

  // randomness
  int value = random_int(min_val, max_val);

  // clamp for range
  return std::clamp(value, 25, 95);
}

static int gen_potential(int current, int talent_level) {
  // Higher talent means higher ceiling
  int growth_range = 10 + (talent_level * 5);  // 15-35 points of growth
  int potential = current + random_int(5, growth_range);
  return std::clamp(potential, current, 99);
}

Player generate_player(Position pos, Year year, int talent_level) {
  Player p;

  // basic info
  p.first_name = random_first_name();
  p.last_name = random_last_name();
  p.position = pos;
  p.year = year;

  // Age based on year (roughly)
  switch (year) {
    case Year::Freshman:
      p.age = random_int(18, 19);
      break;
    case Year::Sophomore:
      p.age = random_int(19, 20);
      break;
    case Year::Junior:
      p.age = random_int(20, 21);
      break;
    case Year::Senior:
      p.age = random_int(21, 23);
      break;
  }

  // Work ethic (weighted towards avg)
  int ethic_roll = random_int(1, 10);
  if (ethic_roll <= 2) {
    p.work_ethic = WorkEthic::Low;
  } else if (ethic_roll <= 8) {
    p.work_ethic = WorkEthic::Average;
  } else {
    p.work_ethic = WorkEthic::High;
  }

  // Generate base attributes
  // (typically 30-55 range for base, talent impacts it)
  p.attrs.speed = gen_attr(talent_level, 30, 55);
  p.attrs.strength = gen_attr(talent_level, 30, 55);
  p.attrs.vertical = gen_attr(talent_level, 30, 55);
  p.attrs.three_point = gen_attr(talent_level, 25, 50);
  p.attrs.mid_range = gen_attr(talent_level, 30, 55);
  p.attrs.finishing = gen_attr(talent_level, 30, 55);
  p.attrs.passing = gen_attr(talent_level, 30, 55);
  p.attrs.post_game = gen_attr(talent_level, 25, 50);
  p.attrs.rebounding = gen_attr(talent_level, 30, 55);
  p.attrs.perimeter_d = gen_attr(talent_level, 30, 55);
  p.attrs.interior_d = gen_attr(talent_level, 30, 55);
  p.attrs.iq = gen_attr(talent_level, 30, 60);
  p.attrs.handles = gen_attr(talent_level, 30, 55);
  p.attrs.clutch = gen_attr(talent_level, 30, 55);
  p.attrs.stamina = gen_attr(talent_level, 40, 65);
  p.attrs.potential = gen_attr(talent_level, 40, 70);

  switch (pos) {
    case Position::PG:
      p.attrs.handles += random_int(5, 15);
      p.attrs.passing += random_int(5, 15);
      p.attrs.speed += random_int(3, 10);
      p.attrs.iq += random_int(3, 10);
      break;

    case Position::SG:
      p.attrs.three_point += random_int(5, 15);
      p.attrs.mid_range += random_int(5, 12);
      p.attrs.speed += random_int(3, 10);
      break;

    case Position::SF:
      p.attrs.finishing += random_int(3, 10);
      p.attrs.rebounding += random_int(3, 8);
      p.attrs.perimeter_d += random_int(3, 8);
      break;

    case Position::PF:
      p.attrs.rebounding += random_int(5, 15);
      p.attrs.strength += random_int(5, 12);
      p.attrs.post_game += random_int(3, 10);
      p.attrs.interior_d += random_int(3, 10);
      break;

    case Position::C:
      p.attrs.rebounding += random_int(5, 15);
      p.attrs.interior_d += random_int(5, 15);
      p.attrs.strength += random_int(5, 15);
      p.attrs.post_game += random_int(5, 12);
      // Centers are usually slow
      p.attrs.speed -= random_int(5, 15);
      p.attrs.handles -= random_int(5, 10);
      break;
  }

  // clamp all attributes to range
  p.attrs.speed = std::clamp(p.attrs.speed, 25, 99);
  p.attrs.strength = std::clamp(p.attrs.strength, 25, 99);
  p.attrs.vertical = std::clamp(p.attrs.vertical, 25, 99);
  p.attrs.three_point = std::clamp(p.attrs.three_point, 25, 99);
  p.attrs.mid_range = std::clamp(p.attrs.mid_range, 25, 99);
  p.attrs.finishing = std::clamp(p.attrs.finishing, 25, 99);
  p.attrs.passing = std::clamp(p.attrs.passing, 25, 99);
  p.attrs.post_game = std::clamp(p.attrs.post_game, 25, 99);
  p.attrs.rebounding = std::clamp(p.attrs.rebounding, 25, 99);
  p.attrs.perimeter_d = std::clamp(p.attrs.perimeter_d, 25, 99);
  p.attrs.interior_d = std::clamp(p.attrs.interior_d, 25, 99);
  p.attrs.iq = std::clamp(p.attrs.iq, 25, 99);
  p.attrs.handles = std::clamp(p.attrs.handles, 25, 99);
  p.attrs.clutch = std::clamp(p.attrs.clutch, 25, 99);
  p.attrs.stamina = std::clamp(p.attrs.stamina, 25, 99);
  p.attrs.potential = std::clamp(p.attrs.potential, 25, 99);

  // generate potential caps
  p.potential_caps.speed = gen_potential(p.attrs.speed, talent_level);
  p.potential_caps.strength = gen_potential(p.attrs.strength, talent_level);
  p.potential_caps.vertical = gen_potential(p.attrs.vertical, talent_level);
  p.potential_caps.three_point =
      gen_potential(p.attrs.three_point, talent_level);
  p.potential_caps.mid_range = gen_potential(p.attrs.mid_range, talent_level);
  p.potential_caps.finishing = gen_potential(p.attrs.finishing, talent_level);
  p.potential_caps.passing = gen_potential(p.attrs.passing, talent_level);
  p.potential_caps.post_game = gen_potential(p.attrs.post_game, talent_level);
  p.potential_caps.rebounding = gen_potential(p.attrs.rebounding, talent_level);
  p.potential_caps.perimeter_d =
      gen_potential(p.attrs.perimeter_d, talent_level);
  p.potential_caps.interior_d = gen_potential(p.attrs.interior_d, talent_level);
  p.potential_caps.iq = gen_potential(p.attrs.iq, talent_level);
  p.potential_caps.handles = gen_potential(p.attrs.handles, talent_level);
  p.potential_caps.clutch = gen_potential(p.attrs.clutch, talent_level);
  p.potential_caps.stamina = gen_potential(p.attrs.stamina, talent_level);
  p.potential_caps.potential = p.attrs.potential;  // meta stays same always

  p.calculate_overall();

  return p;
}

Player generate_random_player(int talent_level) {
  // Random position
  auto pos = static_cast<Position>(random_int(0, 4));

  // Random year (weighted towards underclassmen)
  Year year;
  int year_roll = random_int(1, 10);
  if (year_roll <= 4) {
    year = Year::Freshman;
  } else if (year_roll <= 7) {
    year = Year::Sophomore;
  } else if (year_roll <= 9) {
    year = Year::Junior;
  } else {
    year = Year::Senior;
  }

  return generate_player(pos, year, talent_level);
}
