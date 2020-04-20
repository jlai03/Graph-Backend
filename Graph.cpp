/*
 *
 *  COMP 15 Proj2
 *
 *  Graph.cpp
 *  Complete Graph Class Implementation
 *  Purpose: Implements construction and access to graph. Able to read data
 *           files and construct graph. Can list nodes from graph, compute
 *           distance between nodes and list a certain number of paths
 *           between nodes.
 *  Written by  (UTLN): jlai03 - Jonathan Lai
 *           On       : Apr. 13, 2020
 *
 */
#include "Graph.h"


// ******** CONSTRUCTOR / DESTRUCTOR *************************************** //

// Function:    Constructor
// Parameters:  none
// Does:        constructs an empty Graph --> doesn't require anything
// Returns:     nothing
//
Graph :: Graph(){

}

// Function:    Destructor
// Parameters:  none
// Does:        Deallocates all left over memory on the heap (if any)
// Returns:     nothing
//
Graph :: ~Graph(){
    // fixed size
    int size = Nodes.size();
    // loop through vector
    for (int i = 0; i < size; i++){
        // deallocate memory
        delete Nodes.at(i);
    }
}

// ******** READ IN DATA FUNCTIONS **************************************** //

// Function:    Read Nodes Function
// Parameters:  string filename (.vdat file)
// Does:        Reads in Data from .vdat file and constructs nodes accordingly
// Returns:     nothing
//
void Graph :: read_nodes(string filename){
    // filename should .vdat file
    ifstream infile(filename.c_str());
    // Error Opening File Message
    if(infile.fail()){
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }
    // Read in nodes via linestream
    istringstream line_stream;
    string line_info;
    Node *temp;
    // While Loop - get line
    while(getline(infile, line_info)){
        // Allocate new memory
        temp = new Node;
        // Retrieve Info
        line_stream.str(line_info);
        line_stream >> temp->name;
        line_stream >> temp->lat_d >> temp->lat_m;
        line_stream >> temp->lon_d >> temp->lon_m;
        // Add Node to Graph's Vector
        Nodes.push_back(temp);
        // Reset Line Stream
        line_stream.clear();
    }
    return;
}

// Function:    Read Graph Function
// Parameters:  string filename (.adat file)
// Does:        Reads in Data from .adat file and connects nodes with directed
//              edges accordingly
// Returns:     nothing
//
void Graph :: read_graph(string filename){
    // filename should .adat file
    ifstream infile(filename.c_str());
    // Error Opening File Message
    if(infile.fail()){
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }
    // Read in nodes --> create edges
    istringstream line_stream;
    string line_info, start, end;
    Node *p1 = nullptr;
    Node *p2 = nullptr;
    // While Loop - get line
    while(getline(infile, line_info)){
        // Retrieve Info
        line_stream.str(line_info);
        line_stream >> start >> end;
        // Find Nodes - set ptr's (p1 = start, p2 = end)
        p1 = Nodes.at(find_index(start));
        p2 = Nodes.at(find_index(end));
        // Add Edge to p1's ptr vector
        p1->pointers.push_back(p2);
        // Reset Line Stream
        line_stream.clear();
    }
    return;
}

// Function:    Find Index Function
// Parameters:  string name - name of desired node
// Does:        This is a helper function - which helps find the index
//              of a given node in the vector
// Returns:     int - index of node
//
int Graph :: find_index(string name){
    // fixed size
    int size = Nodes.size();
    // find with for loop
    for (int i = 0; i < size; i++){
        // Name matches current index
        if (Nodes.at(i)->name == name){
            return i;
        }
    }
    // If it doesn't exist in the vector
    return -1;
}

// ******** LIST FUNCTIONS ************************************************* //

// Function:    List Function
// Parameters:  none
// Does:        Lists the City Names - Node names
// Returns:     nothing
//
void Graph :: list(){
    // fixed size
    int size = Nodes.size();
    // print for loop
    for (int i = 0; i < size; i++){
        cout << Nodes.at(i)->name << endl;
    }
    return;
}

// ******** DISTANCE FUNCTIONS ********************************************* //

// Function:    Distance Function
// Parameters:  string start - names of nodes
//              string end
// Does:        Computes the "Distance" between two nodes' locations
// Returns:     double - distance between the two nodes
//

