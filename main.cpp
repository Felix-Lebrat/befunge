#include <iostream>
#include <vector>
#include "divers.h"
#include "Memoire.h"
#include "Pile.h"
#include <ctime>
//#define DEBUG

using namespace std;

int main(int argc,char **argv)
{
    vector<string> fichier;
    #ifdef DEBUG
    lecture("test.txt",fichier);
    #else
    if(argc>1)
    {
        lecture(argv[1],fichier);
    }
    else
    {
        cout<<"ERREUR fichier non specifie"<<endl;
        exit(-1);
    }
    #endif

    #ifdef DEBUG
    bool debug=true;
    #else
    bool debug=false;
    #endif
    if(argc>2&&string(argv[2])=="-d")
        debug=true;

    Memoire mem(maximum(fichier),fichier.size(),fichier);
    Pile p;
    bool text=false;
    Registres r;

    int tps=time(0);

    while(r.ci!='@')
    {
        r.ci=mem.read();
        if(debug)
        {
            cout<<endl<<p.afficher()<<endl;
            cout<<mem.afficher()<<endl;
        }
        if(text)//gestion du mode texte
        {
            if(r.ci=='"')//sortie du mode texte
            {
                text=false;
            }
            else
            {
                p.push(r.ci);
            }
        }
        else if(48<=r.ci&&r.ci<=57)//empiler un chiffre
        {
            p.push(r.ci-48);
        }
        else
        {
            r.a=p.pop();
            r.b=p.pop();
            switch(r.ci)
            {
            case '+'://addition
                p.push(r.a+r.b);
                break;
            case '-'://soustraction
                p.push(r.b-r.a);
                break;
            case '*'://multiplication
                p.push(r.a*r.b);
                break;
            case '/'://quotient de division entire
                if(r.a==0)
                {
                    cout<<"ERREUR division par zero"<<endl;
                    exit(-1);
                }
                p.push(r.b/r.a);
                break;
            case '%'://reste de division entiere
                if(r.a==0)
                {
                    cout<<"ERREUR division par zero"<<endl;
                    exit(-1);
                }
                p.push(r.b%r.a);
                break;
            case '!'://operateur non
                p.push(r.b);
                p.push(r.a==0);
                break;
            case '`'://comparaison
                p.push(r.b>r.a);
                break;
            case '_'://flux horizontale conditionnel
                p.push(r.b);
                (r.a==0)?mem.setDep(1,0):mem.setDep(-1,0);
                break;
            case '|'://flux verticale conditionnel
                p.push(r.b);
                (r.a==0)?mem.setDep(0,1):mem.setDep(0,-1);
                break;
            case ':'://duplication du haut de la pile
                p.push(r.b);
                p.push(r.a);
                p.push(r.a);
                break;
            case '\\'://permutation du haut de la pile
                p.push(r.a);
                p.push(r.b);
                break;
            case '$'://depilage d'une valeur
                p.push(r.b);
                break;
            case '.'://affichage numerique
                cout<<r.a;
                p.push(r.b);
                break;
            case ','://affichage ascii
                cout<<(char)r.a;
                p.push(r.b);
                break;
            case 'p'://modification du code
                mem.write(p.pop(),r.b,r.a);
                break;
            case 'g'://lecture du code
                p.push(mem.read(r.b,r.a));
                break;
            default:
                p.push(r.b);
                p.push(r.a);
                switch(r.ci)
                {
                case ' '://nop
                    break;
                case '>'://orientation du flux (droite)
                    mem.setDep(1,0);
                    break;
                case '<'://orientation du flux (gauche)
                    mem.setDep(-1,0);
                    break;
                case 'v'://orientation du flux (bas)
                    mem.setDep(0,1);
                    break;
                case '^'://orientation du flux (haut)
                    mem.setDep(0,-1);
                    break;
                case '?'://orientation du flux (rand)
                    mem.randomize_dep();
                    break;
                case '"'://activation du mode texte
                    text=true;
                    break;
                case '#'://trampoline
                    mem.deplacer();
                    break;
                case '&'://affichage numérique
                    cin>>r.nin;
                    p.push(r.nin);
                    break;
                case '~'://affichage ascii
                    cin>>r.ain;
                    p.push(r.ain);
                    break;
                case '@'://end
                    break;
                default:
                    cout<<endl<<"ERREUR instruction inconnue "<<(int)r.ci<<"("<<r.ci<<")"<<endl;
                    exit(-1);
                }
            }
        }
        mem.deplacer();
    }
    cout<<endl<<"**OK**"<<endl<<"execution time : "<<time(0)-tps<<endl;
    getchar();
}
