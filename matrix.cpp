#include "matrix.h"

Matrix::Matrix(int n) : N(n), adj_matrix(N, std::vector<Link>(N)), nodes{}
{

    if (N <= 0)
    {
        throw std::runtime_error{"N must be bigger than 1"};
    }
}

void Matrix::printAllPathsUtil(int u, int d, bool visited[],
                               int path[], int &path_index, std::ostream &ADJM_)
{
    // std::cout << " 19 matrix.cpp\n";
    //  Mark the current node and store it in path[]
    //  Se il nodo è visitato, il suo indice va aggiunto all'interno dell'array path, incrementato la posizione per il cammino successivo.
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]

    //  std::ofstream adjmatrix;
    // adjmatrix.open("adjmatrix.txt"); // Viene creato un file di nome "adjmatrix.txt"
    if (u == d)
    {

        for (int i = 0; i < path_index; i++)
        {
            int index = path[i];
            ADJM_ << index << " ";
            //  adjmatrix << " ";

            std::cout << path[i] << " ";
        }
        std::cout << -1;
        std::cout << std::endl;
        ADJM_ << -1;
        ADJM_ << std::endl;

    }

    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        std::list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])

                printAllPathsUtil(*i, d, visited, path, path_index, ADJM_);
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
    // std::cout << "47 matrix.cpp\n";
    // adjmatrix.close();
}

// Prints all paths from 's' to 'd'
void Matrix::printAllPaths(int s, int d, std::ostream &ADJM)
{

    // std::cout << "51 matrix.cpp\n";
    // Mark all the vertices as not visited
    bool *visited = new bool[N]; // In modo tale che capisca quali percorsi ha già tracciato, evitando di mandare in loop il programma.

    // Create an array to store paths
    int *path = new int[N];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < N; i++)
        visited[i] = false; // In quanto è necessario esplorarli uno ad uno.

    // Call the recursive helper function to print all paths
    printAllPathsUtil(s, d, visited, path, path_index, ADJM);

    




}

bool Matrix::isConnectedUtil(int u, int d, bool visited[],
                             int path[], int &path_index, int &depth_)
{
    depth_++;
    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]
    if (nodes[u].GetType() == BuildingType::C)
    {
        return true;
    }
    else // If current vertex is not a central
    {
        // Recur for all the vertices adjacent to current vertex
        std::list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            if (!visited[*i])
            {
                isConnectedUtil(*i, d, visited, path, path_index, depth_);
            }
        }
    }
    depth_--;
    path_index--;
    visited[u] = false;

    if (depth_ == 0)
    {
        return false;
    }
}

bool Matrix::isConnected(int s, int d)
{

    bool result;
    // Mark all the vertices as not visited
    bool *visited = new bool[N];

    // Create an array to store paths
    int *path = new int[N];
    int path_index = 0; // Initialize path[] as empty

    int depth = 0;

    // Initialize all vertices as not visited
    for (int i = 0; i < N; i++)
        visited[i] = false;

    // Call the recursive helper function to print all paths
    result = isConnectedUtil(s, d, visited, path, path_index, depth);
    return result;
};

