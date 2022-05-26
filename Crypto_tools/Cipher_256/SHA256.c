#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

char * Convert(char const *key)
{
    unsigned char buf[SHA256_DIGEST_LENGTH]; //or SHA256_DIGEST_LENGTH
    SHA256((unsigned char const*)key, strlen(key), buf);

    char * res = malloc(sizeof(char)*SHA256_DIGEST_LENGTH+50);
    memset(res, 0, 82);
    char * ch = malloc(sizeof(char)*3);

    for(int i=0; i<sizeof(buf);i++)
    {
        sprintf(ch, "%.2hhx", buf[i]);
        strcat(res, ch);
    }
    return res;
}

void Gr256(char * message)
{
  sfRenderWindow *window;
  sfVideoMode video_mode = {1400, 800, 32};
  sfEvent event;
  sfTexture * empty = sfTexture_createFromFile("Ui_tools/CRY_SHA256/SHA256.png", NULL);

  window = sfRenderWindow_create(video_mode, "Hashage SHA-256", 
          sfClose | sfResize, NULL);

  sfSprite *img = sfSprite_create();
  sfFont * f;
  f = sfFont_createFromFile("./Ui_tools/Generals/ayar.ttf");

  char * msg = Convert((char const *) message);

  sfSprite_setTexture(img, empty, sfFalse);

  sfText * saved = SetText(message, 35, 95, f, sfBlue, 30);
  sfText * hash = SetText(msg, 35, 712, f, sfRed, 30);

  while(sfRenderWindow_isOpen(window))
  {
      sfRenderWindow_display(window);
      sfRenderWindow_drawSprite(window, img, NULL);
      sfRenderWindow_drawText(window, saved, NULL);
      sfRenderWindow_drawText(window, hash, NULL);

      while(sfRenderWindow_pollEvent(window, &event))
      {
          if(event.type == sfEvtClosed)
              sfRenderWindow_close(window);
      }
  }
}
