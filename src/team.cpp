// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#include "team.h"  // NOLINT(build/include_subdir)

#include <algorithm>
#include <vector>
#include <string>

#include "names.h"  // NOLINT(build/include_subdir)

namespace {

// School name components
const std::vector<std::string> school_prefixes = {
    "University of", "State University of", "", "", "", "", ""
};

const std::vector<std::string> school_names = {
    "Northern",      "Eastern",      "Southern",      "Western",
    "Central",       "Northeastern", "Northwestern",  "Southeastern",
    "Southwestern",  "Coastal",      "Mountain",      "Valley",
    "Lake",          "River",        "Canyon",        "Highland",
    "Midland",       "Atlantic",     "Pacific",       "Prairie",
    "Desert",        "Forest",       "Woodland",      "Bayou",
    "Delta",         "Glacier",      "Mesa",          "Peninsula",
    "Island",        "Piedmont",     "Tidewater",     "Bluegrass",
    "Forest",        "Hill",         "Valley",        "Plain",
    "Hills",         "Mount",        "Gorge",         "Oak",
    "Pine",          "Cedar",        "Maple",         "Willow",
    "Birch",         "Aspen",        "Redwood",       "Sycamore",
    "Magnolia",      "Dogwood",      "Cypress",       "Bay",
    "Harbor",        "Port",         "Creek",         "Springs",
    "Falls",         "Brook",        "Lakeside",      "Riverside",
    "Oceanside",     "Bayside",      "Clearwater",    "Ridge",
    "Summit",        "Peak",         "Bluff",         "Cliff",
    "Crest",         "Heights",      "Hollow",        "Grove",
    "Meadow",        "Glen",         "Dale",          "Metro",
    "Capital",       "Bridge",       "Crossroads",    "Gateway",
    "Junction",      "Midtown",      "Uptown",        "Downtown",
    "Parkway",       "Boulevard",    "Heritage",      "Liberty",
    "Union",         "Trinity",      "Victory",       "Horizon",
    "Frontier",      "Pioneer",      "Freedom",       "Independence",
    "Progress",      "Concord",      "Harmony",       "Unity",
    "Providence",    "Faith",        "Hope",          "Colonial",
    "National",      "American",     "Federal",       "Republic",
    "Continental",   "Founding",     "Revolutionary", "Presidential",
    "Golden",        "Silver",       "Iron",          "Stone",
    "Copper",        "Bronze",       "Steel",         "Crimson",
    "Scarlet",       "Azure",        "Emerald",       "Amber",
    "Ivory",         "North Star",   "Polar",         "Southern Cross",
    "Morning Star",  "Appalachian",  "Ozark",         "Cascadia",
    "Acadia",        "Allegheny",    "Shenandoah",    "Cumberland",
    "Chattahoochee", "Chesapeake",   "Susquehanna",   "Monongahela",
    "Rappahannock",  "Roanoke",
};

const std::vector<std::string> school_suffixes = {
  "State", "University", "College", "Tech",
  "A&M", "Institute", "Poly", "Baptist",
  "Methodist", "Christian", "Catholic", "Lutheran", "Presbyterian",
  "", "", "", ""
};

const std::vector<std::string> nicknames = {
    "Tigers",       "Lions",        "Panthers",      "Cougars",
    "Wildcats",     "Bobcats",      "Jaguars",       "Leopards",
    "Cheetahs",     "Lynx",         "Pumas",         "Ocelots",
    "Bears",        "Grizzlies",    "Bruins",        "Kodiaks",
    "Polar Bears",  "Wolves",       "Huskies",       "Bulldogs",
    "Coyotes",      "Foxes",        "Dingoes",       "Wolfpack",
    "Greyhounds",   "Mastiffs",     "Terriers",      "Retrievers",
    "Eagles",       "Hawks",        "Falcons",       "Owls",
    "Ravens",       "Condors",      "Ospreys",       "Kestrels",
    "Harriers",     "Vultures",     "Raptors",       "Cardinals",
    "Bluejays",     "Orioles",      "Robins",        "Pelicans",
    "Seagulls",     "Herons",       "Cranes",        "Swans",
    "Phoenixes",    "Thunderbirds", "Mustangs",      "Stallions",
    "Broncos",      "Colts",        "Chargers",      "Mavericks",
    "Palominos",    "Appaloosas",   "Thoroughbreds", "Bulls",
    "Longhorns",    "Bison",        "Buffalo",       "Brahmas",
    "Toros",        "Matadors",     "Angus",         "Steers",
    "Rams",         "Badgers",      "Wolverines",    "Beavers",
    "Otters",       "Weasels",      "Jackrabbits",   "Razorbacks",
    "Javelinas",    "Armadillos",   "Anteaters",     "Kangaroos",
    "Billikens",    "Musketeers",   "Gorillas",      "Apes",
    "Gators",       "Crocodiles",   "Cobras",        "Vipers",
    "Rattlers",     "Moccasins",    "Copperheads",   "Diamondbacks",
    "Salamanders",  "Horned Frogs", "Sharks",        "Dolphins",
    "Marlins",      "Barracudas",   "Stingrays",     "Hammerheads",
    "Makos",        "Orcas",        "Swordfish",     "Wahoos",
    "Tarpons",      "Hornets",      "Yellowjackets", "Wasps",
    "Bees",         "Scorpions",    "Spiders",       "Fireflies",
    "Monarchs",     "Beetles",      "Knights",       "Warriors",
    "Spartans",     "Trojans",      "Vikings",       "Gladiators",
    "Crusaders",    "Paladins",     "Sentinels",     "Guardians",
    "Defenders",    "Lancers",      "Cavaliers",     "Highlanders",
    "Clan",         "Chieftains",   "Raiders",       "Pirates",
    "Rebels",       "Outlaws",      "Bandits",       "Renegades",
    "Rogues",       "Privateers",   "Buccaneers",    "Marauders",
    "Desperados",   "Pioneers",     "Explorers",     "Trailblazers",
    "Pathfinders",  "Rangers",      "Scouts",        "Frontiersmen",
    "Mountaineers", "Voyageurs",    "Trappers",      "Settlers",
    "Homesteaders", "Sooners",      "Pilgrims",      "Colonials",
    "Miners",       "Oilers",       "Steelers",      "Ironmen",
    "Loggers",      "Lumberjacks",  "Drillers",      "Roughnecks",
    "Railroaders",  "Rivermen",     "Dockers",       "Foundry",
    "Millwrights",  "Boilermakers", "Welders",       "Storm",
    "Thunder",      "Lightning",    "Blaze",         "Inferno",
    "Flames",       "Avalanche",    "Cyclones",      "Hurricanes",
    "Tornadoes",    "Typhoons",     "Tsunami",       "Earthquakes",
    "Volcanoes",    "Blizzard",     "Heatwave",      "Rockets",
    "Comets",       "Meteors",      "Asteroids",     "Stars",
    "Suns",         "Moons",        "Cosmos",        "Nebulas",
    "Galaxies",     "Novas",        "Satellites",    "Crimson Tide",
    "Scarlet Knights", "Golden Bears", "Blue Devils", "Green Wave",
    "Red Storm",    "Orange Crush", "Purple Aces",   "Black Knights",
    "Silver Hawks", "Maroon Tigers", "Navy Midshipmen", "Roadrunners"
};

const std::vector<std::string> cities = {
  "Springfield", "Franklin", "Clinton", "Madison",
  "Georgetown", "Bristol", "Fairview", "Salem",
  "Manchester", "Newport", "Ashland", "Burlington",
  "Lexington", "Milton", "Oakland", "Riverside",
  "Cleveland", "Kingston", "Arlington", "Winchester",
  "Auburn", "Greenville", "Marion", "Columbia",
  "Plymouth", "Jackson", "Monroe", "Hamilton",
  "Warren", "Chester", "Troy", "Hudson",
  "Dover", "Oxford", "Cambridge", "Princeton",
  "Dayton", "Canton", "Akron", "Toledo",
  "Lansing", "Flint", "Saginaw", "Kalamazoo",
  "Pontiac", "Savannah", "Charleston", "Asheville",
  "Raleigh", "Durham", "Chapel Hill", "Knoxville",
  "Chattanooga", "Nashville", "Memphis", "Birmingham",
  "Montgomery", "Mobile", "Huntsville", "Tuscaloosa",
  "Baton Rouge", "Shreveport", "Lafayette", "Lake Charles",
  "Tallahassee", "Gainesville", "Pensacola", "Jacksonville",
  "Tampa", "Des Moines", "Cedar Rapids", "Sioux Falls",
  "Fargo", "Bismarck", "Omaha", "Lincoln",
  "Topeka", "Wichita", "Lawrence", "Kansas City",
  "St. Joseph", "Springfield", "Joplin", "Columbia",
  "Bloomington", "Champaign", "Peoria", "Rockford",
  "Decatur", "Tucson", "Flagstaff", "Tempe",
  "Mesa", "Scottsdale", "Albuquerque", "Santa Fe",
  "Las Cruces", "El Paso", "Lubbock", "Amarillo",
  "Midland", "Odessa", "Abilene", "Waco",
  "Boise", "Spokane", "Tacoma", "Olympia",
  "Bellingham", "Eugene", "Salem", "Bend",
  "Medford", "Corvallis", "Reno", "Carson City",
  "Henderson", "Boulder City", "Provo", "Ogden",
  "Logan", "St. George", "Cedar City", "Hartford",
  "New Haven", "Stamford", "Providence", "Warwick",
  "Worcester", "Lowell", "Brockton", "Quincy",
  "Lynn", "Portland", "Bangor", "Augusta",
  "Concord", "Nashua", "Burlington", "Montpelier",
  "Rutland", "Syracuse", "Rochester", "Buffalo",
  "Albany", "Utica", "Binghamton", "Ithaca",
  "Harrisburg", "Pittsburgh", "Scranton", "Allentown",
  "Erie", "Reading", "Lancaster", "York",
  "Wilmington", "Newark", "Trenton", "Camden",
  "Atlantic City", "Princeton", "Hoboken", "Denver",
  "Boulder", "Fort Collins", "Colorado Springs", "Pueblo",
  "Cheyenne", "Laramie", "Casper", "Billings",
  "Missoula", "Helena", "Great Falls", "Bozeman", "Butte"
};

const std::vector<std::string> states = {
    "AL", "AZ", "AR", "CA", "CO", "CT", "DE", "FL", "GA", "ID", "IL", "IN",
    "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO", "MT",
    "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA",
    "RI", "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY"
};

}  // namespace