void Matrix::create()
{

    std::random_device rd;
    std::default_random_engine gen(rd());
    // std::default_random_engine gen;
    std::discrete_distribution<int> nodeType_dist({100, 5, 1});
    std::uniform_real_distribution<double> needfluct_dist(0.0, 3.33); // distribuzione uniforme di fluttuazioni nella richiesta di energia delle case
    std::uniform_real_distribution<double> link_dist(0.0, 1.0);       // distribuzione uniforme per distribuzione dei link, generato come proporzioni programma arcelli
    std::uniform_int_distribution<int> choice_position_in_nodes(0, N - 1);

    Building empty;

    // ----------------------CREAZIONE NODI-----------------------

    for (int k = 0; k < N; ++k)
    {
        int numtype = nodeType_dist(gen); // numtype = type of node

        double fluct = needfluct_dist(gen);
        nodes.push_back(empty);

        if (numtype == 0)
        {
            nodes[k].SetNeed(fluct); // consumo medio giornaliero di una famiglia media in kW.
            House.push_back(k);
        }
        else if (numtype == 1)
        {
            nodes[k].SetType(BuildingType::S);
            nodes[k].SetEfficiency(0.98);
            Sorting.push_back(k);
        }
        else if (numtype == 2)
        {
            nodes[k].SetType(BuildingType::C);
            Centrall.push_back(k); // si sta riempiendo il vettore di Cetral con i posti delle Centrali rispettivi all'array nodes
            // Le centrali hanno un Need in base a quanto immettono nel network
        }

        else
        {
            throw std::runtime_error{"Problem in the number generation"};
        }
    }
    //--------------------CONTROLLI SUI NODI-----------------------

    if (Centrall.size() == 0)
    { // Controllo per non avere un numero nullo di centrali.

        Building newCentral{BuildingType::C, 0, 0};

        int positionofC = 0;
        char Vector_of_element = ' ';
        while (Vector_of_element == ' ')
        {
            positionofC = choice_position_in_nodes(gen);
            if (nodes[positionofC].GetType() == BuildingType::H)
            {
                Vector_of_element = 'H';
            }
            else
            {
                if (Sorting.size() <= 1)
                {
                    Vector_of_element = ' ';
                }
                else
                {
                    Vector_of_element = 'S';
                }
            }
        }

        // Assegnamento del nodo positionofC alla centrale
        nodes[positionofC] = newCentral;

        Centrall.push_back(positionofC);
        std::cout << "Posizione centrale: " << positionofC << "\n";
        int removeposition = 0;

        // Rimozione dell'elemento dal nodo corrispondente

        if (Vector_of_element == 'H')
        {
            for (int y = 0; y < House.size();)
            {

                if (House[y] == positionofC)
                {
                    removeposition = y;

                    break;
                }

                else
                    y++;
            }

            House.erase(House.begin() + removeposition);
        }
        else if (Vector_of_element == 'S')
        {
            for (int y = 0; y < Sorting.size();)
            {

                if (Sorting[y] == positionofC)
                {
                    removeposition = y;

                    break;
                }

                else
                    y++;
            }

            Sorting.erase(Sorting.begin() + removeposition);
        }
    }

    if (Sorting.size() == 0)
    {
        Building newSorting{BuildingType::S, 0, 0};
        int positionofS = 0;

        bool position_of_House_in_nodes = false;

        while (position_of_House_in_nodes == false)
        {
            positionofS = choice_position_in_nodes(gen);
            if (nodes[positionofS].GetType() == BuildingType::H)
            {
                position_of_House_in_nodes = true;
            }
            else
            {
                continue;
            }
        }
        nodes[positionofS] = newSorting;
        Sorting.push_back(positionofS);
        int removeposition = 0;

        for (int y = 0; y < House.size();)
        {

            if (House[y] == positionofS)
            {
                removeposition = y;

                break;
            }

            else
                y++;
        }

        House.erase(House.begin() + removeposition);
        // std::cout << "277 matrix.cpp\n";
    }

    int j = 0; // j è fuori per poter calcolare solo il triangolo superiore della matrice dato che è simmetrica
    int counter = 0;

    if (Sorting.size() > (House.size() / (100 / 15)))
    {
        throw std::runtime_error{"Too little houses for each sorting"};
    }

    //--------------GENERAZIONE MATRICE DI ADIACENZA-----------------------

    int p = N;

    for (int i = 0; i < p; ++i)
    {

        BuildingType node_i = nodes[i].GetType();

        for (j; j < p; ++j)
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
                //------------Casa----------------

                if (node_i == BuildingType::H)
                {
                    if (node_j == BuildingType::H)
                    {
                        //------------Casa-Casa----------------

                        if (rnd <= 0.20) // si suppone che, su 100 case, una casa sia collegata con altre 10.
                        {
                            adj_matrix[i][j].SetType(LinkType::SH); // Link Small Between Houses
                            adj_matrix[j][i].SetType(LinkType::SH);

                            adj_matrix[i][j].SetNumber(1); // link small
                            adj_matrix[j][i].SetNumber(1);

                            nodes[i].SetLinkedHouse(j);
                            nodes[j].SetLinkedHouse(i);
                            // Qui si sta avando ad inserire il nodo i nel percorso di j ed il nodo j nel percorso di i.
                            adj[i].push_back(j);
                            adj[j].push_back(i);
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
                    {
                        //------------Casa-Smistamento----------------
                        if (nodes[i].GetNofSortingLink() == 0)
                        {
                            if (rnd <= 0.15)
                            {
                                adj_matrix[i][j].SetType(LinkType::SS); // Link  Small Between House and Sorting
                                adj_matrix[j][i].SetType(LinkType::SS);

                                adj_matrix[i][j].SetNumber(2);
                                adj_matrix[j][i].SetNumber(2);

                                nodes[i].SetLinkedSorting(j);
                                nodes[j].SetLinkedHouse(i);

                                adj[i].push_back(j);
                                adj[j].push_back(i);
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
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0);
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else if (node_j == BuildingType::C)
                    {
                        //------------Casa-Centrale----------------
                        adj_matrix[i][j].SetType(LinkType::N);
                        adj_matrix[j][i].SetType(LinkType::N);

                        adj_matrix[i][j].SetNumber(0);
                        adj_matrix[j][i].SetNumber(0);
                    }
                    else
                    {
                        throw std::runtime_error{"No Type for this node"};
                    }
                }
                //------------Smistamento----------------
                else if (node_i == BuildingType::S)
                {
                    //------------Smistamento-Casa----------------
                    if (node_j == BuildingType::H)
                    {
                        if (nodes[j].GetNofSortingLink() == 0)
                        {
                            if (rnd <= 0.15)
                            {
                                adj_matrix[i][j].SetType(LinkType::SS);
                                adj_matrix[j][i].SetType(LinkType::SS);

                                adj_matrix[i][j].SetNumber(2);
                                adj_matrix[j][i].SetNumber(2);

                                nodes[i].SetLinkedHouse(j);
                                nodes[j].SetLinkedSorting(i);

                                adj[i].push_back(j);
                                adj[j].push_back(i);
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
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0);
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else if (node_j == BuildingType::S)
                    { //-----------Smistamento-Smistamento----------------
                        if (rnd <= 0.10)
                        {

                            adj_matrix[i][j].SetType(LinkType::M); // Link Medium Between Sorting
                            adj_matrix[j][i].SetType(LinkType::M);

                            adj_matrix[i][j].SetNumber(3);
                            adj_matrix[j][i].SetNumber(3);

                            nodes[i].SetLinkedSorting(j);
                            nodes[j].SetLinkedSorting(i);

                            adj[i].push_back(j);
                            adj[j].push_back(i);
                        }
                        else
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0);
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else if (node_j == BuildingType::C)
                    { //---------Smistamento-Centrale----------------
                        // Se viene fuori una centrale, non si ha un collegamento diretto in quanto si deve avere sempre una certa randomicità.
                        // Per tale motivo si sceglie una centrale tra quelle che si hanno a disposizione, piuttosto che scegliere la j-esima.

                        int rn = 0;
                        if (nodes[i].GetNofCentralLink() == 0)
                        {
                            // SCELTA DELLA CENTRALE A CUI COLLEGARE LO SMISTAMENTO
                            for (int m = 0; m < Centrall.size();)
                            { // Bisogna assicurarsi che rn assume effettivamente il valore di un k corrispondente ad una centrale.
                                rn = choice_position_in_nodes(gen);
                                if (rn == Centrall[m])
                                {
                                    break;
                                }
                                else
                                {
                                    if (m == (Centrall.size() - 1))
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

                            if (rn == j)
                            {
                                adj_matrix[i][j].SetType(LinkType::B); // Big Link Between Sorting and Central
                                adj_matrix[j][i].SetType(LinkType::B);

                                adj_matrix[i][j].SetNumber(4);
                                adj_matrix[j][i].SetNumber(4);

                                nodes[i].SetLinkedCentral(j);
                                nodes[j].SetLinkedSorting(i);

                                adj[i].push_back(j);
                                adj[j].push_back(i);
                            }
                            else // Se j != rn allora bisogna collegare i ad rn ed eliminare il link i-j.
                            {
                                adj_matrix[i][rn].SetType(LinkType::B);
                                adj_matrix[rn][i].SetType(LinkType::B);

                                adj_matrix[i][rn].SetNumber(4);
                                adj_matrix[rn][i].SetNumber(4);

                                nodes[i].SetLinkedCentral(rn);
                                nodes[rn].SetLinkedSorting(i);

                                adj[i].push_back(rn);
                                adj[rn].push_back(i);

                                // Bastano queste righe di codice sottostante per eliminare il collegamento i-j
                                // Si è infatti in fase di generazione non di controlli.

                                adj_matrix[i][j].SetType(LinkType::N);
                                adj_matrix[j][i].SetType(LinkType::N);

                                adj_matrix[i][j].SetNumber(0);
                                adj_matrix[j][i].SetNumber(0);
                            }
                        }
                    }
                    else
                    {
                        throw std::runtime_error{"No Type for this node"};
                    }
                }
                //--------------Centrale------------------

                else if (node_i == BuildingType::C)
                {
                    //---------Centrale-Casa----------------
                    if (node_j == BuildingType::H)
                    {
                        adj_matrix[i][j].SetType(LinkType::N);
                        adj_matrix[j][i].SetType(LinkType::N);

                        adj_matrix[i][j].SetNumber(0);
                        adj_matrix[j][i].SetNumber(0);
                    }
                    else if (node_j == BuildingType::S)
                    {
                        //---------Centrale-Smistamento----------------

                        if (nodes[j].GetNofCentralLink() == 0)
                        {
                            double rn = link_dist(gen);
                            if (rn <= 0.50)
                            {
                                adj_matrix[i][j].SetType(LinkType::B);
                                adj_matrix[j][i].SetType(LinkType::B);

                                adj_matrix[i][j].SetNumber(4);
                                adj_matrix[j][i].SetNumber(4);

                                nodes[i].SetLinkedSorting(j);
                                nodes[j].SetLinkedCentral(i);

                                adj[i].push_back(j);
                                adj[j].push_back(i);
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
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0); // Se lo smistamento è già collegato, non deve avere collegamento con la matrice corrente
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    else if (node_j == BuildingType::C)
                    {
                        //------------CENTRALE-CENTRALE-----------------

                        adj_matrix[i][j].SetType(LinkType::N);
                        adj_matrix[j][i].SetType(LinkType::N);

                        adj_matrix[i][j].SetNumber(0);
                        adj_matrix[j][i].SetNumber(0);
                    }
                    else
                    {
                        throw std::runtime_error{"No Type for this node"};
                    }
                }
                else
                {
                    throw std::runtime_error{"No Type for this node"};
                }
            }
        }
        counter++;
        j = counter;
    }
}

void Matrix::control_for_matrix()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> choice_position_in_nodes(0, N - 1);

    //----------------------CONTROLLI----------------------
    for (int p = 0; p < N;)
    {
        int rn = 0;
        // ----------------------SMISTAMENTO----------------------

        if (nodes[p].GetType() == BuildingType::S) // Per evitare che possa esserci uno smistamento non collegato a ciascuna centrale.
        {
            //-------------CONTROLLI: Smistamento-Centrale-------------------

            if ((nodes[p].GetNofCentralLink() == 0))
            {
                for (int m = 0; m < Centrall.size();)
                {
                    rn = choice_position_in_nodes(gen);
                    if (rn == Centrall[m])
                    {
                        break;
                    }
                    else
                    {
                        if (m == (Centrall.size() - 1))
                        {
                            m = 0;
                        }

                        else
                        {
                            m++;
                        }
                    }
                }

                adj_matrix[p][rn].SetType(LinkType::B);
                adj_matrix[rn][p].SetType(LinkType::B);

                adj_matrix[p][rn].SetNumber(4);
                adj_matrix[rn][p].SetNumber(4);

                nodes[p].SetLinkedCentral(rn);
                nodes[rn].SetLinkedSorting(p);

                adj[p].push_back(rn);
                adj[rn].push_back(p);
            }

            double localLinkH = static_cast<double>(nodes[p].GetNofHouseLink()) / static_cast<double>(House.size());
            double increment = static_cast<double>(1) / static_cast<double>(House.size());

            //-------------CONTROLLI: Smistamento-Casa (CASO POCHI COLLEGAMENTI)-------------------

            if (localLinkH <= 0.07)
            {
                bool full = false;
                int y = 0;
                while (localLinkH <= 0.07 && y < 100)
                {
                    y++;

                    for (int m = 0; (m < House.size());)
                    {
                        rn = choice_position_in_nodes(gen);
                        if (rn == House[m])
                        {
                            if (nodes[p].AlreadyLinked(rn, 'H') == false)
                            {
                                break;
                            }
                            else
                            {
                                if (m == (House.size() - 1))
                                {
                                    m = 0; // risettato a zero per non uscire dallo "scope"
                                }

                                else
                                {
                                    m++;
                                }
                            }
                        }
                        else
                        {
                            if (m == (House.size() - 1))
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

                        adj_matrix[p][rn].SetNumber(2);
                        adj_matrix[rn][p].SetNumber(2); // La matrice è simmetrica

                        nodes[p].SetLinkedHouse(rn);
                        nodes[rn].SetLinkedSorting(p);

                        adj[p].push_back(rn);
                        adj[rn].push_back(p);

                        localLinkH = localLinkH + increment;

                        y++;
                    }

                    // }
                }
            }
            //-------------CONTROLLI: Smistamento-Smistamento-------------------
            // No controlli per ora

            p++;
        }

        //------------------------CASA--------------------------

        else if (nodes[p].GetType() == BuildingType::H)
        {

            double localLinkH = static_cast<double>(nodes[p].GetNofHouseLink()) / static_cast<double>(House.size());
            double increment = static_cast<double>(1) / static_cast<double>(House.size());

            //---------------CONTROLLI: CASA-CASA--------------
            if (localLinkH <= 0.05)
            {

                bool full = false;
                int y = 0;
                while (localLinkH <= 0.05 && full == false)
                {

                    for (int m = 0; m < House.size();)
                    {
                        rn = choice_position_in_nodes(gen);

                        if (rn == House[m])
                        {

                            if (nodes[p].AlreadyLinked(rn, 'H') == false)
                            {

                                break;
                            }
                            else
                            {
                                if (m == (House.size() - 1))
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
                            if (m == (House.size() - 1))
                            {
                                m = 0; // risettato a zero per non uscire dallo "scope" e trovare una casa.
                            }

                            else
                            {
                                m++;
                            }
                        }
                    }
                    double localLinkH_1 = static_cast<double>(nodes[rn].GetNofHouseLink()) / static_cast<double>(House.size());
                    // ma qua non andrebbe getnofsortinglink? perche se no qua è come ricontrollare le case
                    if (localLinkH_1 <= 0.08)
                    {
                        adj_matrix[p][rn].SetType(LinkType::SH);
                        adj_matrix[rn][p].SetType(LinkType::SH);

                        adj_matrix[p][rn].SetNumber(1);
                        adj_matrix[rn][p].SetNumber(1);

                        nodes[p].SetLinkedHouse(rn);
                        nodes[rn].SetLinkedHouse(p);

                        adj[p].push_back(rn);
                        adj[rn].push_back(p);

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
            /* if (localLinkH >= 0.08)
             { // tolgo case se ne ho troppe collegate
                 int rnd = 0;
                 int pippo=0;

                 for (int y = 0; y < 100;)
                 { // in un for cerco nodo e nell'altro collego


                     if (localLinkH <= 0.06)
                     {
                         break;
                     }

                     for (int m = 0; m < House.size();)
                     {
                         rnd = choice_position_in_nodes(gen); // genera numeri interi tra 0 e N-1

                         if (rnd == House[m] && (rnd != p))
                         {

                             if (nodes[p].AlreadyLinked(rnd, 'H') == true) // condizioni per uscire dal ciclo
                             {
                                 pippo++;
                                 std::cout<<pippo<<'\n';
                                 if (nodes[rnd].GetNofHouseLink() > 1)
                                 {

                                     break;
                                 }
                                 else
                                 {
                                     if (m == (House.size() - 1))
                                     {
                                         m = 0; // risettato a zero per non uscire dallo "scope"
                                     }

                                     else
                                     {
                                         m++;
                                     }
                                 }
                             }
                             else
                             {
                                 if (m == (House.size() - 1))
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
                             if (m == (House.size() - 1))
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

                     adj_matrix[p][rnd].SetType(LinkType::N);
                     adj_matrix[rnd][p].SetType(LinkType::N);

                     adj_matrix[p][rnd].SetNumber(0);
                     adj_matrix[rnd][p].SetNumber(0); // La matrice è simmetrica

                     // nodes[p].SetSortingLink(true);

                     // linkCentral++;
                     nodes[p].DeleteLinkedHouse(rnd);
                     nodes[rnd].DeleteLinkedHouse(p);

                     // Bisogna eliminare tali elementi anche dalla lista.
                     // Inizio DELETE IN ADJ
                     adj[p].remove(rnd);
                     adj[rnd].remove(p);
                     // FINE DELETE IN ADJ

                     localLinkH = localLinkH - increment;

                     y++;
                 }
             }*/

            // Potrebbe essere che con il metodo "delete" rimangano dei punti isolati.
            // Lo scopo del passaggio successivo è proprio quello di andare a collegare il povero nodo con il primo smistamento possibile.
            /* else if ((nodes[p].GetType() == BuildingType::H) && (nodes[p].GetNofSortingLink() == 0) && (nodes[p].GetNofHouseLink() == 0))
             {
                 int u=0;
                   for (int m = 0; m < nofSorting;)
                                 { // Bisogna assicurarsi che rn assume effettivamente il valore di un k corrispondente ad una centrale.
                                     u = choice_position_in_nodes(gen);
                                     if (u == Sorting[m])
                                     {
                                         // rn = Centrall[m];
                                         break;
                                     }
                                     else
                                     {
                                         if (m== (nofSorting - 1))
                                         {
                                             m = 0;
                                         } // Non voglio che esca dal loop finchè non ha un valore assegnato.

                                         else
                                         {
                                             m++;
                                         }
                                     }
                                 }



                 adj_matrix[p][u].SetType(LinkType::SS);
                 adj_matrix[u][p].SetType(LinkType::SS);

                 adj_matrix[p][u].SetNumber(2);
                 adj_matrix[u][p].SetNumber(2);

                 nodes[u].SetLinkedHouse(p);
                 nodes[p].SetLinkedSorting(u);

                 adj[p].push_back(u);
                 adj[u].push_back(p);


             }*/

            //-------------------CENTRALE--------------------------------

            else
            {
                p++;
            }
        }
        // Controlli per evitare che vi siano due network indipendenti all'interno di uno

        int counter = 0;
        for (int i = 0; i < N; i++)
        { // casa

            for (int j = 0; j < N; j++)
            { // Centrale 1
                for (int k = 0; k < N; k++)
                { // Centrale 2

                    std::list<int>::iterator find_j = std::find(adj[i].begin(), adj[i].end(), j);
                    std::list<int>::iterator find_k = std::find(adj[i].begin(), adj[i].end(), k);
                    if ((find_j != adj[i].end()) && (find_k != adj[i].end()))
                    {
                        counter++;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        if (counter == 0)
        {
            throw std::runtime_error{"Indipendent network"};
        }
        p++;
    }
}

// Controlli path
void Matrix::control_path()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> choice_position_in_nodes(0, N - 1);
    int counter_for_central_path = 0;
    // CONTROLLO CASA ISOLATA
    for (int p = 0; p < N; p++)
    {

        if (nodes[p].GetType() == BuildingType::S)
        {

            for (int x = 0; x < N; x++)
            {
                if (nodes[x].GetType() == BuildingType::C)
                {
                    if (isConnected(p, x) == true)
                    {
                        counter_for_central_path++;
                    }
                }
            }
            if (counter_for_central_path == 0)
            {
                int rn = 0;
                for (int m = 0; m < Centrall.size();)
                { // Bisogna assicurarsi che rn assume effettivamente il valore di un k corrispondente ad una centrale.
                    rn = choice_position_in_nodes(gen);
                    if (rn == Centrall[m])
                    {
                        break;
                    }
                    else
                    {
                        if (m == (Centrall.size() - 1))
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

                adj_matrix[p][rn].SetNumber(4);
                adj_matrix[rn][p].SetNumber(4);

                nodes[p].SetLinkedCentral(rn);
                nodes[rn].SetLinkedSorting(p);

                adj[p].push_back(rn);
                adj[rn].push_back(p);
            }
        }
        if (nodes[p].GetType() == BuildingType::H)
        {

            if (nodes[p].GetNofHouseLink() == 0)
            {
                int lp = 0;
                for (int i = 0; i < 3; i++)
                {

                    for (int m = 0; m < House.size();)
                    {
                        lp = choice_position_in_nodes(gen);

                        if (lp == House[m])
                        {
                            break;
                        }
                        else
                        {
                            if (m == (House.size() - 1))
                            {
                                m = 0; // risettato a zero per non uscire dallo "scope"
                            }

                            else
                            {
                                m++;
                            }
                        }
                    }
                    adj_matrix[p][lp].SetType(LinkType::SH); // Link Small Between Houses
                    adj_matrix[lp][p].SetType(LinkType::SH);

                    adj_matrix[p][lp].SetNumber(1); // link small
                    adj_matrix[lp][p].SetNumber(1);

                    nodes[p].SetLinkedHouse(lp);
                    nodes[lp].SetLinkedHouse(p);
                    // Qui si sta avando ad inserire il nodo i nel percorso di j ed il nodo j nel percorso di i.
                    adj[lp].push_back(p);
                    adj[p].push_back(lp);
                }
            }

            // Controllo ghetti case
            counter_for_central_path = 0;
            for (int x = 0; x < N; x++)
            {
                if (nodes[x].GetType() == BuildingType::C)
                {
                    if (isConnected(p, x) == true)
                    {
                        counter_for_central_path++;
                    }
                }
            }
            if (counter_for_central_path == 0)
            {
                int rn = 0;
                for (int m = 0; m < Sorting.size();)
                { // Bisogna assicurarsi che rn assume effettivamente il valore di un k corrispondente ad una centrale.
                    rn = choice_position_in_nodes(gen);
                    if (rn == Sorting[m])
                    {
                        break;
                    }
                    else
                    {
                        if (m == (Sorting.size() - 1))
                        {
                            m = 0;
                        } // Non voglio che esca dal loop finchè non ha un valore assegnato.

                        else
                        {
                            m++;
                        }
                    }
                }

                adj_matrix[p][rn].SetType(LinkType::SS);
                adj_matrix[rn][p].SetType(LinkType::SS);

                adj_matrix[p][rn].SetNumber(2);
                adj_matrix[rn][p].SetNumber(2);

                nodes[p].SetLinkedSorting(rn);
                nodes[rn].SetLinkedHouse(p);

                adj[p].push_back(rn);
                adj[rn].push_back(p);
            }
        }
    }
};

int Matrix::getNofHouse() const
{
    return House.size();
};
int Matrix::getNofSorting() const
{
    return Sorting.size();
};
int Matrix::getNofCentral() const
{
    return Centrall.size();
};
Building &Matrix::operator()(int i)
{
    return nodes[i];
};

Link &Matrix::operator()(int i, int j)
{
    return adj_matrix[i][j];
};

// g++ main.cpp matrix.cpp Building.cpp Link.cpp
void Matrix::fillRecords()
{

    std::ifstream inFile;
    inFile.open("adjmatrix.txt");
    if (!inFile)
    {
        std::cout << "Error, unable to open text file \n";
    }
    //  record in;
    int On = 0;
    int row = 0;
    int currentnumber=0;
    // std::cout<<"riga 1231: "<<currentnumber<<" ";
    

    while (currentnumber != -2)
    {  // std::cout<<"riga 1233: "<<currentnumber<<" ";
        inFile >> currentnumber;
        //std::cout<<"riga 1235: "<<currentnumber<<" ";
        if (currentnumber != -1)
        {
            records[row].push_back(currentnumber); // store row in datastructure at the option number.
            //std::cout<<"riga 1239: "<<currentnumber<<" ";
            On++;
        }
        else
        {   //std::cout<<"\n";
            row++;
        }
    }
}
void Matrix::PrintforRecords()
{
    for (int i = 0; i < records.size(); i++)
    {
        for (int j = 0; j < records[i].size(); j++)
        {
            std::cout<<records[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}

void Matrix::transient()
{
    int totalNeed = 0;

    for (int i = 0; i < N; i++)
    {
        Building current_node = nodes[i];
        BuildingType current_node_type = nodes[i].GetType();
        if (current_node_type == BuildingType::S)
        {
            double localLinkH = static_cast<double>(current_node.GetNofHouseLink()) / static_cast<double>(House.size());

            if (localLinkH <= 0.40)
            {
                // max need for each house: 3.33W
                nodes[i].SetNeed(0.33);
            }
            else if (localLinkH <= 0.80)
            {
                nodes[i].SetNeed(0.73);
            }
            else
            {
                nodes[i].SetNeed(1.0);
            }
        }
    }

    // FOR DI CONTROLLO TOTAL NEED

    for (int i = 0; i < N; i++)
    {
        Building current_node = nodes[i];
        BuildingType current_node_type = nodes[i].GetType();
        if ((current_node_type == BuildingType::H) ||
            (current_node_type == BuildingType::S))
        {
            totalNeed += current_node.GetNeed();
        }

        for (int j = 0; j < N; j++)
        {
            Link current_link = adj_matrix[i][j];
            LinkType current_link_type = current_link.GetType();
            if ((current_link_type == LinkType::N) ||
                (current_link_type == LinkType::SH) || (current_link_type == LinkType::SS) ||
                (current_link_type == LinkType::M) || (current_link_type == LinkType::B))
            {
                continue;
            }
            else
            {
                throw std::runtime_error{"No type for current link"};
            }
        }
    }

    /*for (int i = 0; i < N; i++)
    {
        BuildingType current_node_type = nodes[i].GetType();
        double current_node_need = nodes[i].GetNeed();
        if (current_node_type == BuildingType::H)
        {
            for(int p=0)


        }
    }*/
}
