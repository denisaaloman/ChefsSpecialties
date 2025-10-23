#pragma once
#include "Repository.h"
#include "Subject.h"
class Service : public Subject {
private:
	Repository& repo;


public:
	Service(Repository& repo) : repo{ repo } {}
	~Service() {}
	vector<Chef*> getchefs() {
		return repo.getallchefs();
	}
	vector<Receipe*> getrecsortedbycuisine();
	vector<Receipe*> getfilteredrec(string cuis);
	void addRec(string name, string cuis,int prepar,vector<string> ingreds);
	vector<Receipe*> getrecipesbyingredients(vector<string> ingredients);





};

