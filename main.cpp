#include "Building.h"
#include "Link.h"
#include "matrix.h"
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
- 2 = casa - smistamento
- 3 = smistamento - centrale
- 4 = smistamento-centrale
 **************************************************************  */
int main()
{
    int N = 50;
    Matrix adjiacency_matrix{N};
    adjiacency_matrix.create();
    adjiacency_matrix.PrintNodes();

    adjiacency_matrix.control_for_matrix();
    std::ofstream adjmatrix;
    adjmatrix.open("adjmatrix.txt"); // Viene creato un file di nome "adjmatrix.txt"
    std::cout << "--------------PRIMA---------------\n";
    for (int i = 0; i < N; i++)
    {
        if (adjiacency_matrix(i).GetType() != BuildingType::C)
        {

            for (int j = 0; j < N; j++)
            {
                if (adjiacency_matrix(j).GetType() == BuildingType::C)
                {
                    adjiacency_matrix.printAllPaths(i, j, adjmatrix);
                }
            }
        }
    }

    adjiacency_matrix.control_for_matrix2();
   // adjiacency_matrix.control_path();
   std::cout<<"\n";
   std::cout<<"\n";
   std::cout<<"\n";
   std::cout<<"\n";

    std::cout << "--------------DOPO---------------\n";
    for (int i = 0; i < N; i++)
    {
        if (adjiacency_matrix(i).GetType() != BuildingType::C)
        {

            for (int j = 0; j < N; j++)
            {
                if (adjiacency_matrix(j).GetType() == BuildingType::C)
                {
                    adjiacency_matrix.printAllPaths(i, j, adjmatrix);
                }
            }
        }
    }

    /*std::cout << "---------------------Linked Building FINALE-----------:\n";
    adjiacency_matrix.PrintLinkedBuilding();
    adjiacency_matrix.PrintADJmatrix();
    adjiacency_matrix.transient();
    adjiacency_matrix.PrintADJLoad();*/

    // adjiacency_matrix.evolve();

    /*   int nofHouselinkedS = 0;
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
       std::cout << "H con tasso di collegamento basso: " << condition_house_min << " su " << nofHouse << std::endl;
       std::cout << "H con tasso di collegamento elevato: " << condition_house_max << " su " << nofHouse << std::endl;
       std::cout << "H con tasso di collegamento corretto: " << condition_house_ok << " su " << nofHouse << std::endl;

       // std::cout << "nofCentralLink :" << linkCentral << "\n";

       // ********************SCRITTURA MATRICE SU FILE******************


       */
    // std::ofstream adjmatrix;
    // adjmatrix.open("adjmatrix.txt"); // Viene creato un file di nome "adjmatrix.txt"
    /*for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            adjmatrix << adj_matrix[i][j].GetNumber(); // Vengono scritti i numeri indentati, in modo da avere la visione della matrice
            adjmatrix << " ";
        }
        adjmatrix << std::endl;
    }
    adjmatrix.close();*/
}

// andando a controllare gli argomenti della list relativi a quel nodo e guardare se nessuno arriva a una centrale, se è cosi
//  creare un path diretto che lo colleghi con uno smistamento a caso
// Link casa-smistamento

// Inserisci in tutto il codice gli attributi dei Building,

// fare pathSorting() in matrix.cpp per ordinare i link in ordine crescente//ILARIA: PER ME NON SERVE, BOH FUSTIGATEMI PURE SONO MASOCHISTA
// continuare con il transiente, in cui serve proprio questo meotodo per dividere il need del nodo nei vari path.
// per fare il path sorting andare a leggere le liste dal file e guardare la dimensione o usare l'algoritmo .

// 01/07/2022- la lettura da file non da errori, c'è da mettere a posto print for record con dei cicli (print for record serve
// per vedere se funziona il metodo di lettura), dopo bisogna continuare con il transiente.
// 05.07.2022: va in loop Ricontrolla tutto. partendo da quello fatto oggi(metodi con records)
// 17.07.2022: vedi riga 161 matrix.cpp

