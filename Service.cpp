#include "Service.h"
#include<algorithm>
#include<set>

vector<Receipe*> Service::getrecsortedbycuisine()
{
	vector<Receipe*> allrec = this->repo.getallrec();
	sort(allrec.begin(), allrec.end(), [&](Receipe* r1, Receipe* r2) {
		return r1->getRecCuis() < r2->getRecCuis();
		});
	return allrec;
}

vector<Receipe*> Service::getfilteredrec(string cuis)
{
	vector<Receipe*> allrec = this->getrecsortedbycuisine();
	vector<Receipe*> filtered;
	for (auto r : allrec) {
		if (r->getRecCuis() == cuis) {
			filtered.push_back(r);
		}
	}
	return filtered;
}

void Service::addRec(string name, string cuis, int prepar, vector<string> ingreds)
{
	for (auto r : this->getrecsortedbycuisine()) {
		if (name == r->getRecName()) {
			throw runtime_error("Already exists");
		}
	}
	this->repo.add(new Receipe(name, cuis, prepar, ingreds));
	this->notify();

}

vector<Receipe*> Service::getrecipesbyingredients(vector<string> ingredients) {
	vector<Receipe*> all = this->repo.getallrec();
	vector<Receipe*> result;

	for (Receipe* r : all) {
		const vector<string>& recIngr = r->getingred();
		set<string> recSet(recIngr.begin(), recIngr.end());
		bool allFound = true;
		for (const string& ing : ingredients) {
			if (recSet.find(ing) == recSet.end()) {
				allFound = false;
				break;
			}
		}

		if (allFound)
			result.push_back(r);
	}

	return result;
}

