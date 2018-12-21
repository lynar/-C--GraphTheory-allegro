#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "maze.h"
#include "Noeud.h"
#include "utils/coord.h"
#include "utils/performance.h"
#include <vector>

class Algorithm
{
    public:
        Algorithm(Maze maze);
        virtual ~Algorithm();

        virtual std::vector<Noeud> perform(Graphic& g) = 0;


    protected:

        /*  Maze where to perform Algorithm */
        Maze m_maze;

    private:


};

#endif // ALGORITHM_H
