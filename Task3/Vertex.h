#pragma once
#include <list>
#include <vector>

using namespace std;

template <typename T>
class Vertex
{
public:
	Vertex(T value);
	~Vertex();
	T getValue();
	bool getVisited();
	void setVisited(bool value);
	int appendOut(Vertex<T>*);
	int appendIn(Vertex*);
	void removeOut(Vertex*);
	void removeIn(Vertex*);
	vector<Vertex*> getInAdj();
	vector<Vertex*> getOutAdj();

private:
	T value;
	bool visited;
	vector<Vertex*> inAdjacents;
	vector<Vertex*> outAdjacents;
	int findInVertex(Vertex<T>* v);
	int findOutVertex(Vertex<T>* v);
};

template<typename T>
Vertex<T>::Vertex(T value)
{
	this->value = value;
	this->visited = false;
}

template<typename T>
Vertex<T>::~Vertex()
{
	delete this->value;
}

template<typename T>
inline T Vertex<T>::getValue()
{
	return this->value;
}

template<typename T>
inline bool Vertex<T>::getVisited()
{
	return this->visited;
}

template<typename T>
inline void Vertex<T>::setVisited(bool value)
{
	this->visited = value;
}

template<typename T>
inline int Vertex<T>::appendOut(Vertex<T>* v)
{
	if (findOutVertex(v) == -1)
	{
		this->outAdjacents.push_back(v);
		return 1;
	}
	return 0;
}

template<typename T>
inline int Vertex<T>::appendIn(Vertex* v)
{
	if (findInVertex(v) == -1)
	{
		this->inAdjacents.push_back(v);
		return 1;
	}
	return 0;
}

template<typename T>
inline void Vertex<T>::removeOut(Vertex* rv)
{
	int index = findOutVertex(rv);
	if (index > -1)
	{
		for (int i = 0; i < this->outAdjacents.size(); i++)
		{
			if (this->outAdjacents[i] == rv)
				this->outAdjacents.erase(this->outAdjacents.begin() + i);
		}
	}
	else
	{
		throw "edge not exist";
	}
}

template<typename T>
inline void Vertex<T>::removeIn(Vertex* rv)
{
	int index = findInVertex(rv);
	if (index > -1)
	{
		for (int i = 0; i < this->inAdjacents.size(); i++)
		{
			if (this->inAdjacents[i] == rv)
				this->inAdjacents.erase(this->inAdjacents.begin() + i);
		}
	}
	else
	{
		throw "edge not exist";
	}
}

template<typename T>
inline vector<Vertex<T>*> Vertex<T>::getInAdj()
{
	return this->inAdjacents;
}

template<typename T>
inline vector<Vertex<T>*> Vertex<T>::getOutAdj()
{
	return this->outAdjacents;
}

template<typename T>
inline int Vertex<T>::findInVertex(Vertex<T>* v)
{
	for (int i = 0; i < this->inAdjacents.size(); i++)
	{
		if (this->inAdjacents[i] == v)
			return i;
	}
	return -1;
}

template<typename T>
inline int Vertex<T>::findOutVertex(Vertex<T>* v)
{
	for (int i = 0; i < this->outAdjacents.size(); i++)
	{
		if (this->outAdjacents[i] == v)
			return i;
	}
	return -1;
}