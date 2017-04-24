#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <stack>

using namespace std;

template <typename VertexValue>
struct Vertex {
	VertexValue value;
	Vertex(VertexValue v) : value(std::move(v)) {}
};

template <typename VertexValue,typename EdgeValue>
struct Edge {
	using vtype = Vertex<VertexValue>;
	vtype* from;
	vtype* to;
	EdgeValue value;

	Edge(vtype* from, vtype* to, EdgeValue value) : from(from), to(to), value(std::move(value)) {}
};

template <typename VertexValue, typename EdgeValue>
struct Graph {
	using vtype = Vertex<VertexValue>;
	using etype = Edge<VertexValue,EdgeValue>;

	vector<unique_ptr<vtype>> vertices;
	vector<unique_ptr<etype>> edges;


	vtype * add_vertex(VertexValue value) {
		vertices.push_back(make_unique<vtype>(std::move(value)));
		auto&& last = vertices.back();
		return last.get();
	}

	etype* connect(vtype* from, vtype* to, EdgeValue value) {
		edges.push_back(make_unique<etype>(from, to,std::move(value)));
		auto&& last = edges.back();
		return last.get();
	}

	void disconnect(etype* e) {
		edges.erase(std::remove_if(edges.begin(), edges.end(), [this, e](auto&& edge) { return edge.get() == e; }));
	}

	vector<etype*> edges_from(vtype* a)
	{ 
		vector<etype *> output; 
		for (auto&& edge : edges)
			if (edge.get()->from == a)
				output.push_back(edge.get());
		return output; 
	}

	vector<etype *> edges_to(vtype* a)
	{
		vector<etype *> output; 
		for (auto&& edge : edges)
			if (edge.get()->to == a)
				output.push_back(edge.get());
		return output;
	}

	unordered_set<vtype *> verticies_from(vtype* a)
	{
		std::unordered_set<vtype*> vs; 
		for (etype* i : edges_from(a))
		{
			vs.insert(i->to);
		}
		return vs;
	}

    vtype * find(VertexValue value,vtype * starting_vertex)
	{
		std::queue<vtype *> q; 
		q.push(starting_vertex); 

		while(q.size() != 0)
		{
			vtype* v = q.front();
			q.pop();
			
			if (v->value == value)
				return v; 

			for (auto i : edges_from(v))
				q.push(i->to);
		}
		return nullptr; 
	}

	bool CycleDetection();


};

template <typename VertexValue, typename EdgeValue>
bool Graph<VertexValue, EdgeValue>::CycleDetection()
{
	if (vertices.size() == 0) return false;
	//find verticies with only outputEdges:
	std::stack<vtype*> stack;
	std::unordered_set<vtype *> closed;
	std::unordered_set<vtype *> opened;
	for (auto&&  v :  vertices)
	{
		if(edges_to(v.get()).size() == 0)
		{
			stack.push(v.get());
		}
	}
	if (stack.size() == 0)
	{
		stack.push(vertices[0].get());
	}

	while(!stack.empty())
	{
		vtype * v = stack.top();
		//all children visited
		if (opened.find(v) != opened.end())
		{
			closed.insert(v);
			stack.pop();
			continue;
		}
		for (auto i : verticies_from(v))
		{
			//Circular edge, Cycle found
			if (i == v)
				return true;
			//Visited vertex
			if(closed.find(i) != closed.end())
				continue;
			//Circular way, Cycle found 
			if (opened.find(i) != opened.end())
				return true;
			//corect, push
			stack.push(i);

			//TODO: more components 
		}
		opened.insert(v);

	
	}


	return false;
}


