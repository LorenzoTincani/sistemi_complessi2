#ifndef MATRIX_H
#define MATRIX_H
#include "Building.h"
#include "Link.h"
#include <iostream>
#include <array>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <map>

/*struct record
{
  std::string Pup;
  std::string Dropoff;
  //Qui bisogna usare un vettore in quanto si hanno più di due variabili. 
  
};*/

class Matrix
{
private:
  int N = 0;
  std::vector<std::vector<Link>> adj_matrix{};
  std::list<int> *adj = new std::list<int>[N]; // native array del c++ composto da list
  std::map<int,std::vector<int>> records{};
  void printAllPathsUtil(int, int, bool[], int[], int &, std::ostream &);
  bool isConnectedUtil(int, int, bool[], int[], int &, int &);
  std::vector<Building> nodes{};
  std::vector<int> Centrall{}; // vettore che tiene gli indici delle centrali di nodes
  std::vector<int> Sorting{};  // vettore che tiene gli indici degli smistamenti di nodes
  std::vector<int> House{};    // vettore che tiene gli indici delle case di nodes
  double Total_potential = 0.0;
  

public:
  Matrix(int n);
  Matrix() = default;

  // void addEdge(int u, int v); NOn ha senso usare un metodo quando lo possiamo fare manualmente, avendo diretto accessop ad adj.
  // Nel programma a cui ci stiamo ispirando, il metdodo viene utilizzato sulla classe nel main.

  void printAllPaths(int s, int d, std::ostream &);
  bool isConnected(int s, int d);
  void create();
  void control_for_matrix();
  void control_path();
  void transient();
  int getNofHouse() const;
  int getNofSorting() const;
  int getNofCentral() const;
  void fillRecords();

  Building &operator()(int i);
  Link &operator()(int i, int j);
  void PrintforRecords();
};
#endif
