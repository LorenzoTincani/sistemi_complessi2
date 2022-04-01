#include "Link.h"
Link::Link(LinkType type, int max_load, int load) : type_{type}, max_load_{max_load}, load_{load} {}

LinkType Link::GetType() const
{
    return type_;
};
int Link::GetMaxLoad() const
{
    return max_load_;
};
int Link::GetLoad() const
{

    return load_;
};

void Link::SetLoad(int newload)
{
    load_ = newload;
};

int Link::GetNumber() const
{
    return number_;
};
void Link::SetNumber(int n)
{
    number_ = n;
};
void Link::SetType(LinkType T)
{
    type_ = T;
};
