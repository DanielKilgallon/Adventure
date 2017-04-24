// adventure.cpp  a basic text adventure game using objects and inheritance

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int NUM_DIRECTIONS = 6;

enum direction {north, south, east, west, up, down};

string dirstrings[NUM_DIRECTIONS] = {"north","south","east","west","up","down"};

string direction_to_string(direction dir)
{ return dirstrings[dir];
}

direction string_to_direction(string s)
{ for (int i=0; i<NUM_DIRECTIONS; i++)
    if (dirstrings[i]==s)
       return static_cast<direction>(i);
  cout << "Error: invalid string given to string_to_direction";
  exit(1);
}

enum kind {named_obj, thing_obj, place_obj, person_obj};

#include "named_obj.h"
#include "thing.h"
#include "place.h"
#include "person.h"
#include "werewolf.h"

vector<thing*> all_things;
vector<person*> all_people;

void can_go(place &from, direction dir, place &to)
{ from.add_neighbor(dir,&to);
}

void install_thing(thing &thng, place &loc)
{ all_things.push_back(&thng);
  loc.add_thing(&thng);
}

thing *string_to_thing(string s)
{ for (int i=0; i<all_things.size(); i++)
    if (all_things[i]->get_name()==s)
       return all_things[i];
  cout << "Error: invalid string given to string_to_thing";
  exit(1);
}

void install_person(person &persn)
{ all_people.push_back(&persn);
}

void clock()
{ for (int i=0; i<all_people.size(); i++)
    all_people[i]->clock();
}

int main()
{ place mccormick("McCormick Hall Lobby");
  place bakeless("Bakeless Hall Lobby");
  place computer_lab("Computer Lab");
  place basement("Basement");
  place professors_office("Professor's Office");

  //YOU GOT BIG HANDS BOY
  can_go(mccormick,south,bakeless);
  can_go(bakeless,north,mccormick);
  can_go(bakeless,up,computer_lab);
  can_go(computer_lab,down,bakeless);
  can_go(bakeless,down,basement);
  can_go(basement,up,bakeless);
  can_go(mccormick,up,professors_office);
  can_go(professors_office,down,mccormick);

  person me("Erik",mccormick,10000);
  install_person(me);
  person veronica("Veronica",mccormick,2);
  install_person(veronica);
  werewolf cujo("Cujo",basement,3);
  install_person(cujo);

  thing disk("disk");
  install_thing(disk,computer_lab);
  thing beer("beer");
  install_thing(beer,professors_office);

  //main loop
  char line[99];
  string command, arg;
  me.look();

  while (true)
  {  cout << "> ";
     gets(line);
     command = strtok(line," \n");
     if (command == "quit")
       return 0;
     else if (command == "look")
       me.look();
     else if (command == "go")
     {  arg = strtok(NULL," \n");
        me.go_look(string_to_direction(arg));
     }
     else if (command == "take")
     { arg = strtok(NULL," \n");
       me.take(string_to_thing(arg));
     }
	 else if (command == "wait")
       cout << "Time passes" << endl;
     else
       cout << "Unknown command (ignored)." << endl;
     clock();
  }
}