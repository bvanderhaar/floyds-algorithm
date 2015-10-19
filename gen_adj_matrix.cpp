// gen_adjMatrix.cc
// generates random adjacency matrix of desired size and connectivity
// represents a random graph
// gw

// MSVS: use Win32 Console Application / Empty Project
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <ctime>
using namespace std;

#define MAX_WEIGHT 20

void gen_adj_matrix (int *, int, int);
void print_matrix (int*, int);

int main (int argc, char *argv[])
{
	int numVertices, avgConnectivity;

	// setup/initialize
	if ((argc != 3) || (atoi(argv[2]) > atoi(argv[1]))) {
		cerr << "usage: progName numVertices avgConnectivity\n" << endl;
		exit(-1);
	}
	else {
		numVertices = atoi(argv[1]);
		avgConnectivity = atoi(argv[2]);
	}
	int *adjMatrix = new int[numVertices * numVertices];

	// generate random graph/matrix
	gen_adj_matrix(adjMatrix, numVertices, avgConnectivity);

	print_matrix (adjMatrix, numVertices);

	delete [] adjMatrix;
	return 0;
}

void gen_adj_matrix(int *data, int size, int connectivity)
{
	int i,j;

	// generate random size x size adjacency matrix of requested connectivity
	// uses "infinity" to indicate non-adjacent nodes
	srand((unsigned) time(0));
	for (i=0; i < size; i++)
		for (j=0; j < size; j++)
			if (((rand() % size) < connectivity) && i!=j)
				data[i*size+j] = 1 + (rand() % MAX_WEIGHT);
			else
				data[i*size+j] = INT_MAX;
}


void print_matrix (int *data, int size)
{
	int i,j;
	ofstream outputFile;

	outputFile.open ("matrix.out");
	for (i=0; i < size; i++) {
		for (j=0; j < size; j++)
			outputFile << data[i*size+j] << "\t";
	}
	outputFile.close();
}
