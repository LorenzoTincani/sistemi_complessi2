#include "Building.h"
#include <algorithm>
Building::Building(BuildingType type, double need, double entry_potential) : type_{type}, need_{need}, entry_potential_{entry_potential}
{
}

/*

    BuildingType type_ = BuildingType::H;
    double need_ = 0.0;
    double entry_potential_ = 0.0; // settato a zero, perchè definito dalla dinamica
    bool sorting_link_ = false;
    double efficiency_ = 0;           // diverso da zero solamente per i sorting, è legato al loro consumo e dipende dinamic dall'energia che hanno
    std::vector<int> path_;           // array la cui dimensione è il numero di percorsi. Int indica i nodi tra centrale e nodo interessato
    std::vector<int> Linked_houses;   // Sono tre vettori che contengono le posizioni, all'interno dell'array nodes, del nodo a cui sono collegati.
    std::vector<int> Linked_sortages; // questi 3 vettori per cavare i link di troppo nel controllo
    std::vector<int> Linked_centrals;
*/
Building &Building::operator=(Building const &other)
{
    if (this != &other)
    {
        // Copia attributi
        type_ = other.GetType();
        need_ = other.GetNeed();
        entry_potential_ = other.GetEntryPotential();
        sorting_link_ = other.GetNofSortingLink();
        efficiency_ = other.GetEfficiency();
        // Copia vettori

        Linked_houses.clear();
        for (int i = 0; i < other.GetNofHouseLink(); i++)
        {
            Linked_houses.push_back(other.Linked_houses[i]);
        }
        Linked_sortages.clear();
        for (int i = 0; i < other.GetNofSortingLink(); i++)
        {
            Linked_sortages.push_back(other.Linked_sortages[i]);
        }
        Linked_centrals.clear();
        for (int i = 0; i < other.GetNofCentralLink(); i++)
        {
            Linked_centrals.push_back(other.Linked_centrals[i]);
        }
    }

    return *this;
};
BuildingType Building::GetType() const
{
    return type_;
};
double Building::GetNeed() const
{
    return need_;
};
/*bool Building::GetSortingLink() const
{
    return sorting_link_;
};*/
double Building::GetEntryPotential() const
{

    return entry_potential_;
};
double Building::GetEfficiency() const
{
    return efficiency_;
};
void Building::SetEntryPotential(double entry_potential)
{
    entry_potential_ = entry_potential;
}
void Building::SetNeed(double need)
{
    need_ = need;
}
void Building::SetType(BuildingType type)
{
    type_ = type;
}
/*void Building::SetSortingLink(bool Sorting)
{
    sorting_link_ = Sorting;
}*/
double Building::OutputPotential() const
{
    return (entry_potential_ - need_);
}
/*void Building::SetPath(int path, int distance)
{
    path_[path] = distance;
}

void Building::PathPushBack(int path_length)
{
    path_.push_back(path_length + 1);
}

std::vector<int> Building::GetPath() const
{

    return path_;
}

int Building::GetPathNunmber() const
{

    return path_.size();
}
int Building::GetMinPath() const
{
    auto a = &*min(path_.begin(), path_.end());
    return *a;
};
int Building::GetMaxPath() const
{
    auto a = &*max(path_.begin(), path_.end());
    return *a;
};
int Building::GetPathLength(int path) const
{
    return path_[path];
}*/

int Building::GetNofSortingLink() const
{
    return Linked_sortages.size();
}
int Building::GetNofHouseLink() const
{
    return Linked_houses.size();
}
int Building::GetNofCentralLink() const
{
    return Linked_centrals.size();
}

/*void Building::SetNofSortingLink(int i)
{
    NofSortingLink += i;
}
void Building::SetNofHouseLink(int i)
{
    NofHouseLink += i;
}
void Building::SetNofCentralLink(int i)
{
    NofCentralLink += i;
}*/
void Building::SetLinkedHouse(int i)
{
    Linked_houses.push_back(i);
};
void Building::SetLinkedSorting(int i)
{
    Linked_sortages.push_back(i);
};
void Building::SetLinkedCentral(int i)
{
    Linked_centrals.push_back(i);
};

