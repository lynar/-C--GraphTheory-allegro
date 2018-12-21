/************************************************************
Sokoban project - Main file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/
#include "maze.h"
#include "graphic.h"
#include "utils/console.h"
#include "utils/coord.h"
#include <iostream>

#include "utils/performance.h"

#include "BruteForce.h"
#include "BFS.h"
#include "DFS.h"

#include "Menu.h"

// Init allegro with 800x600 (resolution)
Graphic g(800,600,24);


int main()
{
    // Do not touch !
    Console::getInstance()->setColor(_COLOR_DEFAULT);
    bool test(false);
    int exit(-1);
    // Load level from a file




    Menu menu;


    if (!g.init()) return -1;


        // While playing...
        while (exit != 0)
        {

            switch(menu.m_state){
            case Menu::MAIN_MENU:
                exit = menu.afficherMainMenu();
                break;
            case Menu::NIVEAU_MENU:

                menu.afficherListNiveau();



                break;
            case Menu::ALGORITHME_MENU:

                Maze m (menu.m_levels[menu.m_indice_level]);
                if(!m.init()) return -1;

                switch(menu.afficherAlgoMenu()){
                    case 1:
                        m.AFFICHERSOLUTIONMARIO(BruteForce::perform(m, g),g);
                        break;
                    case 2:
                        m.AFFICHERSOLUTIONMARIO(BFS::perform(m, g),g);
                        break;
                    case 0:
                        m.AFFICHERSOLUTIONMARIO(DFS::perform(m,g),g);
                        break;
                    default:
                        break;


                }




            }



        }


    // Free memory
    g.deinit();
    Console::deleteInstance();



    return 0;
}
END_OF_MAIN()




