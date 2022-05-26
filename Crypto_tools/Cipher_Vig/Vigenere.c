#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <string.h>
#include "Tools.h"

void GrVigenere(char plaintext[], char key[])
{
   
        char *saved_un = malloc((sizeof(char) * strlen(plaintext))+sizeof(char));
        char *saved_ci = malloc((sizeof(char) * strlen(plaintext))+sizeof(char));
        char *saved_key = malloc((sizeof(char) * strlen(key))+sizeof(char));

        strcpy(saved_key, key);
        strcpy(saved_un, plaintext);

        char u1 = saved_un[0];
        char u2 = saved_un[1];
        char u3 = saved_un[2];
        char u4 = saved_un[3];
        char u5 = saved_un[4];
        char u_n_1 = saved_un[strlen(plaintext)-2];
        char u_n = saved_un[strlen(plaintext)-1];

        char k1 = saved_key[0];
        char k2 = saved_key[1];
        char k3 = saved_key[2];
        char k4 = saved_key[3];
        char k5 = saved_key[4];
        char k_n_1 = saved_key[strlen(plaintext)-2];
        char k_n = saved_key[strlen(plaintext)-1];

        Vigenere2_0(plaintext, key);
        strcpy(saved_ci, plaintext);

        char c1 = saved_ci[0];
        char c2 = saved_ci[1];
        char c3 = saved_ci[2];
        char c4 = saved_ci[3];
        char c5 = saved_ci[4];
        char cn_1 = saved_ci[strlen(plaintext)-2];
        char cn = saved_ci[strlen(plaintext)-1];

        sfRenderWindow *window;
        sfVideoMode video_mode = {1401, 800, 32};
        sfEvent event;
        sfTexture *empty = sfTexture_createFromFile("Ui_tools/CRY_Vigenere/Vigenere.bmp", NULL);


        sfSprite *img = sfSprite_create();
        sfFont* f;
        f = sfFont_createFromFile("Ui_tools/Generals/ayar.ttf");


        //set uncipher text
        sfText *uncipher = SetText(saved_un, 50, 110, f, sfRed, 30);

        //set cipher text
        sfText *cipher = SetText(saved_ci, 240, 725, f, sfBlue, 30);


        //set rotation
        sfText *rot = SetText(saved_key, 690, 110, f, sfGreen, 30);

        //set key chars
        sfText *kn1 = SetText(c_to_s(k1), 470, 195, f, sfGreen, 35);
        sfText *kn2 = SetText(c_to_s(k2), 470, 245, f, sfGreen, 35);
        sfText *kn3 = SetText(c_to_s(k3), 470, 295, f, sfGreen, 35);
        sfText *kn4 = SetText(c_to_s(k4), 470, 345, f, sfGreen, 35);
        sfText *kn5 = SetText(c_to_s(k5), 470, 395, f, sfGreen, 35);
        sfText *knn_1 = SetText(c_to_s(k_n_1), 470, 585, f, sfGreen, 35);
        sfText *knn = SetText(c_to_s(k_n), 470, 633, f, sfGreen, 35);


        //set cipher chars
        sfText *cn1 = SetText(c_to_s(c1), 730, 195, f, sfBlue, 35);
        sfText *cn2 = SetText(c_to_s(c2), 730, 245, f, sfBlue, 35);
        sfText *cn3 = SetText(c_to_s(c3), 730, 295, f, sfBlue, 35);
        sfText *cn4 = SetText(c_to_s(c4), 730, 345, f, sfBlue, 35);
        sfText *cn5 = SetText(c_to_s(c5), 730, 395, f, sfBlue, 35);
        sfText *cnn_1 = SetText(c_to_s(cn_1), 730, 585, f, sfBlue, 35);
        sfText *cnn = SetText(c_to_s(cn), 730, 633, f, sfBlue, 35);


        //set unciphers chars
        sfText *un1 = SetText(c_to_s(u1), 325, 195, f, sfRed, 35);
        sfText *un2 = SetText(c_to_s(u2), 325, 245, f, sfRed, 35);
        sfText *un3 = SetText(c_to_s(u3), 325, 295, f, sfRed, 35);
        sfText *un4 = SetText(c_to_s(u4), 325, 345, f, sfRed, 35);
        sfText *un5 = SetText(c_to_s(u5), 325, 395, f, sfRed, 35);
        sfText *unn_1 = SetText(c_to_s(u_n_1), 325, 585, f, sfRed, 35);
        sfText *unn = SetText(c_to_s(u_n), 325, 633, f, sfRed, 35);

        window = sfRenderWindow_create(video_mode, "Chiffrement Vigenère",
                sfClose | sfResize , NULL);



        sfSprite_setTexture(img, empty, sfFalse);

        while(sfRenderWindow_isOpen(window))
        {
            sfRenderWindow_display(window);
            sfRenderWindow_drawSprite(window, img, NULL);

            //draw ciph, unciph and key
            sfRenderWindow_drawText(window, uncipher, NULL);
            sfRenderWindow_drawText(window, cipher, NULL);
            sfRenderWindow_drawText(window, rot, NULL);

            //draw each char
            sfRenderWindow_drawText(window, kn1, NULL);
            sfRenderWindow_drawText(window, kn2, NULL);
            sfRenderWindow_drawText(window, kn3, NULL);
            sfRenderWindow_drawText(window, kn4, NULL);
            sfRenderWindow_drawText(window, kn5, NULL);
            sfRenderWindow_drawText(window, knn_1, NULL);
            sfRenderWindow_drawText(window, knn, NULL);

            sfRenderWindow_drawText(window, un1, NULL);
            sfRenderWindow_drawText(window, un2, NULL);
            sfRenderWindow_drawText(window, un3, NULL);
            sfRenderWindow_drawText(window, un4, NULL);
            sfRenderWindow_drawText(window, un5, NULL);
            sfRenderWindow_drawText(window, unn_1, NULL);
            sfRenderWindow_drawText(window, unn, NULL);
            sfRenderWindow_drawText(window, cn1, NULL);
            sfRenderWindow_drawText(window, cn2, NULL);
            sfRenderWindow_drawText(window, cn3, NULL);
            sfRenderWindow_drawText(window, cn4, NULL);
            sfRenderWindow_drawText(window, cn5, NULL);
            sfRenderWindow_drawText(window, cnn_1, NULL);
            sfRenderWindow_drawText(window, cnn, NULL);

            while(sfRenderWindow_pollEvent(window, &event))
            {
                if(event.type == sfEvtClosed)
                    sfRenderWindow_close(window);
            }
        }
    
}
