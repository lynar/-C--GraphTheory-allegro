#include "Menu.h"

#include <iostream>
#include <allegro.h>
#include <sstream>

#define CURSOR "images/curseur.bmp"
#define MARIO "images/mario.bmp"
#define FOND "images/fond.bmp"

#define OFFSET_MAIN_MENU 3
#define PADDING_MAIN_MENU 10
#define NUMBER_MAIN_MENU 5

#define BOUTON_SIZE 100
#define HEADER_SIZE 100
#define OFFSET_LIST 100

#define NBR_TEST 3
#define NBR_EASY 10
#define NBR_MEDIUM 3
#define NBR_HARD 3

Menu::Menu():m_state(MAIN_MENU), m_indice_level(0){

    const std::string niveau[] = {"test", "easy", "medium", "hard"};
    const int number[] = {3, 10, 3, 3};



//    m_levels = new std::vector<std::string>();
    for(int i = 0; i < 4; i++ ){
            for(int j = 1; j <= number[i]; j++ ){
                std::ostringstream stm ;
                stm << "./levels/" << niveau[i] << "/" << niveau[i] << "_" << j << ".dat";
                m_levels.push_back(stm.str());
                std::cout << m_levels.back() << std::endl;
            }
    }




}

Menu::~Menu(){
}


int Menu::afficherConsole()
{
    int choix(1);
    std::cout << "Tapez 1 pour tester l'algorithme de brute force" << std::endl;
    std::cout << "Tapez 2 pour tester l'algorithme de bfs" << std::endl;
    std::cout << "Tapez 3 pour tester l'algorithme de DFS" << std::endl;

    std::cout << "Tapez 0 pour quitter" << std::endl;

    std::cin >> choix;

    return choix;
}


int Menu::afficherAlgoMenu()
{

    BITMAP* curseur =   NULL;
    BITMAP* mario =     NULL;
    BITMAP* buffer =    NULL;


    int choix(-1);

    curseur = load_bitmap(CURSOR, NULL);
    mario = load_bitmap(MARIO, NULL);

    buffer = create_bitmap(SCREEN_W,SCREEN_H);




    while(choix == -1){

        clear_bitmap(buffer) ;

        rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,255,255));


        if (mouse_x >SCREEN_W/2 + OFFSET_MAIN_MENU && mouse_x < SCREEN_W - OFFSET_MAIN_MENU && mouse_y > SCREEN_H/NUMBER_MAIN_MENU * 1 + OFFSET_MAIN_MENU && mouse_y < SCREEN_H/NUMBER_MAIN_MENU * 2 - OFFSET_MAIN_MENU){
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 1 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 2 - OFFSET_MAIN_MENU, makecol(0,0,255));
            if(mouse_b & 1){
                choix = 2;

                if(m_prec_menu == MAIN_MENU)
                    m_indice_level += 1 % 19;

                while(mouse_b&1);
            }

        }
        else
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 1 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 2 - OFFSET_MAIN_MENU, makecol(0,0,125));


        if (mouse_x >SCREEN_W/2 + OFFSET_MAIN_MENU && mouse_x < SCREEN_W - OFFSET_MAIN_MENU && mouse_y > SCREEN_H/NUMBER_MAIN_MENU * 2 + OFFSET_MAIN_MENU && mouse_y < SCREEN_H/NUMBER_MAIN_MENU * 3 - OFFSET_MAIN_MENU){
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 2 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 3 - OFFSET_MAIN_MENU, makecol(0,255,0));
            if(mouse_b & 1){
                choix = 1;

                if(m_prec_menu == MAIN_MENU)
                    m_indice_level += 1 % 19;

                while(mouse_b&1);
            }
        }
        else
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 2 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 3 - OFFSET_MAIN_MENU, makecol(0,125,0));


        if (mouse_x >SCREEN_W/2 + OFFSET_MAIN_MENU && mouse_x < SCREEN_W - OFFSET_MAIN_MENU && mouse_y > SCREEN_H/NUMBER_MAIN_MENU * 3 + OFFSET_MAIN_MENU && mouse_y < SCREEN_H/NUMBER_MAIN_MENU * 4 - OFFSET_MAIN_MENU){
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 3 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 4 - OFFSET_MAIN_MENU, makecol(255,0,0));
            if(mouse_b & 1){
                choix = 0;

                if(m_prec_menu == MAIN_MENU)
                    m_indice_level += 1 % 19;

                while(mouse_b&1);
            }
        }
        else
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 3 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 4 - OFFSET_MAIN_MENU, makecol(125,0,0));


        if (mouse_x >SCREEN_W/2 + OFFSET_MAIN_MENU && mouse_x < SCREEN_W - OFFSET_MAIN_MENU && mouse_y > SCREEN_H/NUMBER_MAIN_MENU * 4 + OFFSET_MAIN_MENU && mouse_y < SCREEN_H/NUMBER_MAIN_MENU * 5 - OFFSET_MAIN_MENU){
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 4 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 5 - OFFSET_MAIN_MENU, makecol(255,251,0));
            if(mouse_b & 1){
                choix = 3;
                m_state = m_prec_menu;
                while(mouse_b&1);
            }
        }
        else
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 4 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 5 - OFFSET_MAIN_MENU, makecol(125,115,0));

        textout_centre_ex(buffer, font, m_levels[m_indice_level].c_str(), SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 0 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(0, 0, 0), -1);
        textout_centre_ex(buffer, font, "BFS", SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 1 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(255, 255,255), -1);
        textout_centre_ex(buffer, font, "BRUTE FORCE", SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 2 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(255, 255,255), -1);
        textout_centre_ex(buffer, font, "DFS", SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 3 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(255, 255,255), -1);

        textout_centre_ex(buffer, font, "RETOUR", SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 4 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(255, 255, 255), -1);

        stretch_sprite(buffer, mario,0,0,SCREEN_W/2 , SCREEN_H);

        draw_sprite(buffer, curseur, mouse_x, mouse_y);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    destroy_bitmap(mario);
    destroy_bitmap(curseur);
    destroy_bitmap(buffer);

    return choix;

}


