#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu
{
    public:
        Menu();

        virtual ~Menu();

        enum typeMenu {
            MAIN_MENU,
            NIVEAU_MENU,
            ALGORITHME_MENU,
            TIMING_MENU
        };

        enum typeLevels {
            TEST    = 0,
            EASY    = 1,
            MEDIUM  = 2,
            HARD    = 3
        };

        static int afficherConsole();
        int afficherMainMenu();
        int afficherListNiveau();
        int afficherAlgoMenu();

        std::vector<std::string> m_levels;
        int m_indice_level;

        typeMenu m_state;

        typeMenu m_prec_menu;

    protected:

    private:





};

#endif // MENU_H
