#include "Repository.h"
#include<fstream>
#include<algorithm>
#include<sstream>

void Repository::loadfiles() {
	ifstream fin("chefs.txt");
	string line;
	while (getline(fin, line)) {
		istringstream iss(line);
		string name, cusine;
		getline(iss, name, '|');
		getline(iss, cusine);
		this->chefs.push_back(new Chef(name, cusine));

	}

	ifstream fin2("recipes.txt");
	string line2;
	while (getline(fin2, line2)) {
		istringstream iss(line2);
		string name, cusine, prep, ingred;

		getline(iss, name, '|');
		getline(iss, cusine, '|');
		getline(iss, prep, '|');
		int prep2 = stoi(prep);

		getline(iss, ingred);

		istringstream iss2(ingred);
		string ingredient;
		vector<string> ingreds;
		while (iss2 >> ingredient) {
			ingreds.push_back(ingredient);
		}
		this->receipes.push_back(new Receipe(name, cusine, prep2, ingreds));

		


	}
	
	fin2.close();
}



void Repository::savefile() {
	ofstream fout("saved.txt");
	vector<Receipe*> sortedrecipes = this->receipes;
	sort(sortedrecipes.begin(), sortedrecipes.end(), [&](Receipe* a, Receipe* b) {
		if (a->getRecCuis() == b->getRecCuis())
			return a->getprep() < b->getprep();
		return a->getRecCuis() < b->getRecCuis();
		});

	for (auto r : sortedrecipes) {
		fout << r->getRecName() << "|" << r->getRecCuis() << "|" << r->getprep() << "|";
        vector<string> ingredients = r->getingred();
		for (int i = 0; i < ingredients.size(); ++i) {
			fout << ingredients[i] << " ";
		}
		fout << "\n";
	}

	fout.close();
}


Repository::Repository() {
	this->loadfiles();

}

Repository::~Repository() {
	this->savefile();

}


















