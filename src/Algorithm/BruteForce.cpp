#include "BruteForce.h"


/** \brief
 *
 * \param maze Maze
 *
 */
BruteForce::BruteForce(Maze maze) :Algorithm(maze)
{
}

BruteForce::~BruteForce()
{
    //dtor
}


std::vector <Noeud> BruteForce::perform(Graphic& g){
    return perform(m_maze, g);
}

//BRUTE FORCE
std::vector <Noeud> BruteForce::perform(Maze& maze, Graphic& g)
{
   //Variables, g
    char dir (' ');
    unsigned short direction(0);
    bool fin(false);
    unsigned int indiceA(0);
    //On créé dabord le premier qui correspond à la position de départ du joueur et des boites
    Noeud first(maze.getPosPlayer(),maze.getPosBoxes(),-1,TOP);
    std::vector <Noeud> solution;
    std::vector <Noeud> arbre;
    arbre.push_back(first);

    START_MEASUREMENT("Brute Force")


    while (!fin)
    {
        maze.detecterLesDeadLock();
        direction = 0;
        //On teste les 4 directions
        while (direction<4)
        {


            //On engistre les positions du noeud actuel
            maze.ActualisationDuTerrain(arbre[indiceA]);


            //On bouge le joueur
            maze.updatePlayer(direction);


            Noeud nouveau (maze.getPosPlayer(),maze.getPosBoxes(),indiceA,direction);

            //On regarde si le noeud existe déjà
            bool same = false;
            for (unsigned int i=0; i<arbre.size(); i++)
            {
                if (arbre[i] == nouveau)
                {
                    same=true;
                }
            }

            if (!same)
            {
                //On ajoute le noeud dans l'arbre
                arbre.push_back(nouveau);

                maze.AfficherNoeud(nouveau, g);

//                readkey();
            }

            //On change de direction
            direction++;
        }

        unsigned int cpt(0);
        //On regarde si on a trouvé la solution
        for (unsigned int i=0; i<maze.getGoals().size(); i++)
        {
            if (maze.isSquareBoxPlaced(maze.getGoals()[i]))
            {
                cpt++;
            }
            if (cpt==maze.getGoals().size())
            {
                fin =true;
            }
        }

        //On passe au noeud suivant
        indiceA++;

    }

    //On sait que le noeud solution est le noeud situé à la fin de l'arbre


    Noeud temp = arbre.back();
    solution.push_back(temp);
    do
    {
        temp = arbre[temp.getPredecesseur()];
        solution.push_back(temp);
    }
    while(temp.getPredecesseur() != -1);




    END_MEASUREMENT()

    return solution;
}
