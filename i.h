//
// Created by macbook on 10.02.26.
//

#ifndef LAB8_1_I_H
#define LAB8_1_I_H
#include <vector>
struct Artifact;
bool readf(const std::string& filename, std::vector<Artifact>& artifacts, int& Z);
void solve(const std::vector<Artifact>& artifacts, int Z, std::vector<int>& selectedIds,int &totalWeight,int& totalValue);
void printResults(const std::vector<int>& selectedIds, int totalWeight, int totalValue);
void t1();
void inputData(int& K, int& N);
double countk(int K, int N);
void t3();
void t2();
#endif //LAB8_1_I_H