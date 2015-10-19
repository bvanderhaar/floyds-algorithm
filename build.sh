clang-format -i floyd.cpp
clang++ -std=c++14 -O2 floyd.cpp -o floyds-algorithm
chmod +x floyds-algorithm
clang++ -std=c++14 -O2 gen_adj_matrix.cpp -o generate-matrix
chmod +x generate-matrix