int Menu::afficherListNiveau()
{

    BITMAP* curseur = NULL;
    BITMAP* buffer = NULL;


    int choix(-1);

    curseur = load_bitmap(CURSOR, NULL);

    buffer = create_bitmap(SCREEN_W,SCREEN_H);




    while(choix == -1){

        clear_bitmap(buffer) ;

        rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(25,25,25));

        int sizeElement = (SCREEN_H - HEADER_SIZE) / m_levels.size();

        for(int i = 0; i < m_levels.size(); i++){

            if (mouse_x > OFFSET_LIST && mouse_x < SCREEN_W - OFFSET_LIST && mouse_y >  i * sizeElement && mouse_y <  (i+1) * sizeElement){
                rectfill(buffer,OFFSET_LIST, i * sizeElement + 2, SCREEN_W - OFFSET_LIST,  (i+1) * sizeElement - 2, makecol(50,200,50));
                if(mouse_b & 1){
                    m_indice_level = i;
                    choix = 1;
                    m_state = ALGORITHME_MENU;
                    m_prec_menu = NIVEAU_MENU;
                    while(mouse_b&1);
                }
            }
            else
                rectfill(buffer,OFFSET_LIST, i * sizeElement + 2 , SCREEN_W - OFFSET_LIST,  (i+1) * sizeElement - 2, makecol(50,125,50));


            textout_ex(buffer, font, m_levels[i].c_str(), OFFSET_LIST + 10,  i * sizeElement + 10 , makecol(255, 255,255), -1);


        }


        if (mouse_x > OFFSET_MAIN_MENU && mouse_x < BOUTON_SIZE - OFFSET_MAIN_MENU && mouse_y > SCREEN_H - HEADER_SIZE - OFFSET_MAIN_MENU && mouse_y < SCREEN_H - OFFSET_MAIN_MENU){
            rectfill(buffer,OFFSET_MAIN_MENU,SCREEN_H - HEADER_SIZE - OFFSET_MAIN_MENU ,BOUTON_SIZE - OFFSET_MAIN_MENU, SCREEN_H - OFFSET_MAIN_MENU, makecol(255,0,0));
            if(mouse_b & 1){
                choix = 0;
                m_state = MAIN_MENU;
                while(mouse_b&1);
            }
        }
        else
            rectfill(buffer,OFFSET_MAIN_MENU, SCREEN_H - HEADER_SIZE - OFFSET_MAIN_MENU ,BOUTON_SIZE - OFFSET_MAIN_MENU, SCREEN_H - OFFSET_MAIN_MENU, makecol(125,0,0));


        textout_centre_ex(buffer, font, "Quitter", BOUTON_SIZE/2 + OFFSET_MAIN_MENU, SCREEN_H - HEADER_SIZE/2 - OFFSET_MAIN_MENU , makecol(255, 255,255), -1);


        draw_sprite(buffer, curseur, mouse_x, mouse_y);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    destroy_bitmap(curseur);
    destroy_bitmap(buffer);

    return choix;

}


