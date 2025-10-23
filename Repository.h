#pragma once
#include<iostream>
#include "Receipe.h"
#include "Chef.h"
#include<vector>
using namespace std;

class Repository {
private:
	vector<Receipe*> receipes;
	vector<Chef*> chefs;
public:
	Repository();
	~Repository();
	void savefile();
	void loadfiles();
	vector<Receipe*> getallrec() {
		return receipes;
	}
	vector<Chef*> getallchefs() {
		return chefs;
	}
	void add(Receipe* rec) {
		receipes.push_back(rec);
	}





};