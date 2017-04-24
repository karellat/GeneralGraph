#include "graph.h"
#include <string>
#include <iostream>
#include <set>
using namespace  std;
int main() {
	
	Graph<unique_ptr<int>, unique_ptr<double>> g;
	auto* a = g.add_vertex(make_unique<int>(1));
	auto* b = g.add_vertex(make_unique<int>(2));
	auto* c = g.add_vertex(make_unique<int>(3));
	auto* d = g.add_vertex(make_unique<int>(4));
	auto* e = g.add_vertex(make_unique<int>(5));
	auto* f = g.add_vertex(make_unique<int>(6));

	g.connect(a, c, make_unique<double>(1.0));
	g.connect(b, d, make_unique<double>(2.0));
	g.connect(c, d, make_unique<double>(3.0));
	g.connect(c, e, make_unique<double>(4.0));
	g.connect(c, f, make_unique<double>(5.0));
	g.connect(d, f, make_unique<double>(6.0));
	g.connect(f, c, make_unique<double>(7.0));

	if (g.cycle_detection())
		cout << "true" << endl;
	else
		cout << "false" << endl;

	vector<Vertex<unique_ptr<int>>*> from;
	from.push_back(a);
	from.push_back(b);
	if (g.all_vertices_available_from(from))
		cout << "true";
	else
		cout << "false";


	std::string blank; 
	getline(cin, blank);

	return 0;
}
