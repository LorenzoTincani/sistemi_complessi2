#ifndef MAIN_H
#define MAIN_H
#include "Building.h"
#include "Link.h"
#include <iostream>
#include <array>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>
#include <list>

// std::random_device rd;
class Matrix
{
private:
  //  static const int N=100; // N è numero di nodi, N^2-N il numero di link possibili
  // std::array<std::array<Link, N>, N> adj_matrix{}; //cambiato in vector perchè cosi lo si definisce bene nel costruttore
  int N = 0;
  std::vector<std::vector<Link>> adj_matrix{};
  std::list<int> *adj = new std::list<int>[N];
  void printAllPathsUtil(int, int, bool[], int[], int &);


  // std::array<Building,N> nodes;
  std::vector<Building> nodes{};
  std::vector<int> Centrall{}; // vettore che tiene gli indici delle centrali di nodes
  std::vector<int> House{};    // vettore che tiene gli indici delle case di nodes

  double Total_potential = 0.0;
  int nofSorting = 0;
  int nofCentral = 0;
  int nofHouse = 0;
  int nofBiglink = 0;
  int nofSmalllink = 0; // houses
  int nofHSLink = 0;    // house sorting
  int nofMediumlink = 0;

public:
  Matrix(int n);
  Matrix() = default;

  void addEdge(int u, int v);
    void printAllPaths(int s, int d);


  void create();
  void transient();
  int getNofHouse() const;
  int getNofSorting() const;
  int getNofCentral() const;
  // void CalculatePath();
  Building &operator()(int i);
  Link &operator()(int i, int j);
  std::vector<std::vector<int>> Calculate(std::vector<std::vector<int>> adjacency);
};
#endif