#include "Pile.h"

using namespace std;

Liste::Liste(Liste* liste): tail(liste)
{}

string Liste::afficher()
{
    return to_string(head)+"("+(char)head+"), "+((tail!=0)?tail->afficher():"");
}

Pile::Pile():m_liste(0)
{}

void Pile::push(int val)
{
    m_liste=new Liste(m_liste);
    m_liste->head=val;
}

int Pile::pop()
{
    if(m_liste==0)
        return 0;
    int h=m_liste->head;
    Liste *t=m_liste->tail;
    delete m_liste;
    m_liste=t;
    return h;
}

string Pile::afficher()
{
    return "top : "+((m_liste!=0)?m_liste->afficher():"")+": bottom";
}

Pile::~Pile()
{
    while(m_liste) pop();
}
