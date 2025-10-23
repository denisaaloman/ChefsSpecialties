#pragma once
#include<iostream>
#include<string>
#include<vector>

class Receipe {
private:
	std::string name, cuisine;
	int prep;
	std::vector<std::string> ingredients;
public:
	Receipe(std::string name, std::string cui, int prep, std::vector<std::string> ing): name{name}, cuisine{cui},prep{prep}, ingredients{ing}{}
	~Receipe(){}
	std::string getRecName() {
		return name;
	}
	std::string getRecCuis() {
		return cuisine;
	}
	int getprep() {
		return prep;
	}
	std::vector<std::string> getingred() {
		return ingredients;
	}


};