int Building::GetLinked_houses_size() const
{
    return Linked_houses.size();
};
int Building::GetLinked_sortages_size() const
{
    return Linked_sortages.size();
};
int Building::GetLinked_centrals_size() const
{
    return Linked_centrals.size();
};
void Building::DeleteLinkedHouse(int i)
{
    int star = i;
    int position_star = 0;

    for (int y = 0; y < Linked_houses.size();)
    {

        if (Linked_houses[y] == star)
        {

            position_star = y;

            break;
        }

        else
            y++;
    }

    Linked_houses.erase(Linked_houses.begin() + position_star);
};
void Building::DeleteLinkedSorting(int i)
{

    int star = i;
    int position_star = 0;

    for (int y = 0; y < Linked_sortages.size();)
    {

        if (Linked_sortages[y] == star)
        {
            position_star = y;
            break;
        }

        else
            y++;
    }

    Linked_sortages.erase(Linked_sortages.begin() + position_star);
};
void Building::DeleteLinkedCentral(int i)
{

    int star = i;
    int position_star = 0;

    for (int y = 0; y < Linked_centrals.size();)
    {

        if (Linked_centrals[y] == star)
        {

            position_star = y;

            break;
        }

        else
            y++;
    }

    Linked_centrals.erase(Linked_centrals.begin() + position_star);
};
void Building::Print(int position, char C, bool EveryP)
{
    if (EveryP == false)
    {
        if (C == 'H')
        {
            std::cout << Linked_houses[position] << std::endl;
        }
        else if (C == 'S')
        {
            std::cout << Linked_sortages[position] << std::endl;
        }
        else
        {
            std::cout << Linked_centrals[position] << std::endl;
        }
    }
    else if (EveryP == true)
    {
        if (C == 'H')
        {
            for (int i = 0; i < Linked_houses.size(); i++)
            {
                std::cout << Linked_houses[i] << " ";
            }
            std::cout << std::endl;
        }
        else if (C == 'S')
        {
            for (int i = 0; i < Linked_sortages.size(); i++)
            {
                std::cout << Linked_sortages[i] << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            for (int i = 0; i < Linked_centrals.size(); i++)
            {
                std::cout << Linked_centrals[i] << " ";
            }
        }
        std::cout << std::endl;
    }
}

bool Building::AlreadyLinked(int i, char C) const
{

    if (C == 'H')
    {
        auto ItforFind = std::find(Linked_houses.begin(), Linked_houses.end(), i);

        if (ItforFind != Linked_houses.end())
        {
            return true;
        }
        else
            return false;
    }
    else if (C == 'S')
    {
        auto ItforFind = std::find(Linked_sortages.begin(), Linked_sortages.end(), i);

        if (ItforFind != Linked_sortages.end())
        {
            return true;
        }
        else
            return false;
    }
    else
    {
        auto ItforFind = std::find(Linked_centrals.begin(), Linked_centrals.end(), i);

        if (ItforFind != Linked_centrals.end())
        {
            return true;
        }
        else
            return false;
    }
}
void Building::SetEfficiency(int e)
{
    efficiency_ = e;
};



/*int Building::GetPathsize()
{
    int a = path_.size();
    return a;
};*/

/*void Building::PrintPath(int i, bool EveryP)
{
    if (EveryP == false)
    {
        for (int k = 0; k < path_matrix[i].size(); k++)
        {
            std::cout << path_matrix[i][k] << " \n";
            std::cout << path_matrix_Type[i][k] << " ";
        }
        std::cout << std::endl;
    }
    else{
        for(int p=0;p<path_matrix.size();p++){
        for (int k = 0; k < path_matrix[i].size(); k++)
        {
            std::cout << path_matrix[p][k] << " \n";
            std::cout << path_matrix_Type[p][k] << " ";
        }
        std::cout << std::endl;
        }


    }
};*/
/* bool Building::SearchEqualnodes(char C)const{
      if(C=='H'){
          for(int i=0; i<GetNofHouseLink; i++){
              if(AlreadyLinked(i,'H')==true){

              }
          }





     }
     else if(C=='S'){

     }
     else{
     }


 }*/
