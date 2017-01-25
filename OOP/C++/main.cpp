#include <iostream>
#include <string>
#include "human.hpp"
#include "son.hpp"

using namespace std;

int main ()
{
	Human *vasya = new Human ();
	cout << vasya->name << " уже вырос до " << (int) vasya->age << " лет." << endl;
	vasya->say("привет!");
	Son *vasyaSon = new Son (vasya);
	delete vasya;
}
