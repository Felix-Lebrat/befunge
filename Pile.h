#ifndef PILE_H
#define PILE_H

#include <string>

class Liste
{
private:
    Liste(Liste *liste);
    friend class Pile;
    int head;
    std::string afficher();
    Liste *tail;
};

class Pile
{
    public:
        Pile();
        void push(int val);
        int pop();
        std::string afficher();
        ~Pile();
    private:
        Liste *m_liste;
};

#endif // PILE_H