std::string Team::full_name() const { return name + " " + nickname; }

std::array<int, 5> Team::position_counts() const {
  std::array<int, 5> counts = {0, 0, 0, 0, 0};
  for (const auto& p : roster) {
    counts[static_cast<int>(p.position)]++;
  }
  return counts;
}

int Team::average_overall() const {
  if (roster.empty()) {
    return 0;
  }
  int sum = 0;
  for (const auto& p : roster) {
    sum += p.overall;
  }
  return sum / static_cast<int>(roster.size());
}

void Team::sort_roster() {
  std::sort(roster.begin(), roster.end(), [](const Player& a, const Player& b) {
    if (a.position != b.position) {
      return static_cast<int>(a.position) < static_cast<int>(b.position);
    }
    return a.overall > b.overall;  // Higher overall first within position
  });
}

std::string generate_team_name() {
  std::string result;

  // picks a prefix
  const auto& prefix = school_prefixes[random_int(
      0, static_cast<int>(school_prefixes.size()) - 1)];

  // picks a name
  const auto& name =
      school_names[random_int(0, static_cast<int>(school_names.size()) - 1)];

  const auto& suffix = school_suffixes[random_int(
      0, static_cast<int>(school_suffixes.size()) - 1)];

  if (!prefix.empty()) {
    result = prefix + " " + name;
  } else if (!suffix.empty()) {
    result = name + " " + suffix;
  } else {
    result = name + " State";  // Fallback
  }

  return result;
}

