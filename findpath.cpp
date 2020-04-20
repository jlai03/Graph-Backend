/*
 *
 *  COMP 15 Proj2
 *
 *  findpath.cpp
 *  Complete findpath.cpp Implementation
 *  Purpose: Implements Main Function Code - Checks for proper argument count,
 *           then initiates transmission loop. Loop reads in query and calls
 *           functions in Graph.cpp accordingly. Ends each query with "-EOT-",
 *           if no errors occur.
 *  Written by  (UTLN): jlai03 - Jonathan Lai
 *           On       : Apr. 13, 2020
 *
 */
#include "Graph.h"
#include <iomanip>

// *********** FUNCTION DECLARATIONS *************************************** //
int transmission(char *argv[]);




// *********** MAIN FUNCTION  ********************************************** //
int main (int argc, char *argv[])
{
    // Check for proper argument count
    if (argc != 3){
        cerr << "Usage: findpath vertex_data edge_data" << endl;
        exit(1);
    }
    // Transmission Loop - Returns 0 at end of program
    return transmission(argv);
}

// *********** TRANSMISSION LOOP  ****************************************** //

// Function:    Transmission Loop
// Parameters:  Graph graph
// Does:        Simulates Transmission Loop in Reference Implementation
//              Takes query from user and responds accordingly - repeats
//              until query == quit or it reaches the end of a cin file
// Returns:     int - return 0 to indicate end of program
//
int transmission(char *argv[]){
    // Create Graph and Read in Data
    Graph graph;
    graph.read_nodes(argv[1]);
    graph.read_graph(argv[2]);
    // Set up
    string query;
    string city_1, city_2;
    // Begin Transmission Loop - read in query
    while(cin >> query){
        // List Function
        if (query == "list"){
            graph.list();
        }
        // Quit Function
        if (query == "quit"){
            return 0;
        }
        // Distance Function
        if (query == "dist"){
            // Read in cities
            cin >> city_1 >> city_2;
            // Format and Print Distance
            cout << setprecision(2) << fixed;
            cout << graph.distance(city_1, city_2) << endl;
        }
        // Path Function
        if (query == "path"){
            int amount;
            cin >> city_1 >> city_2 >> amount;
            int err = graph.print_path(city_1, city_2, amount);
            // If error thrown - no EOT
            if (err == 1){
                continue;
            }
        }
        // End of Transmission
        cout << "-EOT-" << endl;
    }
    // End Program
    return 0;
}
