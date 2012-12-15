#include <fstream>
#include <list>

#include "GraphWriter.h"
#include "AdjacencyListGraph.h"

using namespace std;
using namespace graphpp;

bool GraphWriter::vertexWasVisited(unsigned int vertexId) {
	list<unsigned int>::iterator it = find(this->visitedVertexes.begin(), this->visitedVertexes.end(), vertexId);
	return it != this->visitedVertexes.end();
}

void GraphWriter::writeGraph(Graph *graph, string outputPath) {
    ofstream destinationFile;
    destinationFile.open(outputPath.c_str(), ios_base::out);

    this->visitedVertexes.clear();

    Graph::VerticesIterator verticesIterator = graph->verticesIterator();
    
    while (!verticesIterator.end()) {
    	Vertex *vertex = *verticesIterator;
    	
    	Vertex::VerticesIterator neighborsIterator = vertex->neighborsIterator();

    	while (!neighborsIterator.end()) {
    		Vertex *neighbor = *neighborsIterator;

    		if (!vertexWasVisited(neighbor->getVertexId())) {
    			destinationFile << vertex->getVertexId() << " " << neighbor->getVertexId() << std::endl;
    		}
    		
    		neighborsIterator++;
    	}

    	this->visitedVertexes.push_back(vertex->getVertexId());
    	verticesIterator++;
    }

    destinationFile.close();
}

void GraphWriter::writeWeightedGraph(WeightedGraph *weightedGraph, string outputPath) {
    ofstream destinationFile;
    destinationFile.open(outputPath.c_str(), ios_base::out);

    WeightedGraph::VerticesIterator verticesIterator = weightedGraph->verticesIterator();

    while (!verticesIterator.end()) {
        WeightedVertex *vertex = *verticesIterator;
        
        WeightedVertex::WeightsIterator weightsIterator = vertex->weightsIterator();

        while (!weightsIterator.end()) {
            if (!vertexWasVisited(weightsIterator->first)) {
                destinationFile << vertex->getVertexId() << " " << weightsIterator->first << " " << weightsIterator->second << std::endl;
            }
            
            weightsIterator++;
        }

        this->visitedVertexes.push_back(vertex->getVertexId());
        verticesIterator++;
    }

    destinationFile.close();
}