#ifndef BUILDING_H
#define BUILDING_H
#include <vector>
#include <iostream>
enum class BuildingType : char //underlying type int: 0 per H, 1 per S, 2 per C
{
    H, //houses
    S, //sorting
    C  //central
};     //Struttura gerarchica edifici

class Building
{
private:
    BuildingType type_ = BuildingType::H;
    double need_ = 0.0; 
    double entry_potential_ = 0.0; //settato a zero, perchè definito dalla dinamica
    bool sorting_link_ = false;
    double efficiency_=0;  //diverso da zero solamente per i sorting, è legato al loro consumo e dipende dinamic dall'energia che hanno
   /* int NofCentralLink=0;
    int NofSortingLink=0;
    int NofHouseLink=0;*/
    std::vector<int> path_; //array che contiene le lunghezze dei path (colonne) di path_matrix
    std::vector<std::vector<int>> path_matrix{};
    std::vector<std::vector<char>> path_matrix_Type{};
    std::vector<int> Linked_houses; //Sono tre vettori che contengono le posizioni, all'interno dell'array nodes, del nodo a cui sono collegati.
    std::vector<int> Linked_sortages;  //questi 3 vettori per cavare i link di troppo nel controllo
    std::vector<int> Linked_centrals;

public:
    Building(BuildingType type, double need, double entry_potential);
    Building() = default; //costruttore di default insieme alle condizioni uguali nel private
    BuildingType GetType() const;
    double GetNeed() const;
    double GetEntryPotential() const;
   // bool GetSortingLink() const;
    void SetEntryPotential(double entry_potential);
    void SetNeed(double need);
    void SetType(BuildingType type);
  //  void SetSortingLink(bool Sorting);
    double OutputPotential()const;
    //path settings
    void SetPath(int path, int distance);
    //void CalcolatePath();
    std::vector<int> GetPath() const;
    int GetPathNunmber () const;
    int GetMinPath()const;
    int GetMaxPath()const;
    int GetPathLength(int path)const;

    int GetNofSortingLink()const;
    int GetNofHouseLink()const;
    int GetNofCentralLink()const;

   /* void SetNofSortingLink(int i);
    void SetNofHouseLink(int i);
    void SetNofCentralLink(int i);*/

    void SetLinkedHouse(int i);
    void SetLinkedSorting(int i);
    void SetLinkedCentral(int i);

    void DeleteLinkedHouse(int i);
    void DeleteLinkedSorting(int i);
    void DeleteLinkedCentral(int i);

    void Print(int position, char C, bool EveryP);
    bool AlreadyLinked(int i, char C) const;
    bool SearchEqualnodes(char C)const;
    
    void SetEfficiency(int e);

    void SetPath_matrix(int i, int i_i);  //nella posizione i c'è il nodo i_i , fissando i indica la colonna
    void SetPath_matrixType(int i, char type);
    void PrintPath(int i, bool EveryP);
    



   


};
#endif