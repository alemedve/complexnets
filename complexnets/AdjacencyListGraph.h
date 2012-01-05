#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#define NO_RANKER

#include "mili/mili.h"
#include "GraphExceptions.h"

namespace graphpp
{                           
                          
    /**
    * Class: Graph
    * ------------
    * Description: Principal graph class. Allows to add vertices and edges, and provides
    * iterators to work with them.
    * Template Argument Vertex: Type of the vertex. Vertex should have an addEdge method that
    * receives another Vertex
    * Template Argument VertexContainer: Container that will hold the vertices. May be 
    * std::list<Vertex>, std::vector<Vertex> or std::set<Vertex>, depending on the user's 
    * preferences
    */
    template <class Vertex, class VertexContainer = std::set<Vertex*> >
    class AdjacencyListGraph
    { 
    public:    

        typedef CAutonomousIterator<VertexContainer>  VerticesConstIterator;
        typedef AutonomousIterator<VertexContainer>  VerticesIterator;
        
        /**
        * Method: addVertex
        * -----------------
        * Description: Adds a vertex to the graph
        * @param v Vertex to be added
        */
        void addVertex(Vertex* v)
        {                
            //insert the vertex in the vertices container
            insert_into(vertices, v);
        }
        
        /**
        * Method: addEdge
        * ---------------
        * Description: Adds an edge, connecting vertices s and d together
        * @param s a vertex to connect
        * @param d a vertex to connect
        */
        void addEdge(Vertex* s, Vertex* d)
        {
            //Since by default this isn't multigraph, duplicate edges are not allowed
            if(s->isNeighbourOf(d))
                throw DuplicateEdge();
            s->addEdge(d);
            d->addEdge(s);
        }

        /**
        * Method: VerticesConstIterator
        * -----------------------------
        * Description: Provides constant forward iterator to the vertices of the graph
        * @returns a constant iterator abstraction to iterate through the vertices of the graph`
        */
        VerticesConstIterator verticesConstIterator() const
        {
            return VerticesConstIterator(vertices);
        }
        
        /**
        * Method: VerticesIterator
        * ------------------------
        * Description: Provides forward iterator to the vertices of the graph
        * @returns a iterator abstraction to iterate through the vertices of the graph`
        */
        VerticesIterator verticesIterator()
        {
            return VerticesIterator(vertices);
        }
        
        /**
        * Method: verticesCount
        * ---------------------
        * Description: informs the number of vertices currently in the graph
        * @returns number of vertices in the graph
        */
        unsigned int verticesCount() const
        {
            return vertices.size();
        }
        
        private:
            VertexContainer vertices;
     }; 

}

#endif