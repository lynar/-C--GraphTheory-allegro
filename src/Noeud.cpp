#include "Noeud.h"


/// Constructeur par défaut

Noeud::Noeud()
    : m_position_joueur(0),m_predecesseur(0),m_depl(' ')
{

}

/// Constructeur surchargé

Noeud::Noeud(unsigned short posJ,std::vector <unsigned short> tabBoites,int predecesseur,char depl)
    : m_position_joueur(posJ), m_pos_boites(tabBoites), m_predecesseur(predecesseur),m_depl(depl)
{

}

/// Destructeur

Noeud::~Noeud()
{
    ///Nothing to do here
}



/// Partie sur Getters

unsigned short Noeud::getPosJoueur() const
{
    return m_position_joueur;
}

unsigned short Noeud::getPosBoite(unsigned int i) const
{
    return m_pos_boites[i];
}

unsigned short Noeud::getSucceseur(unsigned int i) const
{
    return m_successeurs[i];
}

int Noeud::getPredecesseur() const
{
    return m_predecesseur;
}

char Noeud::getDepl() const
{
    return m_depl;
}

std::vector <unsigned int> Noeud::getTabSuccesseurs() const
{
    return m_successeurs;
}

std::vector <unsigned short> Noeud::getTabPosBoites() const
{
    return m_pos_boites;
}



/// Partie sur Setters

void Noeud::setPredecesseur(int NewPredecesseur)
{
    m_predecesseur = NewPredecesseur;
}

void Noeud::setTabPosBoites(std::vector <unsigned short> NewTabBoites)
{
    m_pos_boites=NewTabBoites;
}

void Noeud::setDepl(char NewDepl)
{
    m_depl = NewDepl;
}

void Noeud::setPosJoueur(unsigned short NewPos)
{
    m_position_joueur = NewPos;
}

void Noeud::setAddSuccesseur(unsigned int i)
{
    m_successeurs.push_back(i);
}

void Noeud::setTabSuccesseurs(std::vector <unsigned int> NewTabSuccesseurs)
{
    m_successeurs= NewTabSuccesseurs;
}



///Opérateurs

bool operator==(Noeud const& a,Noeud const& b)
{
    //Teste si a.m_heure == b.m_heure etc.
    if (a.getPosJoueur() == b.getPosJoueur() && a.getTabPosBoites() == b.getTabPosBoites() && a.getDepl() == b.getDepl())
        return true;
    else
        return false;
}

bool operator!=(Noeud const& a,Noeud const& b)
{
    if(a == b) //On utilise l'opérateur == qu'on a défini précédemment !
        return false; //S'ils sont égaux, alors ils ne sont pas différents
    else
        return true; //Et s'ils ne sont pas égaux, c'est qu'ils sont différents
}





