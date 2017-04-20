// a werewolf is a kind of person (but not a kind person!)
class werewolf : public person
{ public:
    werewolf(string nm, place &loc, int thresh)
      : person(nm,loc,thresh) {}
    string get_greeting() const {return greeting;}
    void greeted_by(person *persn)
          {person::greeted_by(persn); eat_person(persn);}
    void greet_others();
    virtual void eat_person(person *prsn);
  private:
    static const string greeting;
};

const string werewolf::greeting = " grrr ... I'm gonna eat you ";

void werewolf::greet_others()
{ string name;
  named_object *pobj;
  for (int i=0; i<location->get_things().size(); i++)
  { pobj =(location->get_things())[i];
    name = pobj->get_name();
    if (pobj->get_kind()==person_obj && name != get_name())
    { cout << get_name() << " says" << greeting << name << endl;
      eat_person(static_cast<person*>(pobj));
    }
  }
}

void werewolf::eat_person(person *persn)
{ cout << get_name() << " devours " << persn->get_name() << endl;
  cout << persn->get_name() <<
       " says it is a far better place i go to " << endl;
  persn->move_to(&heaven);
}