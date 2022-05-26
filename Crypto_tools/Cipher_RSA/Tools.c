#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <errno.h>

void caesar2(char msg[], int key)
{
    for(size_t i = 0; msg[i] != '\0'; i++)
    {
        if(msg[i] <= 90 && msg[i] >= 65)
        {
            msg[i] = ((msg[i]-90)+key) % 26 + 90;
            while(msg[i] < 65)
                msg[i] += 26;
            while(msg[i] > 90)
                msg[i] = (msg[i] - 90)+64;
        }
        else
        {
            if(msg[i] <= 122 && msg[i] >= 97)
            {
                msg[i] = ((msg[i]-122)+key) % 26 + 122;
                while(msg[i] < 97)
                    msg[i] += 26;
                while(msg[i] > 122)
                    msg[i] = (msg[i] - 122) + 96;
            }
        }
    }
}

sfText * SetText(char str[], int x, int y, sfFont *f, sfColor col, int size)
{


    sfVector2f coord = {x,y};
    sfText *string = sfText_create();
    sfText_setString(string, str);
    sfText_setPosition(string, coord);
    sfText_setCharacterSize(string, size);
    sfText_setFont(string, f);
    sfText_setColor(string, col);
    return string;
}

char* c_to_s(char c)
{
    char *res = malloc(3 * sizeof(char));
    res[0] = c;
    res[1] = ' ';
    res[2] = '\0';
    return res;
}

