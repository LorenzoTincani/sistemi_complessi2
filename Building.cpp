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
    return NofSortingLink;
}
int Building::GetNofHouseLink() const
{
    return NofHouseLink;
}
int Building::GetNofCentralLink() const
{
    return NofCentralLink;
}

void Building::SetNofSortingLink(int i)
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
}
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