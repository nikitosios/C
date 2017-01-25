#ifndef HUMAN_H
#define HUMAN_H

#include <string>

using namespace std;

class Human {
	public:
		string name;
		unsigned char age;
		Human () {
			this->name = "Вася";
			this->age = 20;
		}
		Human (string name) {
			this->name = name;
			this->age = 20;
		}
		Human (string name, unsigned char age) {
			this->name = name;
			this->age = age;
		}
		~Human () {
			cout << this->name << " убит..." << endl;
		}
		void say (string msg) {
			cout << this->name << ": " << msg << endl;
		}
};

#endif
