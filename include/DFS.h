#ifndef DFS_H
#define DFS_H

#include <Algorithm.h>


class DFS : public Algorithm
{
    public:
        DFS(Maze maze);
        virtual ~DFS();

        static std::vector <Noeud> perform(Maze& maze, Graphic& g);

        std::vector<Noeud> perform(Graphic& g) override;

    protected:

    private:
};

#endif // DFS_H
