#ifndef DIVERS_H_INCLUDED
#define DIVERS_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct Registres
{
    char ci;//current instruction
    int a,b; //stack top
    int nin; //numeric input
    char ain; //ascii input
    Registres();
};

void lecture(char *nom,std::vector<std::string> &tab);
int maximum(std::vector<std::string> tab);

#endif // DIVERS_H_INCLUDED
