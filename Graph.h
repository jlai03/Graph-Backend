/*
 *
 *  COMP 15 Proj2
 *
 *  Graph.h
 *  Complete Graph Class Header and Declaration
 *  Purpose: Declares public and private members of Graph. Private: includes
 *           vector of Node pointers - to resemble graph structure - and
 *           includes Stack of Stack_var to later simulate DFS for path
 *           function. Public functions allow operation on these private
 *           members to output certain information.
 *  Written by  (UTLN): jlai03 - Jonathan Lai
 *           On       : Apr. 13, 2020
 *
 */
 #include <iostream>
 #include <string>
 #include <vector>
 #include <stack>
 #include <fstream>
 #include <sstream>
 #include <iomanip>
 #include <math.h>
 #include "Node.h"
 #include "Location.h"
 #include "Stack_var.h"
 using namespace std;

 #ifndef GRAPH
 #define GRAPH

 class Graph{
     private:
         // Vector of Nodes
         vector <Node*> Nodes;
         // Stack for Depth First Search (Path Function)
         stack <Stack_var> dfs_nodes;
    public:
        // Constructor & Destructor
        Graph();
        ~Graph();

        // Reading in data from file
        void read_nodes(string filename);
        void read_graph(string filename);
        int find_index(string name);

        // List Functions
        void list();

        // Distance Function
        double distance(string start, string end);
        Location convert(Node *p);

        // Path Function
        int print_path(string start, string end, int amount);
        void print_loop(string end, int amount, int loop_count,
                                    int &count);
        bool explored(vector<string> *predecessor);
        void expand_top(vector <string> *ptr);
        void pathway(vector<string> *ptr, int count);

        // Path - Testing
        void fake_push(string temp);
        void fake_pop();
        string fake_top();

        // Print Functions - Testing
        void print_nodes();

        // Access Functions (Getters) - Testing
        Node *get(string name);
 };

#endif