std::string generate_nickname() {
  return nicknames[random_int(0, static_cast<int>(nicknames.size()) - 1)];
}

std::string generate_location() {
  const auto& city = cities[random_int(0, static_cast<int>(cities.size()) - 1)];
  const auto& state =
      states[random_int(0, static_cast<int>(states.size()) - 1)];

  return city + ", " + state;
}

Team generate_team(int prestige_level, ConferenceTier tier) {
  Team t;

  // Generate identity
  t.name = generate_team_name();
  t.nickname = generate_nickname();
  t.location = generate_location();

  // Set program attributes based on prestige (1-5 scale, 1-100 output)
  int base_prestige = (prestige_level * 20) - 10;  // 10, 30, 50, 70, 90
  t.prestige = std::clamp(base_prestige + random_int(-10, 10), 1, 100);
  t.facilities = std::clamp(base_prestige + random_int(-15, 15), 1, 100);
  t.budget = std::clamp(base_prestige + random_int(-15, 15), 1, 100);

  // Conferences
  t.conference_tier = tier;
  t.conference_name = "";

  // Season record
  t.wins = 0;
  t.losses = 0;

  // Generate roster - 13 players
  // Typically should be 2 PG, 2-3 SG, 2-3 SF, 2-3 PF, 2 C
  // Talent based on prestige: higher prestige = better recruits

  // Determines distribution of talent based on prestige
  // prestige_level 5 = mostly 4-5 star players and so on

  auto roll_talent = [prestige_level]() {
    int roll = random_int(1, 100);
    int base = prestige_level;

    if (roll <= 10) {
      return std::clamp(base + 2, 1, 5);  // Occasional star
    }
    if (roll <= 30) {
      return std::clamp(base + 1, 1, 5);
    }
    if (roll <= 70) {
      return std::clamp(base, 1, 5);
    }
    if (roll <= 90) {
      return std::clamp(base - 1, 1, 5);
    }
    return std::clamp(base - 2, 1, 5);  // Occasional project
  };

  // Position targets
  struct PosTarget {
    Position pos;
    int count;
  };

  std::vector<PosTarget> targets = {
    {Position::PG, 2},
    {Position::SG, random_int(2, 3)},
    {Position::SF, random_int(2, 3)},
    {Position::PF, random_int(2, 3)},
    {Position::C, 2}
  };

  // Fill roster
  for (const auto& target : targets) {
    for (int i = 0; i < target.count; i++) {
      // Mix up years, weighting towards underclassmen
      Year year;
      int year_roll = random_int(1, 10);
      if (year_roll <= 3) {
        year = Year::Freshman;
      } else if (year_roll <= 6) {
        year = Year::Sophomore;
      } else if (year_roll <= 8) {
        year = Year::Junior;
      } else {
        year = Year::Senior;
      }

      int talent = roll_talent();
      t.roster.push_back(generate_player(target.pos, year, talent));
    }
  }

  while (static_cast<int>(t.roster.size()) < 13) {
    auto pos = static_cast<Position>(random_int(0, 4));
    auto year = static_cast<Year>(random_int(0, 3));
    t.roster.push_back(generate_player(pos, year, roll_talent()));
  }

  t.sort_roster();

  return t;
}
