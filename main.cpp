#include "Building.h"
#include "Link.h"
#include "matrix.h"
#include <iostream>
#include <array>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <fstream>

/* *************************************************************
Nella matrice di adiacenza:
- 0 =  nullo
- 1 = casa - casa
- 2 = smistamento - smistamento
- 3 = smistamento - centrale
- 4 = casa -smistamento
 **************************************************************  */
// namespace matrix {
int main()
{
    Matrix adjiacency_matrix{};
    adjiacency_matrix.create();
    

    std::cout << "nofcentral: " << adjiacency_matrix.getNofCentral() << std::endl;
    std::cout << "nofHouse: " << adjiacency_matrix.getNofHouse() << std::endl;
    std::cout << "nofSorting: " << adjiacency_matrix.getNofSorting() << std::endl;

  

    std::cout << "*********************CONTROLLI COLLEGAMENTI SMISTAMENTI-CASE************************************" << std::endl;
    std::cout << std::endl;

    std::cout << "---------------Collegamenti casa-casa prima dei controlli" << std::endl;
    std::cout << std::endl;

  /*  for (int k = 0; k < N; k++)
    {
        if (nodes[k].GetType() == BuildingType::H)
        {
            std::cout << "Case collegate alla " << k << "esima casa :" << nodes[k].GetNofHouseLink();
            // nodes[k].Print(0, 'H', true);
        }
        std::cout << std::endl;
    }*/

   // std::cout << std::endl;

   /* for (int k = 0; k < N; ++k)
    {
        if (nodes[k].GetType() == BuildingType::S)
        {
            double localLinkH = static_cast<double>(nodes[k].GetNofHouseLink()) / static_cast<double>(nofHouse);
            std::cout << "Tasso di collegamento sistamento " << k << "-esimo dopo : " << localLinkH << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "---------------Collegamenti casa-casa dopo i controlli" << std::endl;
    std::cout << std::endl;

    for (int k = 0; k < N; k++)
    {
        if (nodes[k].GetType() == BuildingType::H)
        {
            std::cout << "Case collegate alla casa " << k << "esima: " << nodes[k].GetNofHouseLink();
            // nodes[k].Print(0, 'H', true);
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************************************************" << std::endl;

    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            if (adj_matrix[i][k].GetType() == LinkType::N) // null
            {
                printf("\033[33m0 ");
            }
            else if (adj_matrix[i][k].GetType() == LinkType::SH) // hh
            {
                // std::cout << "       ";
                printf("\033[31m1 ");
            }
            else if (adj_matrix[i][k].GetType() == LinkType::M) // ss
            {
                // std::cout << "       ";
                printf("\033[32m2 ");
            }
            else if (adj_matrix[i][k].GetType() == LinkType::B) // cs
            {
                // std::cout << "       ";
                printf("\033[36m3 ");
            }
            else if (adj_matrix[i][k].GetType() == LinkType::SS)
            { // hs
                printf("\033[37m4 ");
            }
            else
            { // E' giusto vedere se viene generato qualche numero che non sia tra quelli contemplati.
                printf("\033[35m7 ");
            }
            printf("\033[0m");
        }

        std::cout << std::endl;
    }
    int nofHouselinkedS = 0;
    int nofSNOlinked = 0;

    for (int k = 0; k < N; k++)
    {
        auto nodeType = nodes[k].GetType();
        char type = ' ';
        if (nodeType == BuildingType::S)
        {
            type = 'S';
            if (nodes[k].GetNofHouseLink() == 0)
            {
                nofSNOlinked++;
            }
        }
        else if (nodeType == BuildingType::H)
        {
            type = 'H';
            nofHouselinkedS += nodes[k].GetNofSortingLink();
        }
        else
        {
            type = 'C';
        }
        std::cout << "Type of node " << k << " " << type << std::endl;
        std::cout << "Sorting Link of " << nodes[k].GetNofSortingLink() << std::endl;
        std::cout << "House Link of " << nodes[k].GetNofHouseLink() << std::endl;
        std::cout << "Central Link of " << nodes[k].GetNofCentralLink() << std::endl;
        std::cout << "------------------------------" << std::endl;
    }
    std::cout << "nofSmalllink :" << nofSmalllink << "\n";
    std::cout << "nofHouseSortingLink: " << nofHSLink << "\n";
    std::cout << "nofMediumlink :" << nofMediumlink << "\n";
    std::cout << "nofBiglink :" << nofBiglink << "\n";
    std::cout << std::endl;
    std::cout << "****************CONTROLLI***************" << std::endl;
    std::cout << "Su " << nofHouse << " case ce ne sono " << nofHouselinkedS << " collegate ad uno smistamento"
              << "\n";
    std::cout << "Su " << nofSorting << " smistamenti ce ne sono " << nofSNOlinked << "  collegati a zero case"
              << "\n";
    std::cout << "****************************************" << std::endl;
    std::cout << "H con tasso di collegamento basso: " << condition_house_min << " su " << nofHouse << std::endl;
    std::cout << "H con tasso di collegamento elevato: " << condition_house_max << " su " << nofHouse << std::endl;
    std::cout << "H con tasso di collegamento corretto: " << condition_house_ok << " su " << nofHouse << std::endl;

    // std::cout << "nofCentralLink :" << linkCentral << "\n";

    // ********************SCRITTURA MATRICE SU FILE******************
    std::ofstream adjmatrix;
    adjmatrix.open("adjmatrix.txt"); // Viene creato un file di nome "adjmatrix.txt"
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            adjmatrix << adj_matrix[i][j].GetNumber(); // Vengono scritti i numeri indentati, in modo da avere la visione della matrice
            adjmatrix << " ";
        }
        adjmatrix << std::endl;
    }
    adjmatrix.close();

*/
}
