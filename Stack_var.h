/*
 *
 *  COMP 15 Proj2
 *
 *  Stack_var.h
 *  Complete Stack_var Struct Header and Declaration
 *  Purpose: Declares values in Stack_var Struct. Includes stack variable's
 *           name and predecessor (prev). These variable are used in the
 *           graph's stack - for the DFS path search.
 *  Written by  (UTLN): jlai03 - Jonathan Lai
 *           On       : Apr. 13, 2020
 *
 */
#include <iostream>
using namespace std;

#ifndef StackVar
#define StackVar

struct Stack_var{
    string name;
    string prev;
};

#endif
