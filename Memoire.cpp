#include "Memoire.h"

using namespace std;

Memoire::Memoire(int x,int y,vector<string> const& contenu):
    m_size_x(x),m_size_y(y),m_pos_x(0),m_pos_y(0),m_dep_x(1),m_dep_y(0),m_contenu(0)
{
    srand(time(NULL));
    m_contenu=new char*[m_size_x];
    char* tab(0);
    tab=new char[m_size_x*m_size_y];
    if(m_contenu==0||tab==0)
    {
        cout<<"ERREUR lors de l'affectation en ram de la mémoire virtuelle"<<endl;
        exit(-1);
    }

    for(int i=0;i<m_size_x;i++)
    {
        m_contenu[i]=&tab[m_size_y*i];
    }

    for(int y=0;y<m_size_y;y++)
    {
        for(int x=0;x<m_size_x;x++)
        {
            m_contenu[x][y]=((contenu[y].size()>x)?(contenu[y][x]):' ');
        }
    }

}

void Memoire::deplacer()
{
    m_pos_x=(m_pos_x+m_dep_x+m_size_x)%m_size_x;
    m_pos_y=(m_pos_y+m_dep_y+m_size_y)%m_size_y;
}

void Memoire::setDep(int dep_x,int dep_y)
{
    m_dep_x=dep_x;
    m_dep_y=dep_y;
}

void Memoire::randomize_dep()
{
    int dep[2]={0,0};
    int tab[2]={-1,1};
    dep[rand()%2]=tab[rand()%2];
    m_dep_x=tab[0];
    m_dep_y=tab[1];
}

char Memoire::read() const
{
    return read(m_pos_x,m_pos_y);
}

char Memoire::read(int pos_x,int pos_y) const
{
    return m_contenu[pos_x%m_size_x][pos_y%m_size_y];
}

void Memoire::write(char val)
{
    write(val,m_pos_x,m_pos_y);
}

void Memoire::write(char val,int pos_x,int pos_y)
{
    m_contenu[pos_x%m_size_x][pos_y%m_size_y]=val;
}

string Memoire::afficher()
{
    string aff;
    aff+="pos_x : "+to_string(m_pos_x)+" pos_y : "+to_string(m_pos_y)+" dep_x : "+to_string(m_dep_x)+" dep_y : "+to_string(m_dep_y)+"\n";
    for(int y=0;y<m_size_y+3;y++)
    {
        for(int x=0;x<m_size_x;x++)
        {
            if(y<m_size_y)
                aff+=m_contenu[x][y];
            else if(y==m_size_y+1&&x==m_pos_x)
                aff+="^";
            else if(y==m_size_y+2&&x==m_pos_x)
                aff+="|";
            else
                aff+=" ";
        }
        if(m_pos_y==y)
            aff+=" <-";
        aff+="\n";
    }

    return aff;
}

Memoire::~Memoire()
{
    delete[] m_contenu[0];
    delete[] m_contenu;
}
