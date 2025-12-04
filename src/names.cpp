// Copyright 2025 refractable
// SPDX-License-Identifier: PolyForm-Noncommercial-1.0.0

#include "names.h"   // NOLINT(build/include_subdir)

#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

namespace {

// First name pool
const std::vector<std::string> first_names = {
    "James",       "Michael",  "David",    "Robert",   "William",   "John",
    "Christopher", "Anthony",  "Richard",  "Charles",  "Joseph",    "Thomas",
    "Matthew",     "Daniel",   "Paul",     "Mark",     "Donald",    "Steven",
    "Andrew",      "Kenneth",  "Joshua",   "Kevin",    "Brian",     "George",
    "Timothy",     "Ronald",   "Edward",   "Jason",    "Jeffrey",   "Ryan",
    "Jacob",       "Gary",     "Nicholas", "Eric",     "Jonathan",  "Stephen",
    "Larry",       "Justin",   "Scott",    "Brandon",  "Benjamin",  "Samuel",
    "Raymond",     "Gregory",  "Frank",    "Patrick",  "Jack",      "Dennis",
    "Jerry",       "Tyler",    "Aaron",    "Jose",     "Adam",      "Nathan",
    "Henry",       "Douglas",  "Zachary",  "Peter",    "Kyle",      "Walter",
    "Ethan",       "Jeremy",   "Harold",   "Keith",    "Christian", "Roger",
    "Noah",        "Gerald",   "Carl",     "Terry",    "Sean",      "Austin",
    "Arthur",      "Lawrence", "Jesse",    "Dylan",    "Bryan",     "Joe",
    "Jordan",      "Billy",    "Bruce",    "Albert",   "Willie",    "Gabriel",
    "Logan",       "Alan",     "Juan",     "Wayne",    "Elijah",    "Randy",
    "Roy",         "Vincent",  "Ralph",    "Eugene",   "Russell",   "Bobby",
    "Mason",       "Philip",   "Louis",    "Harry",    "Caleb",     "Isaac",
    "Craig",       "Marcus",   "Cameron",  "Connor",   "Evan",      "Cody",
    "Blake",       "Derek",    "Trevor",   "Trey",     "Cole",      "Chase",
    "Grant",       "Garrett",  "Spencer",  "Mitchell", "Dalton",    "Colby",
    "Dustin",      "Brett",    "Shane",    "Troy",     "Corey",     "Seth",
    "Jake",        "Nate",     "Luke",     "Drew",     "Alex",      "Max",
    "Ben",         "Sam",      "Chris",    "Mike",     "Matt",      "Nick",
    "Tony",        "Danny",    "Tommy",    "Bobby",    "Jimmy",     "Johnny",
    "Eddie",       "Freddie",  "Ronnie",   "Ricky",    "Billy",     "Joey",
    "Frankie",     "Ray",      "DeShawn",  "Terrence", "Jamal",     "Darius",
    "Dante",       "Damian",   "Donovan",  "Dwight",   "Derrick",   "Devin",
    "Devon",       "Tyrone",   "Tyrell",   "Jermaine", "Malik",     "Maurice",
    "Rashad",      "Rasheed",  "Lamar",    "Lamont",   "Darnell",   "Marquis",
    "Jerome",      "Reggie",   "Kareem",   "Cedric",   "Terrell",   "Kendrick",
    "Desmond",     "Rodney",   "Vernon",   "Marvin",   "Melvin",    "Calvin",
    "Alvin",       "Kelvin",   "Leroy",    "Percy",    "Clyde",     "Andre",
    "Avery",       "Jalen",    "Jaylen",   "Jayson",   "Javon",     "Quincy",
    "Omar",        "Xavier",   "Isaiah",   "Elijah",   "Malcolm",   "Clifford",
    "Clarence",    "Leon",     "Wendell",  "Reginald", "Carlos",    "Luis",
    "Miguel",      "Jose",     "Antonio",  "Juan",     "Angel",     "Diego",
};

const std::vector<std::string> last_names = {
    "Smith",      "Johnson",    "Williams", "Brown",     "Jones",
    "Garcia",     "Miller",     "Davis",    "Rodriguez", "Martinez",
    "Hernandez",  "Lopez",      "Gonzalez", "Wilson",    "Anderson",
    "Thomas",     "Taylor",     "Moore",    "Jackson",   "Martin",
    "Lee",        "Perez",      "Thompson", "White",     "Harris",
    "Sanchez",    "Clark",      "Ramirez",  "Lewis",     "Robinson",
    "Walker",     "Young",      "Allen",    "King",      "Wright",
    "Scott",      "Torres",     "Nguyen",   "Hill",      "Flores",
    "Green",      "Adams",      "Nelson",   "Baker",     "Hall",
    "Rivera",     "Campbell",   "Mitchell", "Carter",    "Roberts",
    "Gomez",      "Phillips",   "Evans",    "Turner",    "Diaz",
    "Parker",     "Cruz",       "Edwards",  "Collins",   "Reyes",
    "Stewart",    "Morris",     "Morales",  "Murphy",    "Cook",
    "Rogers",     "Gutierrez",  "Ortiz",    "Morgan",    "Cooper",
    "Peterson",   "Bailey",     "Reed",     "Kelly",     "Howard",
    "Ramos",      "Kim",        "Cox",      "Ward",      "Richardson",
    "Watson",     "Brooks",     "Chavez",   "Wood",      "James",
    "Bennett",    "Gray",       "Mendoza",  "Ruiz",      "Hughes",
    "Price",      "Alvarez",    "Castillo", "Sanders",   "Patel",
    "Myers",      "Long",       "Ross",     "Foster",    "Jimenez",
    "Powell",     "Jenkins",    "Perry",    "Russell",   "Sullivan",
    "Bell",       "Coleman",    "Butler",   "Henderson", "Barnes",
    "Gonzales",   "Fisher",     "Vasquez",  "Simmons",   "Stokes",
    "Simpson",    "Patterson",  "Jordan",   "Reynolds",  "Hamilton",
    "Graham",     "Freeman",    "Wells",    "Webb",      "Washington",
    "Tucker",     "Burns",      "Henry",    "Crawford",  "Owens",
    "Stone",      "Cole",       "Lucas",    "Warren",    "Dixon",
    "Gibson",     "Hayes",      "Wallace",  "Kennedy",   "Mcdonald",
    "Hunt",       "Mills",      "Berry",    "Olson",     "Knight",
    "Ferguson",   "Rose",       "Stone",    "Hawkins",   "Dunn",
    "Perkins",    "Hudson",     "Spencer",  "Gardner",   "Stephens",
    "Payne",      "Pierce",     "Berry",    "Matthews",  "Arnold",
    "Wagner",     "Willis",     "Ray",      "Watkins",   "Grant",
    "Meyer",      "Boyd",       "Rice",     "Moreno",    "Mason",
    "Dean",       "Ford",       "Hanson",   "Carr",      "Harvey",
    "Palmer",     "Duncan",     "Fletcher", "Walsh",     "West",
    "Gibson",     "Elliott",    "Fox",      "Lawrence",  "Garrett",
    "Burton",     "Hicks",      "Black",    "Robertson", "Gordon",
    "Blake",      "Snyder",     "Holland",  "Gregory",   "Silva",
    "Park",       "Soto",       "Mann",     "Harper",    "Bates",
    "Ortega",     "Delgado",    "Medina",   "Lane",      "Chang",
    "Craig",      "Franklin",   "Holt",     "Lopez",     "Chandler",
    "Wolfe",      "Daniels",    "Webb",     "Herrera",   "Moss",
    "Monroe",     "Sutton",     "Benson",   "Dawson",    "Sharp",
    "Figueroa",   "Klein",      "Pearson",  "Valdez",    "Wise",
    "Briggs",     "Doyle",      "Swanson",  "Moran",     "Vega",
    "Curry",      "Frank",      "Frazier",  "Ball",      "Norman",
    "Reese",      "Page",       "Wong",     "Thornton",  "Summers",
    "Odom",       "Boone",      "Weeks",    "Hines",     "Love",
    "Ware",       "Allison",    "Vargas",   "Contreras", "Rojas",
    "Campos",     "Guerrero",   "Sandoval", "Nunez",     "Escobar",
    "Villarreal", "Mejia",      "Rios",     "Ibarra",    "Marquez",
    "Padilla",    "Velazquez",  "Trujillo", "Oconnor",   "Obrien",
    "Oneill",     "Casey",      "Brennan",  "Gallagher", "Quinn",
    "Murray",     "Burke",      "Lynch",    "Duffy",     "Donnelly",
    "Callahan",   "Fitzgerald", "Malone",   "Mahoney",   "Mosley",
    "Gaines",     "Booker",     "Beasley",  "Poole",     "Mcgee",
    "Jennings",   "Richmond",   "Mercer",   "Monroe",    "Waller",
    "Barton",     "Livingston", "Ingram",   "Bridges",   "Wiggins",
};

}  // namespace

void init_random() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
}

int random_int(int min, int max) {
  return min + (std::rand() % (max - min + 1));
}

std::string random_first_name() {
  int index = random_int(0, static_cast<int>(first_names.size()) - 1);
  return first_names[index];
}

std::string random_last_name() {
  int index = random_int(0, static_cast<int>(last_names.size()) - 1);
  return last_names[index];
}
