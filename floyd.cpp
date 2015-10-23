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
    // std::cout << "read i: " << i << std::endl;
    vect.push_back(i);
    if (sstr.peek() == '\t' || sstr.peek() == ' ') {
      sstr.ignore();
    }
  }
  return vect;
}

void print_2d_array(std::vector<std::vector<int>> array, int vertices) {
  int i = 0, j = 0;
  for (i = 0; i < vertices; i++) {
    for (j = 0; j < vertices; j++) {
      if (array[i][j] == INF) {
        std::cout << "INF"
                  << "\t";
      } else {
        std::cout << array[i][j] << "\t";
      }
    }
    std::cout << "\n";
  }
}

std::vector<std::vector<int>>
calc_distance(std::vector<std::vector<int>> distance_matrix, int vertices) {
  std::vector<std::vector<int>> solution;
  int i = 0, j = 0, k = 0, normalized;
  solution.resize(vertices, std::vector<int>(vertices, INF));

  // normalize the array with INF to prevent arithmetic overflow
  for (i = 0; i < vertices; i++) {
    for (j = 0; j < vertices; j++) {
      normalized = distance_matrix[i][j];
      if (normalized > INF) {
        normalized = INF;
      }
      solution[i][j] = normalized;
    }
  }

  //std::cout << "normalized array: \n" << std::endl;
  //print_2d_array(solution, vertices);
  for (k = 0; k < vertices; k++) {
    for (i = 0; i < vertices; i++) {
      for (j = 0; j < vertices; j++) {
        if (solution[i][k] + solution[k][j] < solution[i][j])
          solution[i][j] = solution[i][k] + solution[k][j];
      }
    }
  }
  return solution;
}

std::vector<std::vector<int>> test_graph() {
  std::vector<std::vector<int>> test_graph;
  test_graph.resize(4, std::vector<int>(4, INF));
  test_graph = {
      {0, 5, INF, 10}, {INF, 0, 3, INF}, {INF, INF, 0, 1}, {INF, INF, INF, 0}};
  return test_graph;
}

int main(int argc, char *argv[]) {
  int vertices = 0, i = 0, j = 0, k = 0;
  std::vector<std::vector<int>> graph;
  if (argc < 2) {
    std::cout << "Usage: floyds-algorithm num_vertices [-t]" << std::endl;
  }
  vertices = atoi(argv[1]);
  std::vector<int> flat_array = slurp("matrix.out");
  if (argc != 3) {
    graph.resize(vertices, std::vector<int>(vertices, INF));
    for (i = 0; i < vertices; i++) {
      for (j = 0; j < vertices; j++) {
        // std::cout << "i: " << i << " j: " << j << " value: " << flat_array[k]
        // << std::endl;
        graph[i][j] = flat_array[k];
        k++;
      }
    }
  } else {
    std::cout << "using test mode\n";
    vertices = 4;
    graph = test_graph();
  }

  std::vector<std::vector<int>> solution = calc_distance(graph, vertices);
  std::cout << "solution array: " << std::endl;
  print_2d_array(solution, vertices);
  return 0;
}