double Graph :: distance(string start, string end){
    // If either of the nodes don't exist
    if(find_index(start) == -1 || find_index(end) == -1){
        return -1.00;
    }
    // Find pointers to nodes
    Node *p1 = Nodes.at(find_index(start));
    Node *p2 = Nodes.at(find_index(end));
    // Change nodes into locations
    Location l_1 = convert(p1);
    Location l_2 = convert(p2);
    // Compute distance
    double distance = l_1.distance_to(&l_2);
    // Return Distance
    return distance;
}

// Function:    Convert Function
// Parameters:  Node *p - pointer to a node
// Does:        Converts a pointer to a node into a location variable
// Returns:     Location - corresponds to node passed in
//
Location Graph :: convert(Node *p){
    // Edge case
    if(p == nullptr){
        cerr << "Can't convert an empty node to location " << endl;
        exit(1);
    }
    // Compute Latitude & Longitude
    double lat = abs(p->lat_d) + ((p->lat_m)/60.0);
    double lon = abs(p->lon_d) + ((p->lon_m)/60.0);
    // Correct Directions
    if (p->lat_d < 0){
        lat *= -1;
    }
    if (p->lon_d < 0){
        lon *= -1;
    }
    // Assign and Return Location Class
    Location location(lat, lon);
    return location;
}

// ******** PATH FUNCTIONS ************************************************* //

// Function:    Print Path Function
// Parameters:  string start - name of start and end nodes
//              string end
//              int amount - maximum amount of paths desired
// Does:        Prints out Paths from start node to end node. Uses Depth First
//              Search with a stack
// Returns:     int - indicates whether error was thrown (1)
//
int  Graph :: print_path(string start, string end, int amount){
    // Error: if vertices don't exit
    if( find_index(start) == -1 || find_index(end) == -1){
        cout << "ERROR: unknown city" << endl;
        return 1;
    }
    // Set Up Stack Simulation
    int count = 0;
    int loop_count = 0;
    // Push First Vertex
    Stack_var first;
    first.name = Nodes.at(find_index(start))->name;
    first.prev = "-1";
    dfs_nodes.push(first);
    // Print Loop
    print_loop(end, amount, loop_count, count);
    // Error: if no possible path
    if (count == 0){
        cout << "ERROR: no-path-possible" << endl;
        return 1;
    }
    // Clear Stack
    while(dfs_nodes.empty() == false){
        dfs_nodes.pop();
    }
    return 0;
}

// Function:    Print Loop Function
// Parameters:  string end - name of end node
//              int amount - amount of paths desired
//              int loop_count - keeps count of loop's iterations
//              int &count - pass by reference to count variable
// Does:        Initiates "while" loop to simulate DFS with Stack.
//              Prints out desired paths using pathway function - relies
//              on predecessor vector to track paths
// Returns:     nothing
//
void Graph :: print_loop(string end, int amount, int loop_count,
                            int &count){
    // Use Predecessor vector
    vector <string> predecessor;
    // While Loop
    while(count < amount && dfs_nodes.empty() == false){
        // Update Predecessor Vector (if necessary) - tracks path
        while (loop_count > 0 && dfs_nodes.top().prev != predecessor.back()){
            predecessor.pop_back();
        }
        // Base Case 1 - if explored (remove from stack)
        if(explored(&predecessor) == true){
            dfs_nodes.pop();
            continue;
        }
        // If Stack Empty - End Loop
        if (dfs_nodes.empty() == true){ break; }
        // Retreive vertex on top of stack
        string temp_top = dfs_nodes.top().name;
        // If end node not reached, EXPAND
        if(temp_top != end){
            expand_top(&predecessor);
        }else{
            predecessor.push_back(end);
        }
        // If Target was Reached - report pathway
        if (predecessor.back() == end){
            // Update Count and Report Path
            count ++;
            pathway(&predecessor, count);
            cout << endl;
            // Remove Node - if stack & predecessor vector not empty
            if(dfs_nodes.empty() == false){dfs_nodes.pop();}
        }
        // update loop count
        loop_count ++;
    }
}

// Function:    Explored Function
// Parameters:  string <vector> *predecessor - pointer to predecessor vector
// Does:        Checks if vertex on top of stack was already explored/expanded/
//              If it returns true, then it will pop off the vertex from stack
//              later
// Returns:     bool - indicates whether vertex was already explored
//
bool Graph :: explored(vector<string> *predecessor){
    // Retreive size
    int size = predecessor->size();
    for (int i = 0; i < size; i++){
        // If top was already explored
        if (predecessor->at(i) == dfs_nodes.top().name){
            return true;
        }
    }
    return false;
}


