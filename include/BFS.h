#ifndef BFS_H
#define BFS_H

#include <Algorithm.h>


class BFS : public Algorithm
{
    public:
        BFS(Maze maze);
        virtual ~BFS();

        static std::vector <Noeud> perform(Maze& maze, Graphic& g);

        std::vector<Noeud> perform(Graphic& g) override;

    protected:

    private:
};

#endif // BFS_H
