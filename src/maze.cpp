/************************************************************
Sokoban project - Maze file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/

#include "maze.h"
#include "graphic.h"
#include "utils/console.h"
#include "utils/coord.h"
#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <chrono>
#include <algorithm>
#include <stdlib.h>
#include <iostream>

#include "Noeud.h"

Maze::Maze(const std::string& path)
    : m_lig(0), m_col(0), m_pos_player(0), m_dir_player(TOP), m_level_path(path)
{
}

Maze::~Maze()
{
}

bool Maze::init()
{
    bool res = this->_load(this->m_level_path);
    if (!res)
    {
        std::cerr << "Cannot load maze... Check file : " << this->m_level_path << std::endl;
        return false;
    }

    return res;
}

// Check if all boxes are on a goal
bool Maze::_isCompleted() const
{
    for (unsigned int i=0; i<this->m_pos_boxes.size(); ++i)
    {
        if (!this->isSquareBoxPlaced(this->m_pos_boxes[i]))
            return false;
    }
    return true;
}

// Check if we can push a box in a direction
// INPUT: position of the box to check, direction,
// OUTPUT : the position of the box after pushing
//      TRUE if all goes right otherwise FALSE
bool Maze::_canPushBox(unsigned short posBox, char dir, unsigned short& newPosBox) const
{
    // Check if this position is a box !
    if (!this->isSquareBox(posBox))
        return false;
    // Compute new position according to push direction
    newPosBox = Coord::getDirPos(posBox, dir);


    // Can we push the box ?
    return this->isBoxPoussable(newPosBox);
}

// Load a maze from a file (DO NOT TOUCH)
bool Maze::_load(const std::string& path)
{
    std::vector<unsigned short> tmpPosBoxes;
    std::ifstream ifs(path.c_str());
    if (ifs)
    {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(ifs, line))
        {
            lines.push_back(line);
            this->m_lig++;
            this->m_col = (this->m_col < line.size() ? line.size() : this->m_col);
        }
        ifs.close();

        if (this->m_col > NB_MAX_WIDTH || this->m_lig > NB_MAX_HEIGHT)
        {
            std::cerr << "Maze::load => Bad formatting in level data..." << std::endl;
            return false;
        }

        Coord::m_nb_col = this->m_col;
        for (unsigned int i=0; i<lines.size(); i++)
        {
            //LDebug << "Maze::load => Reading : " << lines[i];
            for (unsigned int j=0; j<this->m_col; j++)
            {
                if (j < lines[i].size())
                {
                    bool both = false;
                    unsigned short pos = Coord::coord1D(i, j);
                    unsigned char s = (unsigned char)(lines[i][j] - '0');

                    // Need to add a goal and a box ;)
                    if (s == SPRITE_BOX_PLACED)
                    {
                        both = true;
                    }

                    if (s == SPRITE_GOAL || both)
                    {
                        this->m_pos_goals.push_back(pos);
                    }
                    if (s == SPRITE_BOX || both)
                    {
                        tmpPosBoxes.push_back(pos);
                    }

                    // Assign player position
                    if (s == SPRITE_MARIO)
                    {
                        this->m_pos_player = pos;
                        //LDebug << "\tAdding player pos (" << pos << ")";
                        s = SPRITE_GROUND;
                    }

                    // Add this value in the field
                    this->m_field.push_back(s);
                }
                else
                {
                    // Here - Out of bound
                    this->m_field.push_back(SPRITE_GROUND);
                }
            }
        }

        // Copy box position
        this->m_pos_boxes.resize(tmpPosBoxes.size());
        for (unsigned int i=0; i<tmpPosBoxes.size(); ++i)
        {
            this->m_pos_boxes[i] = tmpPosBoxes[i];
        }

        return (this->m_pos_boxes.size() == this->m_pos_goals.size());
    }
    else
    {
        std::cerr << "Maze::load => File does not exist..." << std::endl;
    }

    return false;
}

bool Maze::updatePlayer(char dir)
{
    ///unsigned short newPosBox(0);
    if (dir < 0 || dir > MAX_DIR)
    {
        std::cerr << "Maze::updatePlayer => Direction not correct... " << +dir << std::endl;
        return false;
    }

    // Implement player moving and pushing here
    if(isSquareWalkable(Coord::getDirPos(m_pos_player, dir))) //si le personnage peut se deplacer sur ce bloc
    {
        setPlayerPos(Coord::getDirPos(m_pos_player, dir)); //deplacer le personnage sur cette case
        m_dir_player=dir;//la direction du perso est enregistrée
    }
    else if(isSquareBox(Coord::getDirPos(m_pos_player, dir))) //si le bloc est une boite
    {
        for(unsigned short i=0; i<m_pos_boxes.size(); i++)

            //si les coordonnees correspondent a celle d'une boite  et et que la caisse peut etre poussee

            if(Coord::getDirPos(m_pos_player, dir)== m_pos_boxes[i]  && isSquareWalkable(Coord::getDirPos(m_pos_boxes[i], dir)))
            {
                setPlayerPos(Coord::getDirPos(m_pos_player, dir)); // on la pousse

                m_dir_player=dir;// on enregistre encore la direction

                //si la boite est sur le goal
                if(isSquareBoxPlaced( Coord::getOppositeDirPos(Coord::getDirPos(m_pos_player, dir),  dir )))

                    setSquare(m_pos_boxes[i],SPRITE_GOAL );//on modifie m_field,,on utilise l'image de la boite rouge
                else
                    setSquare(m_pos_boxes[i], SPRITE_GROUND);//sinon on remplace la boite par une case sol, ceci permet de la deplacer !


                if(isSquareGoal(Coord::getDirPos(m_pos_boxes[i], dir)))//si la case est un goal
                {
                    m_pos_boxes[i]=Coord::getDirPos(m_pos_boxes[i], dir);
                    setSquare(m_pos_boxes[i], SPRITE_BOX_PLACED);//mettre les caisses en rouge
                    if(_isCompleted()==true)
                        return true; ///gagne la partie
                }
                else
                {
                    m_pos_boxes[i]=Coord::getDirPos(m_pos_boxes[i], dir);//modification de la position des boites
                    setSquare(m_pos_boxes[i], SPRITE_BOX);// on definit la case comme etant une boite
                }
            }
    }

    return false;
}



// Display maze on screen with Allegro
void Maze::draw(const Graphic& g) const
{
    for(unsigned int i=0; i<this->getSize(); i++)
    {
        unsigned int l = 0, c = 0;
        Coord::coord2D(i, l, c);

        if (i == this->m_pos_player)
        {
            g.drawT(g.getSpritePlayer(this->m_dir_player), c, l);
        }
        else
        {
            g.drawT(g.getSprite(this->m_field[i]), c, l);
        }
    }
}

// DO NOT TOUCH !
// Overload function for displaying debug information
// about Maze class
std::ostream& operator << (std::ostream& O, const Maze& m)
{
    unsigned int l, c;
    int i = 0;
    Coord::coord2D(m.m_pos_player, l, c);
    O << "Player position " << m.m_pos_player << " (" << l << "," << c << ")" << std::endl;
    O << "Field Size " << +m.m_lig << " x " << +m.m_col << " = " << m.getSize() << std::endl;
    O << "Field Vector capacity : " << m.m_field.capacity() << std::endl;
    O << "Field array : " << std::endl << std::endl;
    for(unsigned int l=0; l<m.getSize(); l++)
    {
        if (l == m.m_pos_player) Console::getInstance()->setColor(_COLOR_YELLOW);
        else if (m.isSquareWall(l)) Console::getInstance()->setColor(_COLOR_PURPLE);
        else if (m.isSquareBoxPlaced(l) || m.isSquareGoal(l)) Console::getInstance()->setColor(_COLOR_GREEN);
        else if (m.isSquareBox(l)) Console::getInstance()->setColor(_COLOR_BLUE);
        else if (m.m_field[l] == SPRITE_DEADSQUARE) Console::getInstance()->setColor(_COLOR_RED);
        else Console::getInstance()->setColor(_COLOR_WHITE);

        O << std::setw(2) << +m.m_field[l] << " "; // + => print as "int"

        if ((l+1) % m.m_col == 0)
        {
            O << std::endl;
        }
    }
    Console::getInstance()->setColor(_COLOR_DEFAULT);

    O << std::endl;
    O << "Box position : " << std::endl;
    for (unsigned int i=0; i<m.m_pos_boxes.size(); i++)
    {
        Coord::coord2D(m.m_pos_boxes[i], l, c);
        O << "\t" << "Box #" << i << " => " << std::setw(3) << m.m_pos_boxes[i] << std::setw(2) << " (" << l << "," << c << ")" << std::endl;
    }

    O << std::endl;
    O << "Goal position : " << std::endl;
    for (const auto& goal : m.m_pos_goals)
    {
        unsigned int l, c;
        Coord::coord2D(goal, l, c);
        if (m.isSquareBoxPlaced(goal)) Console::getInstance()->setColor(_COLOR_GREEN);
        O << "\t" << "Goal #" << i << " => " << std::setw(3) << goal << std::setw(2) << " (" << l << "," << c << ")" << std::endl;
        if (m.isSquareBoxPlaced(goal)) Console::getInstance()->setColor(_COLOR_DEFAULT);
        i++;
    }

    return O;
}



void Maze::AfficherNoeud(Noeud noeud, Graphic& g)
{
        this->ActualisationDuTerrain(noeud);
        this->setPlayerPos(noeud.getPosJoueur());
        this->m_dir_player=noeud.getDepl();
        g.clear();
        this->draw(g);
        g.display(Coord::m_nb_col);

}

//AFFICHAGE SOLUTION//
void Maze::AFFICHERSOLUTIONMARIO(std::vector <Noeud> sol,Graphic g)
{

//On redonne les position initiales au joueur et aux boites
    m_pos_player = sol.back().getPosJoueur();
    m_pos_boxes  = sol.back().getTabPosBoites();
    Noeud update(m_pos_player,m_pos_boxes,0,TOP);



    //Affichage de la solution
    for ( int i=sol.size()-2; i>=0; i--)
    {

        // std::cout << sol[i].getPosJoueur() << " " << std::endl;
        //  std::cout << sol[i].getDepl() << " " << std::endl;
 this->setPlayerPos(sol[i].getPosJoueur());
 this->ActualisationDuTerrain(sol[i]);
 this->m_dir_player=sol[i].getDepl();
        g.clear();
        this->draw(g);
        g.display(Coord::m_nb_col);

    }

    readkey();

}

//DETECT DEADLOCK
void Maze::detecterLesDeadLock()
{
    for (unsigned int i=0; i<m_field.size(); i++)
    {
        if (m_field[i]==SPRITE_GROUND)
        {
            if (m_field[i-1]==SPRITE_WALL)
            {
                m_field[i] = SPRITE_DEADSQUARE;
            }
            else if (m_field[i+1]==SPRITE_WALL)
            {
                m_field[i] = SPRITE_DEADSQUARE;
            }
            else if (m_field[i+Coord::m_nb_col]== SPRITE_WALL)
            {
                m_field[i] = SPRITE_DEADSQUARE;
            }
            else if (m_field[i-Coord::m_nb_col]==SPRITE_WALL)
            {
                m_field[i] = SPRITE_DEADSQUARE;
            }
        }
    }
    ///rajouter le cas où la case potentiellement dead est en fait dans la meme colonne ou ligne qu'un goal sans mur intermédiare entre la box
    /// et le goal et ayant une case derrière la box pour initier le mouvement vers le goal
    unsigned int cpt(0);
    while (cpt<m_field.size())
    {
       for (unsigned int i=0; i<m_field.size(); i++)
        {
            ///Si  la case est un deadlock MAIS peut être poussée sur une case qui n'est pas un deadlock, alors ce n'est pas un dead lock
            if(m_field[i] == SPRITE_DEADSQUARE)
            {
                if( (m_field[i+1]==SPRITE_GROUND || m_field[i+1]==SPRITE_GOAL
                     || m_field[i+1]==SPRITE_BOX || m_field[i+1]==SPRITE_BOX_PLACED )
                   && m_field[i-1]!=SPRITE_WALL)
                {
                    m_field[i] = SPRITE_GROUND;
                }
                else if ( (m_field[i-1]==SPRITE_GROUND || m_field[i-1] == SPRITE_GOAL
                            || m_field[i-1]==SPRITE_BOX_PLACED) && m_field[i+1]!=SPRITE_WALL)
                {
                    m_field[i] = SPRITE_GROUND;
                }
               else if( (m_field[i+Coord::m_nb_col]==SPRITE_GROUND || m_field[i+Coord::m_nb_col] == SPRITE_GOAL
                         || m_field[i+Coord::m_nb_col] == SPRITE_BOX_PLACED || m_field[i+Coord::m_nb_col] == SPRITE_BOX) && m_field[i-Coord::m_nb_col]!=SPRITE_WALL)
                {
                    m_field[i] = SPRITE_GROUND;
                }
                else if((m_field[i-Coord::m_nb_col]==SPRITE_GROUND || m_field[i-Coord::m_nb_col] == SPRITE_GOAL
                         || m_field[i-Coord::m_nb_col] == SPRITE_BOX_PLACED || m_field[i-Coord::m_nb_col] == SPRITE_BOX) && m_field[i+Coord::m_nb_col]!=SPRITE_WALL)
                {
                    m_field[i] = SPRITE_GROUND;
                }
            }
        }
        cpt++;
    }

}

//UPDATE FIELD
void Maze::ActualisationDuTerrain(Noeud a)
{
    for (unsigned int i=0; i <m_field.size(); i++)
    {
        if (!isSquareWall(i))
        {
            if(m_field[i]!=SPRITE_DEADSQUARE)
            {
                m_field[i] = SPRITE_GROUND;
            }
        }

    }
    for (unsigned int i=0; i<m_pos_goals.size(); i++)
    {
        if (m_field[m_pos_goals[i]]!=SPRITE_GOAL)
        {
            m_field[m_pos_goals[i]]=SPRITE_GOAL;
        }
    }
    m_pos_boxes = a.getTabPosBoites();
    m_pos_player = a.getPosJoueur();

    for (unsigned int i=0; i<m_pos_boxes.size(); i++)
    {
        if (m_field[m_pos_boxes[i]]!=SPRITE_BOX)
        {
            m_field[m_pos_boxes[i]] = SPRITE_BOX;
        }
    }
    for (unsigned int i=0; i<m_pos_goals.size(); i++)
    {
        if (m_field[m_pos_goals[i]]==SPRITE_BOX)
        {
            m_field[m_pos_goals[i]] = SPRITE_BOX_PLACED;
        }
    }

}


//TROUVERCHEMIN  ---Fonction pour algo DFS ET BFS

std::vector <unsigned short> Maze::TrouverChemin()
{
    //Variables
    std::vector <unsigned short> marquage; // tableau dynamique indiquant si les sommets sont marqués ou non
    std::vector <unsigned short> file;

    short dep(0);
    bool continuer(true);
    bool isMarked(false);
    int pivot = 0;

    unsigned short position = m_pos_player;
    //std::cout << m_pos_player << std::endl;

    file.push_back(position);
    // Créer (allouer) la file f et enfiler s dans f
    while(continuer){


        position = file[pivot];

        marquage.push_back(position);

        for (int i = 0; i< 4 ; i++){

            switch(i)
            {
            case 0 :
                dep = -Coord::m_nb_col;
                break;
            case 1:
                dep = Coord::m_nb_col;
                break;
            case 2 :
                dep = 1;
                break;
            case 3 :
                dep = -1;
                break;
            default :
                break;
            }



            if(isSquareWalkable(position + dep)){



                isMarked = false;
                for(int j = 0; j < marquage.size(); j++){
                    if(marquage[j] == position + dep ){
                        isMarked = true;
                        break;
                    }
                }

                if(!isMarked){
                    file.push_back(position + dep);
                }
            }

        }


        if(file.size() - 1 > pivot)
            pivot++;
        else
            continuer = false;

    }


    return marquage;
}



///CAN PLAYER REACH ---Fonction pour algo DFS ET BFS

std::vector<char> Maze::zoneVisite(unsigned short& boxPosition)
{

    std::vector<char> zone;
    std::vector <unsigned short> chemin;
    unsigned short playerPosition;

    chemin = TrouverChemin();

    for (char direction=0; direction<4; direction++)
    {
        playerPosition = Coord::getOppositeDirPos(boxPosition, direction);

        for (unsigned int i=0; i<chemin.size(); i++)
        {
            if (playerPosition == chemin[i])
            {
                zone.push_back(direction);
            }
        }

    }

    return zone;
}


bool Maze::canPlayerReach(unsigned short posPlayer)
{
    std::vector <unsigned short> chemin;
    chemin = TrouverChemin();

    for (unsigned int i=0; i<chemin.size(); i++)
    {
        if (posPlayer == chemin[i])
        {
            return true;
        }
    }
    return false;
}



