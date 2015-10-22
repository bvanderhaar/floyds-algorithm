#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#define INF 99999

std::vector<int> slurp(const std::string &filename) {
  std::vector<int> vect;
  int i;
  std::ifstream in(filename, std::ifstream::in);
  std::stringstream sstr;
  sstr << in.rdbuf();
  while (sstr >> i) {
    std::cout << "read i: " << i << std::endl;
    vect.push_back(i);
    if (sstr.peek() == '\t' || sstr.peek() == ' ') {
      sstr.ignore();
      }
  }
  return vect;
}

int main(int argc, char *argv[]) {
  int i, j, k=0;
  if (argc != 2) {
    std::cout << "Usage: floyds-algorithm num_vertices" << std::endl;
  }
  std::vector<int> flat_array = slurp("matrix.out");
  int vertices = atoi(argv[1]);
  int graph[vertices][vertices];
  for (i = 0; i < vertices; i++) {
    for (j = 0; j < vertices; j++) {
      std::cout << "i: " << i << " j: " << j << " value: " << flat_array[k] << std::endl;
      graph[i][j] = flat_array[k];
      k++;
    }
  }

  /* dist[][] will be the output matrix that will finally have the shortest
    distances between every pair of vertices */
  int dist[vertices][vertices];

  /* Initialize the solution matrix same as input graph matrix. Or
     we can say the initial values of shortest distances are based
     on shortest paths considering no intermediate vertex. */
  for (i = 0; i < vertices; i++)
    for (j = 0; j < vertices; j++)
      dist[i][j] = graph[i][j];

  /* Add all vertices one by one to the set of intermediate vertices.
    ---> Before start of a iteration, we have shortest distances between all
    pairs of vertices such that the shortest distances consider only the
    vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
    ----> After the end of a iteration, vertex no. k is added to the set of
    intermediate vertices and the set becomes {0, 1, 2, .. k} */
  for (k = 0; k < vertices; k++) {
    // Pick all vertices as source one by one
    for (i = 0; i < vertices; i++) {
      // Pick all vertices as destination for the
      // above picked source
      for (j = 0; j < vertices; j++) {
        // If vertex k is on the shortest path from
        // i to j, then update the value of dist[i][j]
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
      }
    }
  }
}
