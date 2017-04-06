#include "graph.h"
#include <string>
#include <iostream>
using namespace  std;
int main() {

	Graph<int, double> g;
	auto* a = g.add_vertex(1);
	auto* b = g.add_vertex(2);
	auto* c = g.add_vertex(3);
	auto* f = g.connect(c, a, 3.25);
	auto* e = g.connect(a, b, 3.14);

	
	for (auto&& i : g.edges)
		cout << i->from->value << " --" << i->value << "--> " << i->to->value << endl;
	cout << endl; 
	g.disconnect(f);
	for (auto&& i : g.edges)
		cout << i->from->value << " --" << i->value << "--> " << i->to->value << endl;

	string blank;
		getline(cin, blank);

	return 0;
}
