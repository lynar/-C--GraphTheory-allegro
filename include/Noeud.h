#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED

#include <vector>
#include <algorithm>


class Noeud
{
private :
    std::vector <unsigned int> m_successeurs;
    std::vector <unsigned short> m_pos_boites;
    int m_predecesseur;
    char m_depl;
    unsigned short m_position_joueur;

public :

    /// Déclaration des constructeurs et destructeurs
    Noeud();
    Noeud(unsigned short _position_joueur,std::vector <unsigned short> _pos_boites,int _predecesseur,char _depl);
    ~Noeud();

    /// Déclaration des Getters et Setters

    unsigned short getSucceseur(unsigned int i) const;
    unsigned short getPosBoite(unsigned int i) const;
    int getPredecesseur() const;
    char getDepl() const;
    unsigned short getPosJoueur() const;
    std::vector <unsigned int> getTabSuccesseurs() const;
    std::vector <unsigned short> getTabPosBoites() const;


    void setPosJoueur(unsigned short NewPos);
    void setTabPosBoites(std::vector <unsigned short> NewTabBoites);
    void setPredecesseur(int NewPredecesseur);
    void setTabSuccesseurs(std::vector <unsigned int> NewTabSuccesseurs );
    void setAddSuccesseur(unsigned int i);
    void setDepl(char NewDepl);





};

///Opérateurs

bool operator==(Noeud const& a,Noeud const& b);
bool operator!=(Noeud const& a,Noeud const& b);


#endif // NOEUD_H_INCLUDED