int Menu::afficherMainMenu()
{

    BITMAP* curseur = NULL;
    BITMAP* mario = NULL;
    BITMAP* buffer = NULL;


    int choix(-1);

    curseur = load_bitmap(CURSOR, NULL);
    mario = load_bitmap(MARIO, NULL);

    buffer = create_bitmap(SCREEN_W,SCREEN_H);




    while(choix == -1){

        clear_bitmap(buffer) ;

        rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, makecol(255,255,255));


        if (mouse_x >SCREEN_W/2 + OFFSET_MAIN_MENU && mouse_x < SCREEN_W - OFFSET_MAIN_MENU && mouse_y > SCREEN_H/NUMBER_MAIN_MENU * 1 + OFFSET_MAIN_MENU && mouse_y < SCREEN_H/NUMBER_MAIN_MENU * 2 - OFFSET_MAIN_MENU){
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 1 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 2 - OFFSET_MAIN_MENU, makecol(0,0,255));
            if(mouse_b & 1){
                choix = 2;
                m_state = ALGORITHME_MENU;
                m_prec_menu = MAIN_MENU;
                m_indice_level=0;
                while(mouse_b&1);
            }
        }
        else
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 1 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 2 - OFFSET_MAIN_MENU, makecol(0,0,125));


        if (mouse_x >SCREEN_W/2 + OFFSET_MAIN_MENU && mouse_x < SCREEN_W - OFFSET_MAIN_MENU && mouse_y > SCREEN_H/NUMBER_MAIN_MENU * 2 + OFFSET_MAIN_MENU && mouse_y < SCREEN_H/NUMBER_MAIN_MENU * 3 - OFFSET_MAIN_MENU){
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 2 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 3 - OFFSET_MAIN_MENU, makecol(0,255,0));
            if(mouse_b & 1){
                choix = 1;
                m_state = NIVEAU_MENU;
                while(mouse_b&1);
            }
        }
        else
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 2 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 3 - OFFSET_MAIN_MENU, makecol(0,125,0));


        if (mouse_x >SCREEN_W/2 + OFFSET_MAIN_MENU && mouse_x < SCREEN_W - OFFSET_MAIN_MENU && mouse_y > SCREEN_H/NUMBER_MAIN_MENU * 3 + OFFSET_MAIN_MENU && mouse_y < SCREEN_H/NUMBER_MAIN_MENU * 4 - OFFSET_MAIN_MENU){
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 3 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 4 - OFFSET_MAIN_MENU, makecol(255,0,0));
            if(mouse_b & 1)
                choix = 0;
        }
        else
            rectfill(buffer,SCREEN_W/2 + OFFSET_MAIN_MENU,SCREEN_H/NUMBER_MAIN_MENU * 3 + OFFSET_MAIN_MENU ,SCREEN_W - OFFSET_MAIN_MENU, SCREEN_H/NUMBER_MAIN_MENU * 4 - OFFSET_MAIN_MENU, makecol(125,0,0));

        textout_centre_ex(buffer, font, "Lancer le jeu", SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 1 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(255, 255,255), -1);
        textout_centre_ex(buffer, font, "Niveaux", SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 2 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(255, 255,255), -1);
        textout_centre_ex(buffer, font, "Quitter", SCREEN_W/4*3, SCREEN_H/NUMBER_MAIN_MENU * 3 + SCREEN_H/NUMBER_MAIN_MENU/2 , makecol(255, 255,255), -1);

        stretch_sprite(buffer, mario,0,0,SCREEN_W/2 , SCREEN_H);

        draw_sprite(buffer, curseur, mouse_x, mouse_y);
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    destroy_bitmap(mario);
    destroy_bitmap(curseur);
    destroy_bitmap(buffer);

    return choix;

}
