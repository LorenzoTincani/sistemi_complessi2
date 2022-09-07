#ifndef LINK_H
#define LINK_H
enum class LinkType : char // underling type int : 0 per null, 1 per small, etc
{

    N,    // null
    SH,   // small between houses
    SH_1, // tre tipi di small link
    SH_2,
    SH_3,
    SS, // small between house and sorting
    M,  // medium
    B   // big

}; // Struttura gerarchica collegamenti
class Link
{
private:
    LinkType type_ = LinkType::N;
    const double basic_load = 3; // carico massimo del link più piccolo
    double max_load_ = basic_load * static_cast<double>(static_cast<int>(type_));
    double load_ = 0.0;
    int number_ = 0; // number that identifies the type of link during the print

public:
    Link(LinkType type, double load);
    Link() = default;
    LinkType GetType() const;
    void SetType(LinkType const T);
    double GetMaxLoad() const;
    double GetLoad() const;
    bool SetLoad(double const newload);
    int GetNumber() const;
    void SetNumber(int n);
};
#endif
