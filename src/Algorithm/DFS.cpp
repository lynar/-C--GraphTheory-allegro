#include "DFS.h"

DFS::DFS(Maze maze) : Algorithm(maze)
{
    //ctor
}

DFS::~DFS()
{
    //dtor
}

std::vector <Noeud> DFS::perform(Graphic& g){
    return perform(m_maze, g);
}

//DFS
std::vector <Noeud> DFS::perform(Maze& maze, Graphic& g) {

   std::vector<Noeud> pile; // pile
    std::vector<Noeud> marquage; // Tab de marquage
    std::vector<Noeud> predecesseurs;
    bool ajout=false;
    unsigned short newPosBox(0);
    unsigned int compteur(0);
    int pivot = 0;
    unsigned short playerPosition;

    START_MEASUREMENT("DFS")


    Noeud depart(maze.getPosPlayer(),maze.getPosBoxes(),-1,TOP); // On crée le premier Noeud
    marquage.push_back(depart); // Le premier noeud est marqué
    pile.push_back(depart); // Le premier noeud est enfilé

    while (predecesseurs.empty()) //Tant que la file n'est pas vide
    {
        maze.detecterLesDeadLock();
        Noeud actuel = pile[pivot]; // le premier noeud est défilé
        maze.AfficherNoeud(actuel, g);
        maze.ActualisationDuTerrain(actuel); //On met le niveau avec les positions du joueur et des boites contenues dans ce noeud
        maze.setPlayerPos(actuel.getPosJoueur());


        for (unsigned int i = 0 ; i<actuel.getTabPosBoites().size(); i++) //Pour chaque boite du noeud actuel
        {
            unsigned short box = actuel.getPosBoite(i);
            std::vector<char> visite = maze.zoneVisite(box);

            for (unsigned short j=0; j<visite.size(); j++)
            {
                newPosBox =0;
                playerPosition = Coord::getOppositeDirPos(actuel.getPosBoite(i), visite[j]); //Nouvelle position de la boite

                if( maze._canPushBox(actuel.getPosBoite(i),visite[j],newPosBox))
                    //Si on peut bouger une boite vers la direction souhaitee
                {
                    std::vector<unsigned short> newPositions(actuel.getTabPosBoites()); //Creation d'une copie des positions des boites
                    newPositions[i] = newPosBox; //Modification de la position à l'index actuel
                    Noeud next = Noeud(playerPosition, newPositions,pivot,visite[j]); //Creation d'un nouveau noeud

                    ajout = false;
                    for(unsigned short i=0; i<marquage.size(); i++)
                    {
                        if(marquage[i]==next)
                        {
                            ajout=true;
                            break;
                        }

                    }

                    if(!ajout) //Si le noeud n'est pas marque

                    {

                        marquage.push_back(next); //On le marque
                        pile.push_back(next); //On le rajoute à la file
                    }
                }


            }
        }


        /// STOP CONDITIONS
        compteur = 0;
        for (unsigned int i=0; i<maze.getGoals().size(); i++)
        {
            if (maze.isSquareBoxPlaced(maze.getGoals()[i]))
            {
                compteur++;
            }
        }

        if (compteur==maze.getGoals().size()) // Si on l'a trouvée
        {
            Noeud temp = actuel;
            predecesseurs.push_back(temp);
            do
            {
                temp = pile[temp.getPredecesseur()];
                predecesseurs.push_back(temp);
            }
            while(temp.getPredecesseur() != -1);
        }
        else
        {
            pivot ++;
        }

    }

    END_MEASUREMENT()

    return predecesseurs;

}
