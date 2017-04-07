#pragma once
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

template <typename VertexValue>
struct Vertex {
	VertexValue value;
	Vertex(VertexValue v) : value(v) {}
};

template <typename VertexValue, typename EdgeValue>
struct Edge {
	using vtype = Vertex<VertexValue>;

	vtype* from;
	vtype* to;
	EdgeValue value;

	Edge(vtype* from, vtype* to, EdgeValue value) : from(from), to(to), value(value) {}
};

template <typename VertexValue, typename EdgeValue>
struct Graph {
	using vtype = Vertex<VertexValue>;
	using etype = Edge<VertexValue, EdgeValue>;

	vector<unique_ptr<vtype>> vertices;
	vector<unique_ptr<etype>> edges;


	vtype * add_vertex(VertexValue value) {
		vertices.push_back(make_unique<vtype>(value));
		auto&& last = vertices.back();
		return last.get();
	}

	etype* connect(vtype* a, vtype* b, EdgeValue value) {
		edges.push_back(make_unique<etype>(a, b, value));
		auto&& last = edges.back();
		return last.get();
	}
	vector<etype*> edges_from(vtype* a)
	{
		vector<etype *> output; 
		std::copy_if(edges.begin(), edges.end(),std::back_inserter(output), [this, a](auto&& edge) {return edge->from == a; }); 
		return output; 
	}
	void disconnect(etype* e)	{
		edges.erase(std::remove_if(edges.begin(),edges.end(), [this, e](auto&& edge) { return edge.get() == e; }));
	}

	


};


