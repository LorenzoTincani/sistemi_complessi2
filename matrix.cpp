#include "matrix.h"
Matrix::Matrix(int n) : N(n), adj_matrix(N, std::vector<Link>(N)), nodes{}
{
    if (N <= 0)
    {
        throw std::runtime_error{"N must be bigger than 1"};
    }
}
void Matrix::printAllPathsUtil(int u, int d, bool visited[],
                               int path[], int &path_index, std::vector<std::vector<int>> &local)
{
    // std::cout << " 19 matrix.cpp\n";
    //  Mark the current node and store it in path[]
    //  Se il nodo è visitato, il suo indice va aggiunto all'interno dell'array path, incrementato la posizione per il cammino successivo.
    visited[u] = true;
    path[path_index] = u;
    path_index++;
    std::vector<int> current_path{};
    // If current vertex is same as destination, then print

    if (u == d)
    {

        for (int i = 0; i < path_index; i++)
        {
            int index = path[i];
            // std::cout << path[i] << " ";
            current_path.push_back(path[i]);
        }
        local.push_back(current_path);
    }

    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        std::list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (!visited[*i])

                printAllPathsUtil(*i, d, visited, path, path_index, local);
    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;
    // std::cout << "47 matrix.cpp\n";
    // adjmatrix.close();
};

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
void Matrix::printAllPaths(int s, int d, std::vector<std::vector<int>> &local)
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
    printAllPathsUtil(s, d, visited, path, path_index, local);
};

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

