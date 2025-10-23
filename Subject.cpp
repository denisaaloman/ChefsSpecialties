#include "Subject.h"
void Subject::addobserver(Observer* obs) {
	this->observers.push_back(obs);
}
void Subject::notify() {
	for (auto o : this->observers)
		o->update();
}