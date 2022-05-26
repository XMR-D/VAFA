#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define MAXSIZE 100

double te_interp(const char *expression, int *error);

void Call_calcu(char * path)
{
    sfRenderWindow *window;
    sfVideoMode video_mode = {403, 671, 32};
    sfEvent MainWindow;

    sfTexture *empty = sfTexture_createFromFile(path, NULL);
    sfSprite *img = sfSprite_create();
    sfVector2i mouse_pos;

    window = sfRenderWindow_create(video_mode, "Calculatrice",
            sfClose | sfResize, NULL);

    sfSprite_setTexture(img, empty, sfFalse);
    sfFont* f;
    f = sfFont_createFromFile("./Ui_tools/Generals/ayar.ttf");


    char *expr = malloc(sizeof(char)*51);
    sfText *ex;
    memset(expr, 0, 51);
    memset(expr, 0, 51);


    while(sfRenderWindow_isOpen(window))
    {
        sfRenderWindow_display(window);
        sfRenderWindow_drawSprite(window, img, NULL);

        ex = SetText(expr, 20, 25, f, sfBlack, 25);
        sfRenderWindow_drawText(window, ex, NULL);

        while(sfRenderWindow_pollEvent(window, &MainWindow))
        {

            if(MainWindow.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if(MainWindow.type == sfEvtMouseButtonPressed)
            {
                mouse_pos = sfMouse_getPositionRenderWindow(window);

                if(mouse_pos.x > 11 && mouse_pos.x < 85 &&
                        mouse_pos.y > 180 && mouse_pos.y < 250)
                    {memset(expr, 0, strlen(expr));}

                if(mouse_pos.x > 115 && mouse_pos.x < 190 &&
                        mouse_pos.y > 180 && mouse_pos.y < 250)
                    {strcat(expr, "(");}

                if(mouse_pos.x > 215 && mouse_pos.x < 290 &&
                    mouse_pos.y > 180 && mouse_pos.y < 250)
                    {strcat(expr, ")");}

                if(mouse_pos.x > 315 && mouse_pos.x < 390 &&
                        mouse_pos.y > 180 && mouse_pos.y < 250)
                    {strcat(expr, "/");}
                if(mouse_pos.x > 11 && mouse_pos.x < 85 &&
                        mouse_pos.y > 280 && mouse_pos.y < 350)
                    {strcat(expr, "7");}

                if(mouse_pos.x > 115 && mouse_pos.x < 190 &&
                        mouse_pos.y > 280 && mouse_pos.y < 350)
                    {strcat(expr, "8");}

                if(mouse_pos.x > 215 && mouse_pos.x < 290 &&
                        mouse_pos.y > 280 && mouse_pos.y < 350)
                    {strcat(expr, "9");}

                if(mouse_pos.x > 315 && mouse_pos.x < 390 &&
                        mouse_pos.y > 280 && mouse_pos.y < 350)
                    {strcat(expr, "*");}

                if(mouse_pos.x > 11 && mouse_pos.x < 85 &&
                        mouse_pos.y > 380 && mouse_pos.y < 450)
                    {strcat(expr, "4");}

                if(mouse_pos.x > 115 && mouse_pos.x < 190 &&
                        mouse_pos.y > 380 && mouse_pos.y < 450)
                    {strcat(expr, "5");}

                if(mouse_pos.x > 215 && mouse_pos.x < 290 &&
                        mouse_pos.y > 380 && mouse_pos.y < 450)
                    {strcat(expr, "6");}

                if(mouse_pos.x > 315 && mouse_pos.x < 390 &&
                        mouse_pos.y > 380 && mouse_pos.y < 450)
                    {strcat(expr, "-");}

                if(mouse_pos.x > 11 && mouse_pos.x < 85 &&
                        mouse_pos.y > 480 && mouse_pos.y < 550)
                    {strcat(expr, "1");}

                if(mouse_pos.x > 115 && mouse_pos.x < 190 &&
                        mouse_pos.y > 480 && mouse_pos.y < 550)
                    {strcat(expr, "2");}

                if(mouse_pos.x > 215 && mouse_pos.x < 290 &&
                        mouse_pos.y > 480 && mouse_pos.y < 550)
                    {strcat(expr, "3");}

                if(mouse_pos.x > 315 && mouse_pos.x < 390 &&
                        mouse_pos.y > 480 && mouse_pos.y < 550)
                    {strcat(expr, "+");}

                if(mouse_pos.x > 11 && mouse_pos.x < 85 &&
                        mouse_pos.y > 580 && mouse_pos.y < 650)
                    {strcat(expr, ".");}

                if(mouse_pos.x > 115 && mouse_pos.x < 190 &&
                        mouse_pos.y > 580 && mouse_pos.y < 650)
                    {strcat(expr, "0");}

                if(mouse_pos.x > 215 && mouse_pos.x < 390 &&
                        mouse_pos.y > 580 && mouse_pos.y < 650)
                    {
                        sprintf(expr, "%f", te_interp(expr, 0));
                    }
            }

        }
    }
}
