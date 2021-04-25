#ifndef MEMOIRE_H
#define MEMOIRE_H

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Memoire
{
    public:
        Memoire(int x,int y,std::vector<std::string> const& contenu);
        void deplacer();
        void setDep(int dep_x,int dep_y);
        void randomize_dep();
        char read() const;
        char read(int pos_x,int pos_y) const;
        void write(char val);
        void write(char val,int pos_x,int pos_y);
        std::string afficher();
        ~Memoire();
    private:
        int const m_size_x;
        int const m_size_y;
        int m_pos_x;
        int m_pos_y;
        int m_dep_x;
        int m_dep_y;
        char **m_contenu;
};

#endif // MEMOIRE_H
