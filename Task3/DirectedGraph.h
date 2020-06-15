#pragma once
#include<list>
#include <vector>
#include <string>
#include "Vertex.h"

using namespace std;

template <typename T2>
class DirectedGraph
{
public:
    DirectedGraph();
    ~DirectedGraph();
    bool contains(T2* vertex);
    bool adjacent(T2* from, T2* to);
    int addVertex(T2* obj);
    int addEdge(T2* from, T2* to);
    void removeVertex(T2* vertex);
    void removeEdge(T2* from, T2* to);
    int get_num_vertices();
    int get_num_edges();
    vector<T2*> depth_first(T2* vertex);
    vector<T2*> get_vertices();

private:
    vector<Vertex<T2*>*> vertices;
    int graph_size;
    int number_edges;
    Vertex<T2*>* getVertex(T2* val);
    vector<T2*> depth(vector<T2*> list, Vertex<T2*>* vertex);
};

template<typename T2>
DirectedGraph<T2>::DirectedGraph()
{
    this->graph_size = 0;
    this->number_edges = 0;
}

template<typename T2>
DirectedGraph<T2>::~DirectedGraph()
{
    for(int i = 0; i < this->vertices.size(); i++)
    {
        delete this->vertices.at(i);
    }
}

template<typename T2>
inline vector<T2*> DirectedGraph<T2>::get_vertices() {
    vector<T2*> vertices;
    for (Vertex<T2*>* vertex : this->vertices)
    {
        vertices.push_back(vertex->getValue());
    }
    return vertices;
}

template<typename T2>
inline Vertex<T2*>* DirectedGraph<T2>::getVertex(T2* val)
{
    for (Vertex<T2*>* vertex : this->vertices)
    {
        if (vertex->getValue() == val)
            return vertex;
    }
    return nullptr;
}

template<typename T2>
inline int DirectedGraph<T2>::get_num_vertices()
{
    return this->graph_size;
}

template<typename T2>
inline int DirectedGraph<T2>::get_num_edges()
{
    return this->number_edges;
}

template<typename T2>
inline vector<T2*> DirectedGraph<T2>::depth_first(T2* vertex)
{
    if (!contains(vertex))
        throw "vertex not exist in graph";
    Vertex<T2*>* first_vertex = this->getVertex(vertex);
    vector<T2*> list;
    for (Vertex<T2*>* v : this->vertices)
        v->setVisited(false);
    return this->depth(list, first_vertex);
}

template<typename T2>
inline vector<T2*> DirectedGraph<T2>::depth(vector<T2*> list, Vertex<T2*>* vertex)
{
    if (!vertex->getVisited()) {
        list.push_back(vertex->getValue());
        vertex->setVisited(true);
        for (Vertex<T2*>* next : vertex->getOutAdj())
        {
            list = depth(list, next);
        }
    }
    return list;
}

template<typename T2>
inline bool DirectedGraph<T2>::contains(T2* vertex)
{
    for (Vertex<T2*> *v : this->vertices)
    {
        if (v->getValue() == vertex)
            return true;
    }
    return false;
}

template<typename T2>
inline bool DirectedGraph<T2>::adjacent(T2* from, T2* to)
{
    if (!contains(from))
        throw "from-vertex not exist in graph";
    if (!contains(to))
        throw "to-vertex not exist in graph";
    Vertex<T2*>* v_from = this->getVertex(from);
    Vertex<T2*>* v_to = this->getVertex(to);
    bool f1 = false;
    for (Vertex<T2*>* v : v_from->getOutAdj())
    {
        if (v->getValue() == v_to->getValue())
            f1 = true;
    }
    bool f2 = false;
    for (Vertex<T2*>* v : v_to->getInAdj())
    {
        if (v->getValue() == v_from->getValue())
            f2 = true;
    }
    return f1 && f2;
}

template<typename T2>
int DirectedGraph<T2>::addVertex(T2* obj)
{
    if (contains(obj))
        return 0;
    Vertex<T2*> *vertex = new Vertex<T2*>(obj);
    this->vertices.push_back(vertex);
    this->graph_size++;
    return 1;
}

template<typename T2>
inline int DirectedGraph<T2>::addEdge(T2* from, T2* to)
{
    if (!contains(from))
        throw "from-vertex not exist in graph";
    if (!contains(to))
        throw "to-vertex not exist in graph";
    if (from == to)
        throw "loops not allowed";
    Vertex<T2*>* v_from = this->getVertex(from);
    Vertex<T2*>* v_to = this->getVertex(to);
    int r1 = v_from->appendOut(v_to);
    int r2 = v_to->appendIn(v_from);
    this->number_edges += r2;
    return r2;
}

template<typename T2>
inline void DirectedGraph<T2>::removeVertex(T2* obj)
{
    if (!contains(obj))
        throw "vertex not exist in graph";
    Vertex<T2*>* vertex = this->getVertex(obj);
    vector<Vertex<T2*>*> vect = vertex->getInAdj();
    int s = vect.size();
    for (int i = 0; i < s; i++)
    {
        vect[i]->removeOut(vertex);
    }
    this->number_edges -= s;
    for (int i = 0; i < vertex->getOutAdj().size(); i++)
    {
        vertex->getOutAdj().at(i)->removeIn(vertex);
    }
    this->number_edges -= vertex->getOutAdj().size();
    for (int i = 0; i < this->vertices.size(); i++)
    {
        if (this->vertices[i]->getValue() == obj)
            this->vertices.erase(this->vertices.begin() + i);
    }
    this->graph_size--;
}

template<typename T2>
inline void DirectedGraph<T2>::removeEdge(T2* from, T2* to)
{
    if (!contains(from))
        throw "from-vertex not exist in graph";
    if (!contains(to))
        throw "to-vertex not exist in graph";
    Vertex<T2*>* v_from = this->getVertex(from);
    Vertex<T2*>* v_to = this->getVertex(to);
    v_from->removeOut(v_to);
    v_to->removeIn(v_from);
    this->number_edges--;
}