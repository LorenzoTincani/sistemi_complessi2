#include "Building.h"
#include "algorithm"
Building::Building(BuildingType type, double need, double entry_potential) : type_{type}, need_{need}, entry_potential_{entry_potential}
{
}
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
void Building::SetPath(int path, int distance)
{
    path_[path] = distance;
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
}

int Building::GetNofSortingLink() const
{
    // return NofSortingLink;
    return Linked_sortages.size();
}
int Building::GetNofHouseLink() const
{
    // return NofHouseLink;
    return Linked_houses.size();
}
int Building::GetNofCentralLink() const
{
    // return NofCentralLink;
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
void Building::DeleteLinkedHouse(int i)
{
    Linked_houses.erase(Linked_houses.begin() + i);
};
void Building::DeleteLinkedSorting(int i)
{
    Linked_sortages.erase(Linked_sortages.begin() + i);
};
void Building::DeleteLinkedCentral(int i)
{
    Linked_centrals.erase(Linked_centrals.begin() + i);
};
void Building::Print(int position, char C, bool EveryP)
{
    std::cout<<"ciao\n";
    
    /*

    if (EveryP == false)
    {
        if (C == 'H')
        {
            std::cout << Linked_houses[position]<< std::endl;
        }
        else if (C == 'S')
        {
            std::cout << Linked_sortages[position] << std::endl;
        }
        else
        {
            std::cout << Linked_centrals[position]<< std::endl;
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
                std::cout << Linked_sortages[i]<< " ";
            }
            std::cout << std::endl;
        }
        else
        {for (int i = 0; i < Linked_centrals.size(); i++)
            {
                std::cout << Linked_centrals[i] << " ";
            }
        }
        std::cout << std::endl;
        }*/
    }

    bool Building::AlreadyLinked(int i, char C) const{

        if(C=='H'){
            auto ItforFind=std::find(Linked_houses.begin(), Linked_houses.end(), i);

            if(ItforFind!=Linked_houses.end()){
                return true;
            }
            else return false;


        }
        else if(C=='S'){
            auto ItforFind=std::find(Linked_sortages.begin(), Linked_sortages.end(), i);

            if(ItforFind!=Linked_sortages.end()){
                return true;
            }
            else return false;

        }
        else{
             auto ItforFind=std::find(Linked_centrals.begin(), Linked_centrals.end(), i);

            if(ItforFind!=Linked_centrals.end()){
                return true;
            }
            else return false;
        }

    }
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
