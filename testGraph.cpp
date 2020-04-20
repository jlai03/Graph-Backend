/*
 *
 *  COMP 15 Proj2
 *
 *  testGraph.cpp
 *  Complete Unit Testing Implementation - for Graph Class -
 *  Purpose: Provides Unit Testing for Graph's public functions. Tests
 *           ability to read in data and construct graph, list vertices,
 *           compute distance between nodes, and determine paths between
 *           nodes (Broken into sub functions, main function, and edge cases)
 *  Written by  (UTLN): jlai03 - Jonathan Lai
 *           On       : Apr. 13, 2020
 *
 */
#include "Graph.h"
using namespace std;

// EXPECT TRUE TESTING MECHANISM
#define EXPECT_TRUE(condition)                      \
        cout << ((condition) ? "Passed" : "Failed") \
                  << " test '" #condition "'\n"

// TESTING FUNCTIONS
void read_functions();
void list_function();
void distance_function();
void path_sub_function();
void path_final_function();
void path_edge_case();

// MAIN TESTING FUNCTION
int main(){
    cout << endl;
    cout << "-- READ IN FUNCTIONS -- " << endl;
    read_functions();
    cout << endl;
    cout << "-- LIST FUNCTION -- " << endl;
    list_function();
    cout << endl;
    cout << "-- LOCATION FUNCTION -- " << endl;
    distance_function();
    cout << endl;
    cout << "-- PATH SUB FUNCTION --" << endl;
    path_sub_function();
    cout << endl;
    cout << "-- PATH FINAL FUNCTION --" << endl;
    path_final_function();
    cout << endl;
    cout << "-- PATH EDGE CASE --" << endl;
    path_edge_case();
    cout << endl;
    return 0;
}

// ****** TEST READ IN FUNCTIONS ******************************************* //

void read_functions(){
    // Set up
    Graph g;
    // Read Nodes
    g.read_nodes("data0.vdat");
    // Read Graph
    g.read_graph("data0.adat");
    // Find Index
    EXPECT_TRUE(g.find_index("v1") == 0);
    EXPECT_TRUE(g.find_index("v3") == 2);
    EXPECT_TRUE(g.find_index("v7") == 6);
    // Print
    g.print_nodes(); // PRINTED AS EXPECTED
    // EDGE CASES
    // g.read_nodes("bloop.vdat"); // CRASHED AS EXPECTED
    // g.read_graph("bloop.adat"); // CRASHED AS EXPECTED
    EXPECT_TRUE(g.find_index("boop") == -1);
    return;
}

// ****** TEST LIST FUNCTION *********************************************** //

void list_function(){
    // Set up
    Graph g;
    g.read_nodes("data0.vdat");
    // List Function
    g.list();
    return;
}

// ****** TEST LIST FUNCTION *********************************************** //

void distance_function(){
    // Set up
    Graph g;
    g.read_nodes("data0.vdat");
    g.read_graph("data0.adat");
    // Test Distances - All printed as Expected
    cout << "print out 1397.40: ";
    cout << setprecision(2) << fixed << g.distance("v1", "v3")  << endl;
    cout << "print out 3403.91: ";
    cout << setprecision(2) << fixed << g.distance("v1", "v6")  << endl;
    cout << "print out 6272.37: ";
    cout << setprecision(2) << fixed << g.distance("v3", "v5")  << endl;
    cout << "print out 790.47: ";
    cout << setprecision(2) << fixed << g.distance("v4", "v1")  << endl;
    cout << "print out 3277.54: ";
    cout << setprecision(2) << fixed << g.distance("v2", "v1")  << endl;
    cout << "print out 6277.10: ";
    cout << setprecision(2) << fixed << g.distance("v7", "v1")  << endl;
    cout << "print out 3297.53: ";
    cout << setprecision(2) << fixed << g.distance("v7", "v5")  << endl;
    // EDGE CASE
    // g.convert(nullptr); // CRASHED AS EXPECTED
    EXPECT_TRUE(g.distance("v9", "v8") == -1.00);
    EXPECT_TRUE(g.distance("bloop", "womp") == -1.00);
    return;
}

// ****** TEST PATH SUB FUNCTIONS ****************************************** //

void path_sub_function(){
    // set up
    Graph g;
    g.read_nodes("data0.vdat");
    g.read_graph("data0.adat");
    vector <string> vec;
    // Expand Top Function
    g.fake_push("v1");
    g.expand_top(&vec);
    EXPECT_TRUE(vec.at(0) == "v1");
    EXPECT_TRUE(g.fake_top() == "v2");
    g.expand_top(&vec);
    EXPECT_TRUE(vec.at(1) == "v2");
    g.fake_pop();
    EXPECT_TRUE(g.fake_top() == "v4");
    g.fake_pop();
    g.fake_pop();
    // g.fake_pop(); // Crashed as Expected
    // Pathway Function
    vec.clear();
    vec.push_back("v1");
    vec.push_back("v4");
    vec.push_back("v5");
    vec.push_back("v7");
    stack <string> stack_temp;
    g.pathway(&vec, 1); // Printed as Expected
    cout << endl;
    return;
}

// ****** TEST PATH FINAL FUNCTIONS **************************************** //

void path_final_function(){
    // set up
    Graph g;
    g.read_nodes("data0.vdat");
    g.read_graph("data0.adat");
    // print 1 path
    g.print_path("v1", "v3", 1); // Printed as Expected
    cout << endl;
    // print 2 paths
    g.print_path("v1", "v3", 2); // Printed as Expected
    cout << endl;
    // dealing with empty stack
    g.print_path("v1", "v3", 7); // Printed as Expected
    cout << endl;
    // Larger Cases
    g.print_path("v1", "v7", 10); // Printed as Expected
    cout << endl;
    g.print_path("v3", "v4", 10); // Printed as Expected
    cout << endl;
    // Edge Case
    g.print_path("v1", "v1", 5); // Printed as Expected
    cout << endl;
    g.print_path("v3", "BloP", 4); // Printed as Expected
    cout << endl;
    return;
}

// ****** TEST PATH FINAL FUNCTIONS **************************************** //

void path_edge_case(){
    // set up
    Graph g;
    g.read_nodes("data0.vdat");
    g.read_graph("ec0.adat");
    // No Possible Path - Edge Cases
    g.print_path("v1", "v5", 1);
    cout << endl;
    g.print_path("v2", "v7", 10);
    cout << endl;
    g.print_path("v4", "v1", 10);
    cout << endl;
    g.print_path("bloop", "doop", 10);
    cout << endl;
    // Possible Path
    g.print_path("v4", "v7", 10);
    cout << endl;
    g.print_path("v7", "v7", 10);
    cout << endl;
    g.print_path("v2","v2", 10);
    cout << endl;
    g.print_path("v2","v1", 10);
    cout << endl;
    return;
}



//
