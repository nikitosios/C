#ifndef SON_H
#define SON_H

#include <string>
#include "human.hpp"

using namespace std;

class Son : public Human {
	public:
		string parent;
		Son (Human *parent) {
			this->parent = parent->name;
			this->name = "Петя";
			this->age = 0;
			parent->say("у меня родился сын!");
			this->say("агу!");
		}
		Son (Human *parent, string name) {
			this->parent = parent->name;
			this->name = name;
			this->age = 0;
			parent->say("у меня родился сын!");
			this->say("агу!");
		}
};

#endif