void Matrix::findIsolated(int starting_building, std::vector<int> building_to_scan, std::vector<int> &local_linked_building)
{
    local_linked_building.clear();
    // 19.07.2022: da riguardare gli iteratori, in quanto creano un core dump
    // int position_first_central = 0;
    // std::vector<int> linked_building{};
    std::vector<int> currently_linked{};
    std::vector<int> local{}; // vettore fantoccio, serve solo per immagazinare i dati nel loop
                              // int last_iteration_size = 1;
    int size_i = 0;
    int size_ii = 0;

    /*for (int i = 0; i < N; i++)
    {
        if (nodes[i].GetType() == BuildingType::C)
        {
            position_first_central = i;
            break;
        }
    }*/

    local_linked_building.push_back(starting_building);
    // std::cout << local_linked_building[0] << "\n";
    // Al primo giro starting_building sarà una centrale.
    currently_linked.push_back(starting_building);
    size_ii++;
    int f = 0;
    while (size_i != size_ii)
    {
        f++;

        // std::cout << "ciclo:" << f << "\n";
        size_i = local_linked_building.size();

        //   std::cout << "currently_linked.size() 232: " << currently_linked.size() << "\n";

        for (int i = 0; i < currently_linked.size(); i++)
        {
            // std::cout << "currently_linked[i]: " << currently_linked[i] << "\n";
            local.clear();

            for (int j = 0; j < building_to_scan.size(); j++) // fai condizione per cui j sia tra i builsing contenuti in building_to_scan
            {

                auto it1 = adj[currently_linked[i]].begin(); // guarda se j è tra i nodes collegat a i
                auto it2 = adj[currently_linked[i]].end();
                auto it3 = std::find(it1, it2, building_to_scan[j]);

                if (it3 != it2)
                {
                    auto it4 = local_linked_building.begin(); // guarada se j è gia dentro a linked_builing
                    auto it5 = local_linked_building.end();
                    auto it6 = std::find(it4, it5, building_to_scan[j]);
                    if (it6 == it5) // se non esiste, fa il push_back
                    {

                        local_linked_building.push_back(building_to_scan[j]);
                        local.push_back(building_to_scan[j]);
                    }
                }
            }
            // std::cout << "££££££££££££££££££££££££££££££££££\n";

            /*  for (int p = 0; p < local.size(); p++)
              {
                  // std::cout << "Iterazione n." << i << "\n";
                  std::cout << local[p] << "-"<<"\n";
              }*/
            // std::cout << "££££££££££££££££££££££££££££££££££\n";

            //  currently_linked = local; // not so sure 'bout this, potrebbe dare problemi
        }
        currently_linked.clear();
        currently_linked = local;

        // std::cout << "currently_linked.size() 276: " << currently_linked.size() << "\n";
        size_ii = local_linked_building.size();
    }
    auto itlinkedI = local_linked_building.begin();
    auto itlinkedII = local_linked_building.end();
    std::sort(itlinkedI, itlinkedII);
    /* for (int i = 0; i < linked_building.size(); i++)
     {
         std::cout << linked_building[i] << " ";
     }*/

    /*for (int p = 0; p < local_linked_building.size(); p++)
    {

        std::cout << local_linked_building[p] << "_"
                  << "\n";
    }*/
    // return local_linked_building;
}
void Matrix::PrintNodes() const
{
    for (int i = 0; i < N; i++)
    {
        if (nodes[i].GetType() == BuildingType::H)
        {
            std::cout << "Casa: " << i << "\n";
        }
        if (nodes[i].GetType() == BuildingType::C)
        {
            std::cout << "Centrale: " << i << "\n";
        }
        if (nodes[i].GetType() == BuildingType::S)
        {
            std::cout << "Smistamento: " << i << "\n";
        }
    }
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

    Building empty{};

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

        int removeposition = 0;

        // Rimozione dell'elemento dal nodo corrispondente

        if (Vector_of_element == 'H')
        {

            auto it_1 = House.begin();
            auto it_2 = House.end();
            auto it_find = std::find(it_1, it_2, positionofC);
            if (it_find != it_2)
            {
                House.erase(it_find);
            }
            else
            {
                throw std::runtime_error{"Casa da rimuovere non trovata"};
            }
        }
        else if (Vector_of_element == 'S')
        {
            auto it_1 = Sorting.begin();
            auto it_2 = Sorting.end();
            auto it_find = std::find(it_1, it_2, positionofC);
            if (it_find != it_2)
            {
                Sorting.erase(it_find);
            }
            else
            {
                throw std::runtime_error{"Casa da rimuovere non trovata"};
            }
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

        auto it_1 = House.begin();
        auto it_2 = House.end();
        auto it_find = std::find(it_1, it_2, positionofS);
        if (it_find != it_2)
        {
            House.erase(it_find);
        }
        else
        {
            throw std::runtime_error{"Casa da rimuovere non trovata"};
        }

        // std::cout << "277 matrix.cpp\n";
    }

    int j = 0; // j è fuori per poter calcolare solo il triangolo superiore della matrice dato che è simmetrica
    int counter = 0;

    if (Sorting.size() > (House.size() / (100 / 15)))
    {
        throw std::runtime_error{"Too little houses for each sorting"};
    }
    if ((Sorting.size() / House.size()) > 1 / 40)
    {
        throw std::runtime_error{"Too many houses for each sorting"};
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

                        if (rnd <= (1) / (House.size() * House.size())) // diminuto di 3 ordini di gandezza
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
                            if (rnd <= (0.01) / (Sorting.size() * Sorting.size()))
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
                    /*if (node_j == BuildingType::H)
                    {
                        if (nodes[j].GetNofSortingLink() == 0)
                        {
                            if (rnd <= (0.01)/(House.size()))
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
                        }*/

                    if (node_j == BuildingType::S)
                    { //-----------Smistamento-Smistamento----------------
                        if (rnd <= 0.05)
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
                        else
                        {
                            adj_matrix[i][j].SetType(LinkType::N);
                            adj_matrix[j][i].SetType(LinkType::N);

                            adj_matrix[i][j].SetNumber(0);
                            adj_matrix[j][i].SetNumber(0);
                        }
                    }
                    /*   else
                       {
                           throw std::runtime_error{"No Type for this node"};
                       }*/
                }
                //--------------Centrale------------------

                else if (node_i == BuildingType::C)
                {
                    //---------Centrale-Casa----------------
                    /* if (node_j == BuildingType::H)
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
                     }*/
                    if (node_j == BuildingType::C)
                    {
                        //------------CENTRALE-CENTRALE-----------------

                        adj_matrix[i][j].SetType(LinkType::N);
                        adj_matrix[j][i].SetType(LinkType::N);

                        adj_matrix[i][j].SetNumber(0);
                        adj_matrix[j][i].SetNumber(0);
                    }
                    /* else
                     {
                         throw std::runtime_error{"No Type for this node"};
                     }*/
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
    for (int p = 0; p < N; p++)
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

            if (localLinkH <= 1 / 50) // 0.000007
            {

                bool full = false;
                int y = 0;
                while ((localLinkH <= 1 / 50) && y < 100)
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

                    if (nodes[rn].GetNofSortingLink() == 0) // La casa può essere collegata solo ad uno smistamento
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
            if (localLinkH <= (1) / (House.size())) // 5e-7
            {

                bool full = false;
                int y = 0;
                while (localLinkH <= (1) / (House.size()) && full == false)
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
                    if (localLinkH_1 <= (1) / (House.size())) // 8e-8
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
            // Nel caso vi siano più collegamenti.
            else
            {
                while(localLinkH <= (3) / (House.size())){

                int rn = 0;
                for (int m = 0; m < House.size();)
                {
                    rn = choice_position_in_nodes(gen);

                    if ((nodes[rn].GetType() == BuildingType::H) && (nodes[p].AlreadyLinked(rn, 'H')))
                    {
                        break;
                    }
                    else
                    {
                        if (m == (House.size() - 1))
                        {
                            m = 0;
                        }

                        else
                        {
                            m++;
                        }
                    }
                }

                adj_matrix[p][rn].SetType(LinkType::N);
                adj_matrix[rn][p].SetType(LinkType::N);

                adj_matrix[p][rn].SetNumber(0);
                adj_matrix[rn][p].SetNumber(0);

                /* nodes[j].DeleteLinkedCentral(i);
                 nodes[i].DeleteLinkedHouse(j);*/

                auto it1_p = adj[p].begin();
                auto it2_p = adj[p].end();
                auto find_p = std::find(it1_p, it2_p, rn);

                if (find_p != it2_p)
                {

                    adj[p].erase(find_p);
                }
                auto it1_rn = adj[rn].begin();
                auto it2_rn = adj[rn].end();
                auto find_rn = std::find(it1_rn, it2_rn, p);
                if (find_rn != it2_rn)
                {
                    adj[rn].erase(find_rn);
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

            // std::cout<<"Esce a 1014\n";
        }
    }
}

void Matrix::control_for_matrix2()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> choice_position_in_nodes(0, N - 1);
    for (int i = 0; i < N; i++)
    {
        Building B_i = nodes[i];
        for (int j = 0; j < N; j++)
        {
            Building B_j = nodes[j];
            if (B_i.GetType() == BuildingType::H && B_j.GetType() == BuildingType::C)
            {
                if (adj_matrix[i][j].GetType() != LinkType::N)
                {
                    adj_matrix[i][j].SetType(LinkType::N);
                    adj_matrix[j][i].SetType(LinkType::N);

                    adj_matrix[i][j].SetNumber(0);
                    adj_matrix[j][i].SetNumber(0);

                    /*nodes[i].DeleteLinkedHouse(j);
                    nodes[j].DeleteLinkedHouse(i);*/

                    auto it1_i = adj[i].begin();
                    auto it2_i = adj[i].end();
                    auto find_i = std::find(it1_i, it2_i, j);
                    if (find_i != it2_i)
                    {
                        adj[i].erase(find_i);
                    }
                    auto it1_j = adj[j].begin();
                    auto it2_j = adj[j].end();
                    auto find_j = std::find(it1_j, it2_j, i);
                    if (find_j != it2_j)
                    {
                        adj[j].erase(find_j);
                    }

                    int rn = 0;
                    for (int m = 0; m < Sorting.size();)
                    {
                        rn = choice_position_in_nodes(gen);
                        if (rn == Sorting[m])
                        {
                            std::cout << "SMISTAMENTO SOSPETTO: " << rn << "\n";
                            break;
                        }
                        else
                        {
                            if (m == (Sorting.size() - 1))
                            {
                                m = 0;
                            }

                            else
                            {
                                m++;
                            }
                        }
                    }

                    // Collegamento casa smistamento

                    adj_matrix[i][rn].SetType(LinkType::SS);
                    adj_matrix[rn][i].SetType(LinkType::SS);

                    if (!(nodes[i].AlreadyLinked(rn, 'S')))
                    {
                        nodes[i].SetLinkedSorting(rn);
                        adj[i].push_back(rn);
                    }
                    if (!(nodes[rn].AlreadyLinked(i, 'H')))
                    {
                        nodes[rn].SetLinkedHouse(i);
                        adj[rn].push_back(i);
                    }

                    // Collegamento centrale smistamento

                    adj_matrix[j][rn].SetType(LinkType::B);
                    adj_matrix[rn][j].SetType(LinkType::B);

                    if (!(nodes[j].AlreadyLinked(rn, 'S')))
                    {
                        nodes[j].SetLinkedSorting(rn);
                        adj[j].push_back(rn);
                    }
                    if (!(nodes[rn].AlreadyLinked(j, 'C')))
                    {
                        nodes[rn].SetLinkedCentral(j);
                        adj[rn].push_back(j);
                    }
                }
            }
        }
    }
};
void Matrix::PrintADJmatrix() const
{
    std::cout << "\n";
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            if (adj_matrix[i][k].GetType() == LinkType::N) // null
            {
                printf("\033[33m0 ");
                // ADJmatrix[i].push_back(0);
            }
            else if (adj_matrix[i][k].GetType() == LinkType::SH) // hh
            {
                // std::cout << "       ";
                printf("\033[31m1 ");
                // ADJmatrix[i].push_back(1);
                // ADJmatrix[i][k]=1;
            }
            else if (adj_matrix[i][k].GetType() == LinkType::SH_1) // hh
            {
                // std::cout << "       ";
                printf("\033[31m1 ");
                // ADJmatrix[i].push_back(1);
                // ADJmatrix[i][k]=1;
            }
            else if (adj_matrix[i][k].GetType() == LinkType::SH_2) // hh
            {
                // std::cout << "       ";
                printf("\033[31m1 ");
                // ADJmatrix[i].push_back(1);
                // ADJmatrix[i][k]=1;
            }
            else if (adj_matrix[i][k].GetType() == LinkType::SH_3) // hh
            {
                // std::cout << "       ";
                printf("\033[31m1 ");
                // ADJmatrix[i].push_back(1);
                // ADJmatrix[i][k]=1;
            }
            else if (adj_matrix[i][k].GetType() == LinkType::SS)
            { // hs
                printf("\033[37m2 ");
                // ADJmatrix[i][k]=1;
            }
            else if (adj_matrix[i][k].GetType() == LinkType::M)
            {
                // std::cout << "       ";
                printf("\033[32m3 ");
                //   ADJmatrix[i].push_back(1);
                // ADJmatrix[i][k]=1;
            }
            else if (adj_matrix[i][k].GetType() == LinkType::B) // cs
            {
                // std::cout << "       ";
                printf("\033[36m4 ");
                // ADJmatrix[i][k]=1;
            }

            else
            { // E' giusto vedere se viene generato qualche numero che non sia tra quelli contemplati.
                printf("\033[35m7 ");
            }
            printf("\033[0m");
        }

        std::cout << std::endl;
    }
}

// Controlli path
void Matrix::control_path()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> choice_position_in_nodes(0, N - 1);

    /* std::cout << "Entrato 1053\n";
     std::random_device rd;
     std::default_random_engine gen(rd());
     std::uniform_int_distribution<int> choice_position_in_nodes(0, N - 1);
     int counter_for_central_path = 0;
     // CONTROLLO BUILDING ISOLATA
     for (int p = 0; p < N; p++)
     {
         std::cout << "Ciclo n: " << p << "\n";
         if (nodes[p].GetType() == BuildingType::S)
         {

             for (int x = 0; x < N; x++)
             {
                 if (nodes[x].GetType() == BuildingType::C)
                 {
                     if (isConnected(p, x) == true) // quiiiiii
                     {
                         counter_for_central_path++;
                     }
                 }
             }
             std::cout << "Entrato 1070\n";
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
             std::cout << "Entrato 1151\n";
             // Controllo ghetti case
             counter_for_central_path = 0;
             for (int x = 0; x < N || counter_for_central_path == 0; x++)
             {
                 std::cout << "Entrato 1155\n";
                 if (nodes[x].GetType() == BuildingType::C)
                 {
                     std::cout << "trovato centrale\n";
                     if (isConnected(p, x) == true)
                     {
                         std::cout << "sono collegati\n";
                         counter_for_central_path++;
                     }
                 }
             }
             std::cout << "Entrato 1168\n";
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
         std::cout << "Numero ciclo: " << p << "\n";
     }
     std::cout << "esce a 1204\n";*/
    //  std::vector<int> connected_buildings = Matrix::findIsolated();
    int position_first_central = 0;

    for (int i = 0; i < N; i++)
    {
        if (nodes[i].GetType() == BuildingType::C)
        {
            position_first_central = i;
            break;
        }
    }

    std::vector<int> nodes_int{};
    for (int i = 0; i < N; i++)
    {
        nodes_int.push_back(i);
    }

    std::cout << "\n-------LINKED BUILDING APPENA NATO----------\n";

    findIsolated(position_first_central, nodes_int, linked_building);
    for (int i = 0; i < linked_building.size(); i++)
    {
        std::cout << linked_building[i] << " ";
    }
    std::cout << "\n------------------------\n";
 

    if (linked_building.size() != N)
    {
        std::vector<int> non_linked_building{};
        for (int i = 0; i < N; i++)
        {
            auto it1 = linked_building.begin();
            auto it2 = linked_building.end();
            auto it3 = std::find(it1, it2, i);
            if (it3 == it2)
            {
                non_linked_building.push_back(i);
            }
        }
        std::cout << "------------Building non collegati---------------------\n";

        std::cout << "\n";
        int counter = 0;
        std::vector<int> non_linked_building_local{};
        non_linked_building_local = non_linked_building;
        while (non_linked_building_local.size() != 0)
        {

            //  std::cout<<"iterazione n. "<<counter<<non_linked_building.size()<<"\n";

            // creare vector non linked buildin e while qui

            counter++;
            non_linked_building.clear();

            findIsolated(non_linked_building_local[0], non_linked_building_local, non_linked_building); // nonlinked building dopo la prima iterazione diventa il vettore che ha i nodes collegati al primo oggetto che passo alla funzione
                                                                                                        /* for (int k = 0; k < non_linked_building.size(); k++)
                                                                                                         {
                                                                                                             std::cout << non_linked_building[k] << " ";
                                                                                                         }
                                                                                                         std::cout << "\n";*/
            if (nodes[non_linked_building_local[0]].GetType() == BuildingType::H)
            {

                int rn = 0;
                for (int m = 0; m < linked_building.size();)
                { // Bisogna assicurarsi che rn assume effettivamente il valore di un k corrispondente ad una centrale.
                    rn = choice_position_in_nodes(gen);
                    if ((rn == linked_building[m]) && (nodes[m].GetType() == BuildingType::H)&&!(nodes[non_linked_building_local[0]].AlreadyLinked(rn,'H')))
                    {
                        break;
                    }
                    else
                    {
                        if (m == (linked_building.size() - 1))
                        {
                            m = 0;
                        } // Non voglio che esca dal loop finchè non ha un valore assegnato.

                        else
                        {
                            m++;
                        }
                    }
                }

                adj_matrix[non_linked_building_local[0]][rn].SetType(LinkType::SH); // Link Small Between Houses
                adj_matrix[rn][non_linked_building_local[0]].SetType(LinkType::SH);

                adj_matrix[non_linked_building_local[0]][rn].SetNumber(1); // link small
                adj_matrix[rn][non_linked_building_local[0]].SetNumber(1);

                nodes[non_linked_building_local[0]].SetLinkedHouse(rn);
                nodes[rn].SetLinkedHouse(non_linked_building_local[0]);
                // Qui si sta avando ad inserire il nodo i nel percorso di j ed il nodo j nel percorso di i.
                adj[non_linked_building_local[0]].push_back(rn);
                adj[rn].push_back(non_linked_building_local[0]);
            }
            /*else if (nodes[non_linked_building_local[0]].GetType() == BuildingType::S)
            {
                throw std::runtime_error{"Isolated sorting"};
            }
            else
            {
                throw std::runtime_error{"Isolated central"};
            }*/
            std::cout << "------------non_linked_building-----------\n";

            for (int s = 0; s < non_linked_building.size(); s++)
            {

                auto itFindI = non_linked_building_local.begin();
                auto itFindII = non_linked_building_local.end();
                auto find = std::find(itFindI, itFindII, non_linked_building[s]);

                if (find == itFindII)
                {

                    throw std::runtime_error{"Il metodo non fuunziona come dovrebbe"};
                }
                else
                {
                    std::cout << "erase: " << *find << "\n";
                    non_linked_building_local.erase(find);
                    int o = *find;

                    linked_building.push_back(non_linked_building[s]);
                }
            }
            std::cout << "-------------- ciclo: " << counter << "esimo ------------ \n";
        }
    }
    auto itI = linked_building.begin();
    auto itII = linked_building.end();
    std::sort(itI, itII);

    /* for (int i=0; i;i++){

                 auto it1 = adj[currently_linked[i]].begin(); // guarda se j è tra i nodes collegat a i
                 auto it2 = adj[currently_linked[i]].end();
                 auto it3 = std::find(it1, it2, building_to_scan[j]);

     }*/

    for (int i = 0; i < Centrall.size(); i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (nodes[j].GetType() != BuildingType::S)
            {

                LinkType Type_i = adj_matrix[j][i].GetType();
                int rn = 0;
                if (Type_i != LinkType::N)
                {

                    std::cout << "è passato da 1582\n";

                    for (int m = 0; m < Sorting.size();)
                    {
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
                            }

                            else
                            {
                                m++;
                            }
                        }
                    }

                    // Collegamento casa smistamento

                    adj_matrix[j][rn].SetType(LinkType::SS);
                    adj_matrix[rn][j].SetType(LinkType::SS);

                    adj_matrix[j][rn].SetNumber(2);
                    adj_matrix[rn][j].SetNumber(2);

                    nodes[j].SetLinkedSorting(rn);
                    nodes[rn].SetLinkedHouse(j);

                    adj[j].push_back(rn);
                    adj[rn].push_back(j);

                    // delete casa centrale

                    adj_matrix[i][j].SetType(LinkType::N);
                    adj_matrix[j][i].SetType(LinkType::N);

                    adj_matrix[i][j].SetNumber(0);
                    adj_matrix[j][i].SetNumber(0);

                    /* nodes[j].DeleteLinkedCentral(i);
                     nodes[i].DeleteLinkedHouse(j);*/

                    auto it1_i = adj[i].begin();
                    auto it2_i = adj[i].end();
                    auto find_i = std::find(it1_i, it2_i, j);
                    std::cout << "è passato da 1637\n";
                    if (find_i != it2_i)
                    {
                        std::cout << "Trovato i in j\n";
                        adj[i].erase(find_i);
                    }
                    auto it1_j = adj[j].begin();
                    auto it2_j = adj[j].end();
                    auto find_j = std::find(it1_j, it2_j, i);
                    if (find_j != it2_j)
                    {
                        std::cout << "Trovato j in i\n";
                        adj[j].erase(find_j);
                    }

                    // throw std::runtime_error("Big Link tra casa e centrale");
                }
            }
        }
    }
};

