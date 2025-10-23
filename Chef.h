#pragma once
#include<iostream>
#include<string>

class Chef {
private:
	std::string name, cuisine;
public:
	Chef(std::string name, std::string cuisine): name(name), cuisine(cuisine){}
	~Chef(){}
	std::string getname() {
		return name;
	}
	std::string getcuisine() {
		return cuisine;
	}

};