// Function:    Expand Top Function
// Parameters:  string *ptr - pointer to predecessor vector
// Does:        Pops of vertex on top of stack, Updates Predecessor Vector,
//              and pushes on its neighbors
// Returns:     nothing
//
void Graph :: expand_top(vector<string> *ptr){
    // Store pred vertex info
    string temp = dfs_nodes.top().name;
    // Pop From Stack
    dfs_nodes.pop();
    // Push Back to predecessor vector
    ptr->push_back(temp);
    // Push Neighbors onto stack
    int size = Nodes.at(find_index(temp))->pointers.size();
    for(int i = size - 1; i >= 0; i--){
        // Set info
        Stack_var temp_var;
        temp_var.name = Nodes.at(find_index(temp))->pointers.at(i)->name;
        temp_var.prev = temp;
        // Push
        dfs_nodes.push(temp_var);
    }
    return;
}

// Function:    Pathway Function
// Parameters:  string * ptr - pointer to predecessor vector
//              int count - number of pathways reported
// Does:        Prints out pathway in provided format - does by printing
//              out vertices in predecessor vector and the distances
//              between them
// Returns:     nothing
//
void Graph :: pathway(vector<string> *ptr, int count){
    // Path number
    cout << "PATH " << count << " ::";
    int size = ptr->size();
    // Print Format
    for (int i = 0; i < size; i++){
        // Distance
        if(i == 0){
            cout << " " << 0 << " ";
        }else{
            int dist = distance(ptr->at(i-1), ptr->at(i));
            cout << " " << dist << " ";
        }
        // Find vertex
        int index = find_index(ptr->at(i));
        Node *temp_node = Nodes.at(index);
        // Print Name
        cout << temp_node->name << " ";
        // Print Location
        convert(temp_node).print();
    }
    return;
}

// ******** PATH TESTING *************************************************** //

// Function:    Fake Push Function
// Parameters:  string temp
// Does:        Pushes stack variable onto dfs_nodes stack - for testing
//              purposes
// Returns:     nothing
//
void Graph :: fake_push(string temp){
    // Make Stack Var
    Stack_var var;
    var.name = temp;
    dfs_nodes.push(var);
    return;
}

// Function:    Fake Pop Function
// Parameters:  none
// Does:        Pops off vertex on top of stack - for testing
// Returns:     nothing
//
void Graph :: fake_pop(){
    dfs_nodes.pop();
    return;
}

// Function:    Fake Top Function
// Parameters:  none
// Does:        Returns name of vertex on top of stack - for testing
// Returns:     nothing
//
string Graph :: fake_top(){
    Stack_var var =  dfs_nodes.top();
    return var.name;
}

// ******** PRINT FUNCTIONS ************************************************ //

// Function:    Print Nodes Function
// Parameters:  none
// Does:        Prints out Nodes Vector - Mainly for Testing Purposes
// Returns:     nothing
//
void Graph :: print_nodes(){
    // fixed sizes
    int size = Nodes.size();
    int temp;
    // print for loop
    for (int i = 0; i < size; i++){
        cout << endl;
        // name
        cout << "name: " << Nodes.at(i)->name << endl;
        // location
        cout << "location: ";
        cout << Nodes.at(i)->lat_d << " " << Nodes.at(i)->lat_m << " ";
        cout << Nodes.at(i)->lon_d << " " << Nodes.at(i)->lon_m << endl;
        // edges
        cout << "directed neighbors: ";
        temp = Nodes.at(i)->pointers.size();
        // edges - loop
        for (int j = 0; j < temp; j++){
            cout << Nodes.at(i)->pointers.at(j)->name;
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

// ******** ACCESS FUNCTIONS *********************************************** //

// Function:    Get Function
// Parameters:  string name - name of desired node
// Does:        Finds desired node in graph's Nodes Vector and returns a
//              pointer to it
// Returns:     Node * - pointer to desired node
//
Node *Graph :: get(string name){
    // Find index
    int index = find_index(name);
    // Return pointer to node in vector
    return Nodes.at(index);
}



//
