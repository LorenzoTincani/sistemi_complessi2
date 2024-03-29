#ifndef BUILDING_H
#define BUILDING_H
#include <vector>
#include <iostream>
#include <list>
enum class BuildingType : char // underlying type int: 0 per H, 1 per S, 2 per C
{
    H, // houses
    S, // sorting
    C  // central
};     // Struttura gerarchica edifici

class Building
{
private:
    BuildingType type_ = BuildingType::H;
    double need_ = 0.0;
    double entry_potential_ = 0.0; // settato a zero, perchè definito dalla dinamica
    bool sorting_link_ = false;
    double efficiency_ = 0;             // diverso da zero solamente per i sorting, è legato al loro consumo e dipende dinamic dall'energia che hanno
    std::vector<int> Linked_houses{};   // Sono tre vettori che contengono le posizioni, all'interno dell'array nodes, del nodo a cui sono collegati.
    std::vector<int> Linked_sortages{}; // questi 3 vettori per cavare i link di troppo nel controllo
    std::vector<int> Linked_centrals{};
    std::vector<std::vector<int>> path_{};
    
public:
    Building(BuildingType type, double need, double entry_potential);
    Building() = default; // costruttore di default insieme alle condizioni uguali nel private

    Building &operator=(Building const &other);
    BuildingType GetType() const;
    double GetNeed() const;
    double GetEntryPotential() const;
    double GetEfficiency() const;
    // bool GetSortingLink() const;
    void SetEntryPotential(double entry_potential);
    void SetNeed(double need);
    void SetType(BuildingType type);
    //  void SetSortingLink(bool Sorting);
    void pathSorting() const;
    double OutputPotential() const;
    // path settings
    void SetPath(std::vector<std::vector<int>>local_path);
    //int GetPathsize();
    //void CalcolatePath();
   
    int GetPathNunmber() const;
    std::vector<int> GetMinPath() const;
    std::vector<int> GetPath_i(int i) const;
    std::vector<int> GetMaxPath() const;
    //int GetPathLength(int path) const;

    int GetNofSortingLink() const;
    int GetNofHouseLink() const;
    int GetNofCentralLink() const;

    int GetLinked_houses_size() const;   // Sono tre vettori che contengono le posizioni, all'interno dell'array nodes, del nodo a cui sono collegati.
    int GetLinked_sortages_size() const; // questi 3 vettori per cavare i link di troppo nel controllo
    int GetLinked_centrals_size() const;

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
    bool SearchEqualnodes(char C) const;

    void SetEfficiency(int e);

    void PrintPath();

    void DeleteAllPaths();
};
#endif
