#include "Building.h"
#include "Link.h"
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

int main()
{

    /* **************** Struttura matrice *************/
    int const N = 100; // N è numero di nodi, N^2-N il numero di link possibili
    // std::array<std::array<int, N>, N> adj_matrix{0}; // matrice di adiacenza, con int come pesi
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

    std::random_device rd; //   seed
    std::default_random_engine gen(rd());
    // std::discrete_distribution<int> link_dist({4, 3, 2, 1}); // parametri tra 0 e 3, per tre link più link non esistente
    // dal link inesistente a quello che collega le centrali //Se non funziona è colpa di Tinca
    std::discrete_distribution<int> nodeType_dist({100, 5, 1});
    std::normal_distribution<double> needfluct_dist(0.0, 0.33); // distribuzione guassiana di fluttuazioni nella richiesta di energia delle case
    std::uniform_real_distribution<double> link_dist(0.0, 1.0); // distribuzione uniforme per distribuzione dei link, generato come proporzioni programma arcelli
    std::uniform_int_distribution<int> forCentralchoice(0, N - 1);
    std::uniform_int_distribution<int> forCentralBuilding(0, N - 1); // distribuzione che sceglie, in caso non si avessero centrali, la posizione in nodes di BuildingType::C

    for (int k = 0; k < N; ++k) // settaggio dei nodi
    {
        int numtype = nodeType_dist(gen); // numtype = type of node
        if (numtype == 0)
        {
            double fluct = needfluct_dist(gen);
            nodes[k].SetType(BuildingType::H);
            nodes[k].SetNeed(7.2 + fluct); // consumo medio giornaliero di una famiglia media in kW/h
            // std::cout<<"house " <<nodes[k].GetNeed()<<std::endl;
            House.push_back(k);
            nofHouse++;
        }
        else if (numtype == 1)
        {
            nodes[k].SetType(BuildingType::S);
            nofSorting++;

            // std::cout<<"sorting "<<nodes[k].GetNeed()<<std::endl;
        }

        else if (numtype == 2)
        {
            double entrypotcentral = 100; // da aggiustare
            nodes[k].SetType(BuildingType::C);
            // std::cout<<"central "<<nodes[k].GetNeed()<<std::endl;
            nodes[k].SetEntryPotential(entrypotcentral); // da aggiustare
            Total_potential += entrypotcentral;
            nofCentral++;
            Centrall.push_back(k); // si sta riempiendo il vettore di Cetral con i posti delle Centrali rispettivi all'array nodes
        }
        else
        {
            std::cout << "Problem in the number generation" << std::endl;
        }
    }

    if (nofCentral == 0)
    { // Controllo per non avere un numero nullo di centrali.
        int positionofC = forCentralBuilding(gen);
        nodes[positionofC].SetType(BuildingType::C);
        Centrall.push_back(positionofC);
        nofCentral++;
    }

    std::cout << "nofcentral: " << nofCentral << std::endl;
    std::cout << "nofHouse: " << nofHouse << std::endl;
    std::cout << "nofSorting: " << nofSorting << std::endl;

    int j = 0; // j è fuori per poter calcolare solo il triangolo superiore della matrice dato che è simmetrica
    int counter = 0;

    if (nofSorting > (nofHouse / (100 / 15)))
    {
        std::cout << "Too little houses for each sorting" << std::endl;
    }

    /* --------------GENERAZIONE MATRICE DI ADIACENZA-----------------------*/

    for (int i = 0; i < N; ++i)
    {

        BuildingType node_i = nodes[i].GetType();

        for (j; j < N; ++j)
        {
            double rnd = link_dist(gen); // generazione variabile uniforme della probabilità che avvenga link
            BuildingType node_j = nodes[j].GetType();

            if (i == j)
            {
                adj_matrix[i][j].SetType(LinkType::N);
                adj_matrix[j][i].SetType(LinkType::N);

                adj_matrix[i][j].SetNumber(0);
                adj_matrix[j][i].SetNumber(0);
            }
            else
            {

                if (node_i == BuildingType::H)
                {
                    if (node_j == BuildingType::H)
                    {                    // casa-casa
                        if (rnd <= 0.20) // si suppone che, su 100 case, una casa sia collegata con altre 10.
                        {
                            adj_matrix[i][j].SetType(LinkType::SH);
                            adj_matrix[j][i].SetType(LinkType::SH);

                            adj_matrix[i][j].SetNumber(1); // link small
                            adj_matrix[j][i].SetNumber(1);

                            /*nodes[i].SetNofHouseLink(1);
                            nodes[j].SetNofHouseLink(1);*/

                            nodes[i].SetLinkedHouse(j);
                            nodes[j].SetLinkedHouse(i);

                            nofSmalllink++;
                        }
                    }
                    else if (node_j == BuildingType::S)
                    { // casa-smismistamento
                        if (nodes[i].GetNofSortingLink() == 0)
                        {
                            if (rnd <= 0.15)
                            {
                                adj_matrix[i][j].SetType(LinkType::SS);
                                adj_matrix[j][i].SetType(LinkType::SS);

                                adj_matrix[i][j].SetNumber(4);
                                adj_matrix[j][i].SetNumber(4);

                                /*nodes[i].SetNofSortingLink(1);
                                nodes[j].SetNofHouseLink(1);*/

                                nodes[i].SetLinkedSorting(j);
                                nodes[j].SetLinkedHouse(i);

                                nofHSLink++;
                            }
                        }
                        else
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0);
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else
                    { // casa-centrale
                        adj_matrix[i][j].SetType(LinkType::N);
                        adj_matrix[j][i].SetType(LinkType::N);

                        adj_matrix[i][j].SetNumber(0);
                        adj_matrix[j][i].SetNumber(0);
                    }
                }
                else if (node_i == BuildingType::S)
                {
                    if (node_j == BuildingType::H)
                    { // smistamento casa
                        if (nodes[j].GetNofSortingLink() == 0)
                        {
                            if (rnd <= 0.15)
                            {
                                adj_matrix[i][j].SetType(LinkType::SS);
                                adj_matrix[j][i].SetType(LinkType::SS);

                                adj_matrix[i][j].SetNumber(4);
                                adj_matrix[j][i].SetNumber(4);

                                /*nodes[i].SetNofHouseLink(1);
                                nodes[j].SetNofSortingLink(1);*/

                                nodes[i].SetLinkedHouse(j);
                                nodes[j].SetLinkedSorting(i);

                                nofHSLink++;
                            }
                        }
                        else
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0);
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else if (node_j == BuildingType::S)
                    { // smistamento-smistamento
                        if (rnd <= 0.10)
                        {

                            adj_matrix[i][j].SetType(LinkType::M);
                            adj_matrix[j][i].SetType(LinkType::M);

                            adj_matrix[i][j].SetNumber(2);
                            adj_matrix[j][i].SetNumber(2);

                            /*nodes[i].SetNofSortingLink(1);
                            nodes[j].SetNofSortingLink(1);*/

                            nodes[i].SetLinkedSorting(j);
                            nodes[j].SetLinkedSorting(i);

                            nofMediumlink++;
                        }
                        else
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0);
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else
                    { // smistamento-centrale
                        int rn = 0;
                        if (nodes[i].GetNofCentralLink() == 0)
                        {
                            // SCELTA DELLA CENTRALE A CUI COLLEGARE LO SMISTAMENTO
                            for (int m = 0; m < nofCentral;)
                            { // Bisogna assicurarsi che rn assume effettivamente il valore di un k corrispondente ad una centrale.
                                rn = forCentralBuilding(gen);
                                if (rn == Centrall[m])
                                {
                                    rn = Centrall[m];
                                    break;
                                }
                                else
                                {
                                    if (m == (nofCentral - 1))
                                    {
                                        m = 0;
                                    } // Non voglio che esca dal loop finchè non ha un valore assegnato.

                                    else
                                    {
                                        m++;
                                    }
                                }
                            }
                            // COLLEGAMENTO DEI DUE NODI
                            //   Il valore è però rn, che non è detto coincida con j

                            if (rn == j) // Se coincide con j, siam contenti e ci va pure di culo, dunque settiamo direttamente il link
                            {
                                adj_matrix[i][j].SetType(LinkType::B);
                                adj_matrix[j][i].SetType(LinkType::B);

                                adj_matrix[i][j].SetNumber(3);
                                adj_matrix[j][i].SetNumber(3); // La matrice è simmetrica
                                // nodes[i].SetSortingLink(true);

                                /*nodes[i].SetNofCentralLink(1);
                                nodes[j].SetNofSortingLink(1);*/

                                nodes[i].SetLinkedCentral(j);
                                nodes[j].SetLinkedSorting(i);

                                nofBiglink++;
                            }
                            else // Se j != rn allora bisogna collegare i ad rn e buttare a zero il link i-j.
                            // Siamo comunque nel caso smistamento- centrale, dunque ciò che viene buttato a zero è per forza un link di questo tipo.
                            {
                                adj_matrix[i][rn].SetType(LinkType::B);
                                adj_matrix[rn][i].SetType(LinkType::B);

                                adj_matrix[i][rn].SetNumber(3);
                                adj_matrix[rn][i].SetNumber(3);

                                nodes[i].SetLinkedCentral(rn);
                                nodes[rn].SetLinkedSorting(i);

                                adj_matrix[i][j].SetType(LinkType::N);
                                adj_matrix[j][i].SetType(LinkType::N);

                                adj_matrix[i][j].SetNumber(0);
                                adj_matrix[j][i].SetNumber(0);

                                nodes[i].DeleteLinkedCentral(j);
                                nodes[j].DeleteLinkedSorting(i);

                                // nodes[i].SetSortingLink(true);
                                /*nodes[i].SetNofCentralLink(1);
                                nodes[rn].SetNofSortingLink(1);*/

                                nofBiglink++;
                            }
                        }
                    }
                }

                else // centrale
                {
                    if (node_j == BuildingType::H)
                    { // centrale-casa
                        adj_matrix[i][j].SetType(LinkType::N);
                        adj_matrix[j][i].SetType(LinkType::N);

                        adj_matrix[i][j].SetNumber(0);
                        adj_matrix[j][i].SetNumber(0);
                    }
                    else if (node_j == BuildingType::S)
                    { // centrale-smistamento
                        if (nodes[j].GetNofCentralLink() == 0)
                        {
                            double rn = link_dist(gen);
                            if (rn <= 0.50)
                            {
                                adj_matrix[i][j].SetType(LinkType::B);
                                adj_matrix[j][i].SetType(LinkType::B);

                                adj_matrix[i][j].SetNumber(3);
                                adj_matrix[j][i].SetNumber(3);

                                /* nodes[i].SetNofSortingLink(1);
                                 nodes[j].SetNofCentralLink(1);*/

                                nodes[i].SetLinkedSorting(j);
                                nodes[j].SetLinkedCentral(i);

                                nofBiglink++;
                            }
                        }
                        else
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0); // Se lo smistamento è già collegato, non deve avere collegamento con la matrice corrente
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else
                    { // centrale-centrale

                        adj_matrix[i][j].SetType(LinkType::N);
                        adj_matrix[j][i].SetType(LinkType::N);

                        adj_matrix[i][j].SetNumber(0);
                        adj_matrix[j][i].SetNumber(0);
                    }
                }
            }
        }
        counter++;
        j = counter;
    }

    std::cout << "*********************CONTROLLI COLLEGAMENTI SMISTAMENTI-CASE************************************" << std::endl;
    std::cout << std::endl;

    std::cout << "---------------Collegamenti casa-casa prima dei controlli" << std::endl;
    std::cout << std::endl;

    for (int k = 0; k < N; k++)
    {
        if (nodes[k].GetType() == BuildingType::H)
        {
            std::cout << "Case collegate alla " << k << "esima casa :"<<nodes[k].GetNofHouseLink();
            //nodes[k].Print(0, 'H', true);
        }
        std::cout << std::endl;
    }

    std::cout << "-------------------------" << std::endl;
     int condition_house_max=0;
     int condition_house_min=0;
     int condition_house_ok=0;



    /*----------------------CONTROLLI----------------------*/

    // Controllo che non vi siano smistamenti non connessi ad una centrale.
    //  Se così fosse, come nelle righe 167-169 ne scelgo una tra le tante e assegno il link 3.
    for (int p = 0; p < N;)
    {
        int rn = 0;
        /* ----------------------SMISTAMENTO----------------------*/

        if (nodes[p].GetType() == BuildingType::S) // Per evitare che possa esserci uno smistamento non collegato a ciascuna centrale.
        //[Si faccia riferimento al ciclo precedente, ultima condizione Centrale- smistamento]
        {
            /*-------------centrale-------------------*/

            if ((nodes[p].GetNofCentralLink() == 0))
            {
                for (int m = 0; m < nofCentral;)
                { // Bisogna assicurarsi che rn assume effettivamente il valore di un k corrispondente ad una centrale.
                    rn = forCentralBuilding(gen);
                    if (rn == Centrall[m])
                    {
                        rn = Centrall[m];
                        break;
                    }
                    else
                    {
                        if (m == (nofCentral - 1))
                        {
                            m = 0;
                        } // Non voglio che esca dal loop finchè non ha un valore assegnato.

                        else
                        {
                            m++;
                        }
                    }
                }

                adj_matrix[p][rn].SetType(LinkType::B);
                adj_matrix[rn][p].SetType(LinkType::B);

                adj_matrix[p][rn].SetNumber(3);
                adj_matrix[rn][p].SetNumber(3); // La matrice è simmetrica

                nodes[rn].SetLinkedSorting(p);
                nodes[p].SetLinkedCentral(rn);

                // nodes[p].SetSortingLink(true);
                /*nodes[p].SetNofCentralLink(1);
                nodes[rn].SetNofSortingLink(1);*/

                nofBiglink++;
                // linkCentral++;
            }

            double localLinkH = static_cast<double>(nodes[p].GetNofHouseLink()) / static_cast<double>(nofHouse);
            double increment = static_cast<double>(1) / static_cast<double>(nofHouse);
            std::cout << "Tasso di collegamento sistamento " << p << "-esimo prima: " << localLinkH << std::endl;

            /*----------------casa----------------*/

            if (localLinkH <= 0.07)
            {
                bool full = false;

                for (int y = 0; localLinkH <= 0.07 && full == false;)
                { // in un for cerco nodo e nell'altro collego

                    for (int m = 0; m < nofHouse && (nodes[p].AlreadyLinked(m, 'H') == false);)
                    {
                        rn = forCentralBuilding(gen);

                        if (rn == House[m])
                        {
                            // std::cout << m << std::endl;
                            rn = House[m];
                            break;
                            // std::cout << "m" << std::endl;
                        }
                        else
                        {
                            if (m == (nofHouse - 1))
                            {
                                m = 0; // risettato a zero per non uscire dallo "scope"
                            }

                            else
                            {
                                m++;
                            }
                        }
                    }

                    if (nodes[rn].GetNofSortingLink() == 0)
                    {
                        adj_matrix[p][rn].SetType(LinkType::SS);
                        adj_matrix[rn][p].SetType(LinkType::SS);

                        adj_matrix[p][rn].SetNumber(4);
                        adj_matrix[rn][p].SetNumber(4); // La matrice è simmetrica

                        // nodes[p].SetSortingLink(true);
                        /*nodes[p].SetNofHouseLink(1);
                        nodes[rn].SetNofSortingLink(1);*/
                        nodes[p].SetLinkedHouse(rn);
                        nodes[rn].SetLinkedSorting(p);

                        nofSmalllink++;
                        // linkCentral++;
                        localLinkH = localLinkH + increment;

                        y++;
                    }
                    else // Bisogna mettere una condizione per evitare il loop, oppure è anche possibile collegare una casa a più smistamenti.
                    {
                        if (y < 100) // Se le iterazioni fatte sono minori di 100, si può procedere, ma una volta superata la soglia, è meglio procedere nel collegamento sistematico, tanto si tratta dei residui.
                        {
                            y++;
                        }
                        else

                        {
                            full = true;
                        }
                    }
                    // }
                }
            }
            /*---------------smistamento---------------*/
            // No controlli per ora

            p++;
        }

        //------------------------CASA--------------------------

        else if (nodes[p].GetType() == BuildingType::H)
        {
            double localLinkH = static_cast<double>(nodes[p].GetNofHouseLink()) / static_cast<double>(nofHouse);
            double increment = static_cast<double>(1) / static_cast<double>(nofHouse);
            //---------------casa--------------
            if (localLinkH <= 0.05)
            {
                condition_house_min++;
                bool full = false;
                for (int y = 0; localLinkH <= 0.05 && full == false;)
                { // in un for cerco nodo e nell'altro collego

                    for (int m = 0; m < nofHouse;)
                    {
                        rn = forCentralBuilding(gen);

                        if (rn == House[m])
                        {
                            // std::cout << m << std::endl;
                            if (nodes[p].AlreadyLinked(rn, 'H') == false)
                            {

                                // rn = House[m];
                                break;
                            }
                            else
                            {
                                if (m == (nofHouse - 1))
                                {
                                    m = 0; // risettato a zero per non uscire dallo "scope" e trovare una casa.
                                }

                                else
                                {
                                    m++;
                                }
                            }

                            // std::cout << "m" << std::endl;
                        }
                        else
                        {
                            if (m == (nofHouse - 1))
                            {
                                m = 0; // risettato a zero per non uscire dallo "scope" e trovare una casa.
                            }

                            else
                            {
                                m++;
                            }
                        }
                    }
                    double localLinkH_1 = static_cast<double>(nodes[rn].GetNofHouseLink()) / static_cast<double>(nofHouse);

                    if (localLinkH_1 <= 0.08)
                    {
                        adj_matrix[p][rn].SetType(LinkType::SH);
                        adj_matrix[rn][p].SetType(LinkType::SH);

                        adj_matrix[p][rn].SetNumber(1);
                        adj_matrix[rn][p].SetNumber(1); // La matrice è simmetrica

                        // nodes[p].SetSortingLink(true);
                        // nodes[p].SetNofHouseLink(1);
                        // nodes[rn].SetNofHouseLink(1);

                        nodes[p].SetLinkedHouse(rn);
                        nodes[rn].SetLinkedHouse(p);

                        nofSmalllink++;
                        // linkCentral++;
                        localLinkH = localLinkH + increment; // increment aumenta il numeratore di uno perchè è normalizzato

                        y++;
                    }
                    else // Bisogna mettere una condizione per evitare il loop, oppure è anche possibile collegare una casa a più smistamenti.
                    {
                        if (y < 100) // Se le iterazioni fatte sono minori di 100, si può procedere, ma una volta superata la soglia, è meglio procedere nel collegamento sistematico, tanto si tratta dei residui.
                        {
                            y++;
                        }
                        else
                        {
                            full = true;
                        }
                    }
                }
            }
            if (localLinkH >= 0.08)
            { // tolgo case se ne ho troppe collegate
            condition_house_max++;

                bool full = false;
                for (int y = 0; full == false;)
                { // in un for cerco nodo e nell'altro collego

                    if( localLinkH <= 0.06){
                        break;
                    }

                    for (int m = 0; m < nofHouse;)
                    {
                        rn = forCentralBuilding(gen);

                        if (rn == House[m])
                        {
                            if (nodes[p].AlreadyLinked(rn, 'H') == true) // condizioni per uscire dal ciclo
                            {
                                // std::cout << m << std::endl;
                                rn = House[m];
                                break;
                                
                            }
                            else
                            {
                                if (m == (nofHouse - 1))
                                {
                                    m = 0; // risettato a zero per non uscire dallo "scope"
                                }

                                else
                                {
                                    m++;
                                }
                            }
                            // std::cout << "m" << std::endl;
                        }
                        else
                        {
                            if (m == (nofHouse - 1))
                            {
                                m = 0; // risettato a zero per non uscire dallo "scope"
                            }

                            else
                            {
                                m++;
                            }
                        }
                    }
                    // Si sta rimuovendo il collegamento in ogni punto del codice: dalla matrice di adiacenza fino al vettore interno.

                    adj_matrix[p][rn].SetType(LinkType::N);
                    adj_matrix[rn][p].SetType(LinkType::N);

                    adj_matrix[p][rn].SetNumber(0);
                    adj_matrix[rn][p].SetNumber(0); // La matrice è simmetrica

                    // nodes[p].SetSortingLink(true);
                    /*nodes[p].SetNofHouseLink(1);
                    nodes[rn].SetNofSortingLink(1);*/
                    // linkCentral++;
                    nodes[p].DeleteLinkedHouse(rn);
                    nodes[rn].DeleteLinkedHouse(p);
                    localLinkH = localLinkH - increment;
                    nofHSLink--;

                    if (y < 100) // Se le iterazioni fatte sono minori di 100, si può procedere, ma una volta superata la soglia, è meglio procedere nel collegamento sistematico, tanto si tratta dei residui.
                    {
                        y++;
                    }
                    else

                    {
                        full = true;
                    }
                }
            }
           
           if(localLinkH > 0.05 && localLinkH< 0.08)
            {
                condition_house_ok++;

            }

            p++;
        }
        /*-------------------CENTRALE--------------------------------*/

        else
        {
            p++;
        }
    }

    std::cout << std::endl;

    for (int k = 0; k < N; ++k)
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
            std::cout << "Case collegate alla casa " << k << "esima: "<<nodes[k].GetNofHouseLink();
           // nodes[k].Print(0, 'H', true);
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************************************************" << std::endl;

    /*for (int i = 0; i < N; i++)
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
    }*/
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
     std::cout<<"H con tasso di collegamento basso: "<<condition_house_min<<" su "<<nofHouse<<std::endl;
      std::cout<<"H con tasso di collegamento elevato: "<<condition_house_max<<" su "<<nofHouse<<std::endl;
    std::cout<<"H con tasso di collegamento corretto: "<<condition_house_ok<<" su "<<nofHouse<<std::endl;

    // std::cout << "nofCentralLink :" << linkCentral << "\n";

    /* ********************SCRITTURA MATRICE SU FILE****************** */
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

    /* ***************DINAMICA MATRICE ****************** */
    /* for (int i = 0; i < N; i++)
     {
         for (int j = 0; j < N; j++)
         {
             if ()
             {
                 if ()
                 {
                 }
             }
         }
     }*/
} 
// FARE I SETNUMBER(0) NELLA MATRICE DI ADIACENZA.+ non vengono aggiornati i link casa-casa dopo i controlli
