#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "Algorithm.h"



class BruteForce : public Algorithm
{
    public:
        BruteForce(Maze maze);
        virtual ~BruteForce();

        static std::vector <Noeud> perform(Maze& maze, Graphic& g);

        std::vector<Noeud> perform(Graphic& g) override;

    protected:

    private:
};

#endif // BRUTEFORCE_H