void Matrix::PrintLinkedBuilding() const
{

    for (int i = 0; i < linked_building.size(); i++)
    {
        std::cout << linked_building[i] << " ";
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
    int currentnumber = 0;
    while (currentnumber != -2)
    {

        inFile >> currentnumber;

        if (currentnumber != -1)
        {
            records[row].push_back(currentnumber); // store row in datastructure at the option number.
            On++;
        }
        else
        { // std::cout<<"\n";
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
            std::cout << records[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Matrix::transient()
{
    int totalNeed = 0;
    int counter_0 = 0;
    int counter_1 = 0;
    int counter_2 = 0;
    int counter_3 = 0;
    int counter_4 = 0;
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
    std::vector<std::vector<int>> local_path{};

    for (int i = 0; i < N; i++)
    {
        Building current_node = nodes[i];
        BuildingType current_node_type = nodes[i].GetType();
        double current_node_need = nodes[i].GetNeed();

        //----------------RIEMPIMENTO DI LOCAL_PATH------------
        if (current_node_type != BuildingType::C) // nodo di partenza
        {
            local_path.clear();
            for (int j = 0; j < N; j++)
            {
                if (nodes[j].GetType() == BuildingType::C) // nodo di arrivo, una centrale
                {
                    printAllPaths(i, j, local_path);
                }
            }
            for (int k = 0; k < local_path.size(); k++)
            {
                std::cout << "path n. " << i << "\n";
                for (int l = 0; l < local_path[k].size(); l++)
                {
                    std::cout << local_path[k][l] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "fine path n. " << i << "\n";
        }

        std::sort(local_path.begin(), local_path.end(), [](const std::vector<int> &a, const std::vector<int> &b)
                  { return a.size() < b.size(); });
        current_node.SetPath(local_path);

        //----------Inizio dinamica-------------------
        double path_resistence = 0.;
        double path_current = 0.0;

        for (int b = 0; b < current_node.GetPathNunmber(); b++)
        {
            std::vector<int> current_path = current_node.GetPath_i(b);
            for (int h = 0; h < current_path.size() - 1; h++)
            {
                int a_1 = current_path[h]; // a_1 e a_2 sono nodi consecutivi
                int a_2 = current_path[h + 1];
                LinkType link_type = adj_matrix[a_1][a_2].GetType();
                // std::cout << a_1 << "-" << a_2 << "-";

                if (link_type == LinkType::N) // null
                {
                    counter_0++;
                    // continue;
                }
                else if ((link_type == LinkType::SH) || (link_type == LinkType::SH_1) ||
                         (link_type == LinkType::SH_2) || (link_type == LinkType::SH_3)) // hh
                {
                    counter_4++;
                    path_resistence += 4;
                }
                else if (link_type == LinkType::SS) // sh
                {
                    path_resistence += 3;
                    counter_3++;
                }
                else if (link_type == LinkType::M) // ss
                {
                    path_resistence += 2;
                    counter_2++;
                }
                else if (link_type == LinkType::B) // cs
                {
                    path_resistence += 1;
                    counter_1++;
                }
                else
                { // E' giusto vedere se viene generato qualche numero che non sia tra quelli contemplati.

                    throw std::runtime_error{"no link type"};
                }
            }

            path_current = current_node_need / path_resistence;
            //-------divisione corrente nei link di un path
            for (int h = 0; h < current_path.size() - 1; h++)
            {
                int a_1 = current_path[h]; // a e b sono due path consecutivi
                int a_2 = current_path[h + 1];

                bool overload = adj_matrix[a_1][a_2].SetLoad(path_current);
                if (overload)
                {
                    switch (adj_matrix[a_1][a_2].GetType())
                    {
                    case LinkType::SH:
                        adj_matrix[a_1][a_2].SetType(LinkType::SH_1);
                        break;
                    case LinkType::SH_1:
                        adj_matrix[a_1][a_2].SetType(LinkType::SH_2);
                        break;
                    case LinkType::SH_2:
                        adj_matrix[a_1][a_2].SetType(LinkType::SH_3);
                        break;
                    }
                    overload = adj_matrix[a_1][a_2].SetLoad(0);
                }
                if (overload)
                {
                    throw std::runtime_error{"Link critico"};
                    continue;
                }
            }
            path_resistence = 0;
            path_current = 0;
        }
        std::cout << "\n";
    }

    std::cout << "COUNTER: \n"
              << "casa-casa: " << counter_4 << "\n casa-smistamento: " << counter_3 << "\n smistamento-smistamento: " << counter_2 << "\n centrale-smistamento: " << counter_1 << "\n nulli: " << counter_0 << " \n";
}
void Matrix::PrintADJLoad() const
{
    std::cout << "\n";
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            std::cout << adj_matrix[i][k].GetLoad() << " "; // null
        }

        std::cout << std::endl;
    }
};
void Matrix::evolve()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> choice_position_in_nodes(0, N - 1);
    int a = 0;
    int b = 0;
    bool condition = true;
    while (condition)
    {
        a = choice_position_in_nodes(gen);
        b = choice_position_in_nodes(gen);
        if ((adj_matrix[a][b].GetType() != LinkType::B) &&
            (adj_matrix[a][b].GetType() != LinkType::M) &&
            (adj_matrix[a][b].GetType() != LinkType::SS) &&
            (adj_matrix[a][b].GetType() != LinkType::N))
        {
            condition = false;
        }
    }

    adj_matrix[a][b].SetType(LinkType::N);
    adj_matrix[b][a].SetType(LinkType::N);

    adj_matrix[a][b].SetNumber(0);
    adj_matrix[b][a].SetNumber(0);

    nodes[a].DeleteLinkedHouse(b);
    nodes[b].DeleteLinkedHouse(a);
    std::cout << "1778\n";

    auto it1_a = adj[a].begin();
    auto it2_a = adj[a].end();
    auto find_a = std::find(it1_a, it2_a, b);
    if (find_a != it2_a)
    {
        std::cout << "Trovato b in a\n";
        adj[a].erase(find_a);
    }
    auto it1_b = adj[b].begin();
    auto it2_b = adj[b].end();
    auto find_b = std::find(it1_b, it2_b, a);
    if (find_b != it2_b)
    {
        adj[b].erase(find_b);
    }

    // ricalcolare i path

    std::vector<std::vector<int>> local_path{};

    for (int i = 0; i < N; i++)
    {

        Building current_node = nodes[i];
        BuildingType current_node_type = nodes[i].GetType();
        double current_node_need = nodes[i].GetNeed();

        //----------------RIEMPIMENTO DI LOCAL_PATH------------

        nodes[i].DeleteAllPaths();

        if (current_node_type != BuildingType::C) // nodo di partenza
        {
            local_path.clear();
            for (int j = 0; j < N; j++)
            {
                if (nodes[j].GetType() == BuildingType::C) // nodo di arrivo, una centrale
                {
                    printAllPaths(i, j, local_path);
                }
            }
            std::sort(local_path.begin(), local_path.end(), [](const std::vector<int> &a, const std::vector<int> &b)
                      { return a.size() < b.size(); });
            current_node.SetPath(local_path);
        }

        // rifare un simil-transiente senza però riadattare i link al load

        // tutto questo dentro un while finchè no si ragguinge l' equilibrio (magari nel main(?))
    }
}
