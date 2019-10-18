#include <iostream>
#include "pch.h"
#include "Graph.h"
#include <string>

class UserDefinedClass
{
	string key;
	// random useless stuff
	unordered_multimap < string, tuple<int, long, char> > m;
	initializer_list<int8_t> il;

public:
	UserDefinedClass(string k) : key{ k } {}
	UserDefinedClass() {}
	UserDefinedClass(const UserDefinedClass& other)
	{
		this->key = other.key;
	}

	bool operator<(const UserDefinedClass& other) const
	{
		return this->key < other.key;
	}
	string getKey() const { return key; }

	bool operator== (const UserDefinedClass &other) const
	{
		return key == other.key;
	}

	// Not required, but needed to test output
	friend ostream& operator<<(ostream& os, const UserDefinedClass& w);
};

ostream& operator<<(ostream& os, const UserDefinedClass& obj)
{
	os << obj.key;
	return os;
}


template<> struct hash<UserDefinedClass>
{
	std::size_t operator()(const UserDefinedClass& obj) const noexcept
	{
		return hash<string>()(obj.getKey());
	}
};

class UserDefinedWeight
{
	string weight;

public:
	UserDefinedWeight(string w) : weight{ w } {}
	UserDefinedWeight(int zero) {}
	UserDefinedWeight() {}

	// sum ascii values of chars to compare weight
	// if contains 'x' multiply sum by 2
	bool operator<(const UserDefinedWeight& other) const
	{
		int thisSum = 0, otherSum = 0;

		for (auto c : this->weight){
			if (c == 'x')
				thisSum *= 2;
			else
				thisSum += c;
		}
		for (auto c : other.weight){
			if (c == 'x')
				otherSum *= 2;
			else
				otherSum += c;
		}
		return (thisSum < otherSum);
	}

	UserDefinedWeight& operator= (const UserDefinedWeight &w)
	{
		weight = w.weight;
		return *this;
	}

	// Not required, but needed to test output
	friend ostream& operator<<(ostream& os, const UserDefinedWeight& w);
};

ostream& operator<<(ostream& os, const UserDefinedWeight& w)
{
	os << w.weight;
	return os;
}

int main()
{

	// Test prim's algorithm with user defined key type and user defined numerical type
	Graph<UserDefinedClass, UserDefinedWeight> g2;
	UserDefinedClass o1{ "o1" }; g2.addVertex(o1);
	UserDefinedClass o2{ "o2" }; g2.addVertex(o2);
	UserDefinedClass o3{ "o3" }; g2.addVertex(o3);
	UserDefinedClass o4{ "o4" }; g2.addVertex(o4);
	UserDefinedClass o5{ "o5" }; g2.addVertex(o5);
	UserDefinedClass o6{ "o6" }; g2.addVertex(o6);
	UserDefinedClass o7{ "o7" }; g2.addVertex(o7);

	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o5, o7, static_cast<UserDefinedWeight>("abcde")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o4, o6, static_cast<UserDefinedWeight>("wx")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o4, o1, static_cast<UserDefinedWeight>("axxxxxx")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o1, o2, static_cast<UserDefinedWeight>("a")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o1, o3, static_cast<UserDefinedWeight>("ab")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o7, o3, static_cast<UserDefinedWeight>("xyzz")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o6, o2, static_cast<UserDefinedWeight>("$.,#(@)`\"/\\n")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o2, o7, static_cast<UserDefinedWeight>("abc")));
	g2.addEdge(Edge<UserDefinedClass, UserDefinedWeight>(o3, o4, static_cast<UserDefinedWeight>("abcd")));

	g2.primsMinTree(o1);

	/*
	// Test prim's algorithm with char type
	int verts, edges;
	cin >> verts >> edges;
	Graph<char, int> g;
	for (int i = 0; i < verts; ++i)
	{
		g.addVertex((char)(i + 65));
	}
	for (int i = 0; i < edges; ++i) {
		char v, w; int  weight;
		cin >> v >> w >> weight;
		g.addEdge(Edge<char, int>(v, w, weight));
	}

	g.primsMinTree('A');
	cout << endl;
	*/

	/*
	// Test prim's algorithm with user defined key type and char as "numerical" type
	Graph<UserDefinedClass, char> g2;
	UserDefinedClass o1{ "o1" }; g2.addVertex(o1);
	UserDefinedClass o2{ "o2" }; g2.addVertex(o2);
	UserDefinedClass o3{ "o3" }; g2.addVertex(o3);
	UserDefinedClass o4{ "o4" }; g2.addVertex(o4);
	UserDefinedClass o5{ "o5" }; g2.addVertex(o5);
	UserDefinedClass o6{ "o6" }; g2.addVertex(o6);
	UserDefinedClass o7{ "o7" }; g2.addVertex(o7);

	g2.addEdge(Edge<UserDefinedClass, char>(o5, o7, 'E'));
	g2.addEdge(Edge<UserDefinedClass, char>(o4, o6, 'W'));
	g2.addEdge(Edge<UserDefinedClass, char>(o4, o1, 'X'));
	g2.addEdge(Edge<UserDefinedClass, char>(o1, o2, 'A'));
	g2.addEdge(Edge<UserDefinedClass, char>(o1, o3, 'B'));
	g2.addEdge(Edge<UserDefinedClass, char>(o7, o3, 'Y'));
	g2.addEdge(Edge<UserDefinedClass, char>(o6, o2, 'Z'));
	g2.addEdge(Edge<UserDefinedClass, char>(o2, o7, 'C'));
	g2.addEdge(Edge<UserDefinedClass, char>(o3, o4, 'D'));

	g2.primsMinTree(o1);
	*/
}


