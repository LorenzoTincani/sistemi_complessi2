#include "Link.h"
Link::Link(LinkType type, double load) : type_{type}, load_{load} {
}

LinkType Link::GetType() const
{
    return type_;
};
double Link::GetMaxLoad() const
{
    return max_load_;
};
double Link::GetLoad() const
{

    return load_;
};

bool Link::SetLoad(double const newload)
{

    load_ += newload;
    bool condition= false;
    if (load_ > max_load_)
    {
        condition = true;
    }
    else
    {
      condition=false;
    }
    return condition;
  
    
};

int Link::GetNumber() const
{
    return number_;
};
void Link::SetNumber(int n)
{
    number_ = n;
};
void Link::SetType(LinkType const T)
{
    type_ = T;
   switch (type_)
    {
    case LinkType::SH:
    max_load_=basic_load*1;
    break;
    case LinkType::SH_1:
    max_load_=basic_load*2;
    break;
    case LinkType::SH_2:
    max_load_=basic_load*3;
    break;
    case LinkType::SH_3:
    max_load_=basic_load*4;
    break;
    case LinkType::SS:
    max_load_=basic_load*5;
    break;
    case LinkType::M:
    max_load_=basic_load*6;
    break;
    case LinkType::B:
    max_load_=basic_load*7;
    break;
    
    default:
        break;
    }
};
