/*
 *
 *  COMP 15 Proj2
 *
 *  Node.h
 *  Complete Node Struct Header and Declaration
 *  Purpose: Declares values in Node Struct. Includes node's name, location
 *           info (latitutde and longitude - in degree min notation), and
 *           another vector of Node pointers. - for adjacency list.
 *  Written by  (UTLN): jlai03 - Jonathan Lai
 *           On       : Apr. 13, 2020
 *
 */
#include <iostream>
#include <vector>
using namespace std;

#ifndef NODE
#define NODE

struct Node{
    string name;
    int lat_d, lat_m, lon_d, lon_m;
    vector <Node*> pointers;
};

#endif
