#include "divers.h"

using namespace std;

Registres::Registres():ci(' ')
{}

void lecture(char *nom,vector<string> &tab)
{
    ifstream fichier(nom);
    string buff;

    if(fichier)
    {
        while(getline(fichier,buff))
        {
            tab.push_back(buff);
        }
    }
    else
    {
        cout<<"ERREUR lors de l'ouverture du fichier"<<endl;
        exit(-1);
    }
}

int maximum(vector<string> tab)
{
    int m=0;
    for(int i=0;i<tab.size();i++)
    {
        if(m<tab[i].size())
        {
            m=tab[i].size();
        }
    }

    return m;
}