// 31.07.2022: alla riga 1143, in matrix.cpp, mettere find_isolated per il controllo sulla casa.
// 02.08.2022: togliere la parte che scrive su file in fill records, in quanto a noi serve map, ma non il file.
// se i path sono già ordinati su map allora trovare tutti i path di ciascuna casa e dividere la corrente in modo inversamente
// proporzionale alla lunghezza di ciascuno, poi dopo ciò, guardare che link contiene che path e sommare le correnti dei path
// sui link e in teoria il TRANSiente è finito.
// 05.08.2022 i rapporti di linkaggio erano sballati e si formavano troppi link, li abbiamo abbassati e sembra decente ora
// parametri, notare che quando ricolleghiamo le case le ricolleghiamo tutte, non solo una per ghetto.
// c'è da guardare dove riconnettiamo i ghetti di case (~1305 matrix.cpp) e effettivamente quante case rimangono scollegate con questi nuovi
//+ guarda il commento del giorno precedente.
// 08.08.2022 nella parte da ~1330 c'è da fare il vector e le altre cose commentate (funzione, creare il vector per i building
// non collegati ce ne devono essere due ) e fare il while . In find isolated c'è da mettere la condizione nel for. poi c'è da fare
// quello che dicono icommenti sopra, ovvero collegare la prima casa di ogni sottoghetto dato da ogni iterazione di
// non linked building
// 10.08.2022 non funziona come dovrebbe ci gli unici path che stampa sono quelli delle case collegate all'inizio, secondo me
// non collega come dovrebbe, fare dei cout per vedere il problema. DAI CHE ORMAI è QUASI FINITO!
// 11.08.2022 linked building non ha niente dentro alla fine, riguardare perchè fa cosi, trova tutte le case però,
// stampare linked building in vari posti per vedere come si comporta all'evolversi della funzione.
// 12.08.2022 l'ila è incazzata, risolto problema con linked building, adesso c'è da fare finalmente il transiente, guarda tutti
// i path, dividi la corrente ecc ecc ormai lo sai cosa c'è da fare nel transiente.
// 13.08.2022 guardare perchè collega direttamente alcune case a centrali, continuare il transiente, dividere la corrente e
// sommare i path sui link dentro il for per far si che siano di ciascuna casa.Forse ci sarebbe da fare un clear ogni ciclo
// del for.
// 14.08.2022 guardare perchè collega direttamente alcune case a centrali,
// in base alla lunghezza del primo path rispetto all' ultimo e al numero di path si calcola la porzione di need che scorre sul primo path,
// poi in base alla lunghezza relativa del secondo rispetto al primo si calcola la porzione del need che scorre sul secondo
// e così via fino a che arrivo ad un punto dove la porzione del need calcolato è minore del need rimasto disponiobile a essere
// distribuito ,
// 17.08.2022 guardare perchè collega direttamente alcune case a centrali, non mette in ordine crescente i path.
// Guarda altre distribuzioni di probabilità per la corrente da attribuire ad ogni path. (guarda foto).
// 20.08.2022 guardare perchè collega direttamente alcune case a centrali, non mette in ordine crescente i path.
// Guarda altre distribuzioni di probabilità per la corrente da attribuire ad ogni path. (guarda foto).
// continuare con il transiente.
// 21.08.2022 la resistenza dei link può essere trascurata quando andiamo a considerare cosa devono produrre le centrali,
// fare una funzione per settare il max load di ciascun tipo di link, guardare il perchè ci sono delle case collegate
// direttamente con delle centrali, ridistribuire la corrente del link che salta, controllare se saltano latri lik dopo aver
// ridistribuito la corrente e se saltano ridistribuire a loro volta la loro corrente su altri link finchè non si raggiunge
// uno stato stazionario. Guarda bene l'ultima stampa per quanto riguarda il tasso di collegamento (natura link.)
// 22.08.2022 guardare perchè connette direttamente case e centrali, conta sbagliato il numero di collegamenti tra le case
// 23.08.2022 riguardare output conta-collegamenti, perchè danno collegamenti smistamento smistamento anche se non gli diamo il
// comando di contarli; far funzionare la parte dove scolleghiamo la casa dalla centrale e la colleghiamo allo smistamento.
// 25.08.2022 non si è trovato il problema; porca troia: continuare. c'è anche da riguardare anche i tassi di collegamento e balle
// varie che con più di 400 nodi da problemi. Se entro fine serata non si troverà nulla fare il controllo accessorio e bona lì. Oggi male, la vedo nera.
// 26.08.2022 collegare la casa scollegata e poi finalmente continuare con il transiente alleluja
// 27.08.2022 problemi problemi problemi, stampa più volte lo stesso path, una casa veniva senza nessun collegamento però con il
// panino sembra funzionare anche se esplode il numero di path
// 28.08.2022 fare il controllo in cui si tolgono i link riguardare in generale i controlli e la generazione
//1.09.2022 Fare il confronto tra file corrente e quello del 20.08
