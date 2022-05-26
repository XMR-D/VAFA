#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>


void extend(int size, char key[], char returned[])
{
    int j = 0;
    for(int i = 0; i <= size; i++)
    {
        if(key[j] == '\0')
        {
            j = 0;
            returned[i] = key[j];
            j++;
        }
        else
        {
            returned[i] = key[j];
            j++;
        }
    }
}

void Vigenere2_0(char msg[], char key[])
{
    char ret[strlen(msg)+1];
    ret[strlen(msg)] = '\0';
    extend(strlen(msg)-1, key, ret);

    for(size_t i = 0; msg[i] != '\0'; i++)
    {
        if(msg[i] <= 122 && msg[i] >= 97)
        {
            size_t val = ((msg[i] - 97) + (ret[i] - 97)) % 26;
            msg[i] = val + 97;
        }
        if(msg[i] <= 90 && msg[i] >= 65)
        {
            ret[i] -= 32;
            size_t val = ((msg[i] - 65) + (ret[i] - 65)) % 26;
            msg[i] = val + 65;
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


