//INCLUDE LIBRAIRIES
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <math.h>
#include <openssl/sha.h>

//INCLUDE CRYPTO PART
#include "Ui_tools/Ui_Widgets/CesarBox/Ui_Popupbox.c"
#include "Ui_tools/Ui_Widgets/VigenereBox/Ui_Popupboxvig.c"
#include "Ui_tools/Ui_Widgets/RSABox/Ui_PopRSA.c"
#include "Ui_tools/Ui_Widgets/SHABox/SHABox.c"

//INCLUDE ALGO PART
#include "Ui_tools/Ui_Widgets/AlgoBox/AlgoBox.c"

//INCLUDE CALCULATOR AND FUNCTION PLOT PART
#include "Math_Tools/calculator/calcu.c"
#include "Ui_tools/Ui_Widgets/PlotBox/PlotBox.c"
#include "Math_Tools/calculator/tinyexpr.h"



#define IMG "./Ui_tools/Generals/VAFAVAFA.png"
#define FONT "./Ui_tools/Generals/ayar.ttf"
#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 961



int main()
{
    sfRenderWindow *main;
    sfVideoMode video_mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};
    sfEvent event;
    sfTexture *empty = sfTexture_createFromFile(IMG, NULL);
    sfVector2i mouse_pos;


    sfSprite *img = sfSprite_create();


    main = sfRenderWindow_create(video_mode, "Visual Application of Fundamental Algorithms"
            , sfClose | sfResize , NULL);

    sfSprite_setTexture(img, empty, sfFalse);

    while(sfRenderWindow_isOpen(main))
    {
        sfRenderWindow_display(main);
        sfRenderWindow_drawSprite(main, img, NULL);
        mouse_pos = sfMouse_getPositionRenderWindow(main);

        if(event.type == sfEvtMouseButtonPressed)
        {
            //MATHS FUNCTIONS 2/2
            if(mouse_pos.x > 110 && mouse_pos.y > 610
                    && mouse_pos.x < 320 && mouse_pos.y < 665)
            {
                Call_calcu("./Ui_tools/MAT_Calcu/Calculator.png");
            }
            if(mouse_pos.x > 110 && mouse_pos.y > 742 
                    && mouse_pos.x < 315 && mouse_pos.y < 790)
            {
                Call_Plot(FONT, "./Ui_tools/MAT_Plot/BOXPlot.png");
            }

            //CRYPTO FUNCTIONS 4/4
            if(mouse_pos.x > 445  && mouse_pos.y > 590
                    && mouse_pos.x < 650 && mouse_pos.y < 642)
            {
               Call_Cesear(FONT, "./Ui_tools/CRY_Caesar/BOX2.png");
            }
            if(mouse_pos.x > 445  && mouse_pos.y > 670
                    && mouse_pos.x < 650 && mouse_pos.y < 723)
            {
               Call_Vig(FONT, "./Ui_tools/CRY_Vigenere/BOX2Vig.png");
            }

            if(mouse_pos.x > 445 && mouse_pos.y > 752
                    && mouse_pos.x < 650 && mouse_pos.y < 805)
            {
                Call_RSA(FONT, "./Ui_tools/CRY_RSA/BOXRSA.png");
            }

            if(mouse_pos.x > 445 && mouse_pos.y > 840 
                    && mouse_pos.x < 650 && mouse_pos.y < 885)
            {
                Call_SHA256(FONT, "./Ui_tools/CRY_RSA/BOXRSA.png");
            }


            //TREES FUNCTION 2/2
            if(mouse_pos.x > 825 && mouse_pos.y > 620
                    && mouse_pos.x < 1030 && mouse_pos.y < 670) //DFS
            {
                Call_Algo(FONT, "./Ui_tools/ALG_Graph/BOXGraph.png", 2); 
            }
            if(mouse_pos.x > 825 && mouse_pos.y > 750
                    && mouse_pos.x < 1030 && mouse_pos.y < 800) //BFS
            {
                Call_Algo(FONT, "./Ui_tools/ALG_Graph/BOXGraph.png", 3);
            }

            //GRAPHS FUNCTION 2/2
            if(mouse_pos.x > 1180 && mouse_pos.y > 615
                    && mouse_pos.x < 1386 && mouse_pos.y < 665) //DFS
            {
                Call_Algo(FONT, "./Ui_tools/ALG_Graph/BOXGraph.png", 0);
            }
            if(mouse_pos.x > 1180 && mouse_pos.y > 750
                    && mouse_pos.x < 1386 && mouse_pos.y < 800) //BFS
            {
                Call_Algo(FONT, "./Ui_tools/ALG_Graph/BOXGraph.png", 1);
            }

        }
        while(sfRenderWindow_pollEvent(main, &event))
        {
            if(event.type == sfEvtClosed)
                 sfRenderWindow_close(main);
        }
    }

    return 0;


}


