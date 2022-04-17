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
//std::random_device rd;
class Matrix{
    private:
    static const int N =100; // N è numero di nodi, N^2-N il numero di link possibili
    std::array<std::array<Link, N>, N> adj_matrix{};
    std::array<Building, N> nodes;
    std::vector<int> Centrall; // vettore che tiene gli indici delle centrali di array
    std::vector<int> House;    // vettore che tiene gli indici delle case di array

    double Total_potential = 0.0;
    int nofSorting = 0;
    int nofCentral = 0;
    int nofHouse = 0;
    int nofBiglink = 0;
    int nofSmalllink = 0; // houses
    int nofHSLink = 0;    // house sorting
    int nofMediumlink = 0;

    public:
    Matrix()=default;
    void create();
    void transient();
    int getNofHouse()const;
    int getNofSorting()const;
    int getNofCentral()const;
    int CalcolatePath();
    




};
#endif