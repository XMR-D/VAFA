#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tinyexpr.h"

double te_interp(const char *expression, int *error);

sfVertexArray * PlotPoints(const char * fnct, unsigned long nbpoints, 
        sfColor color)
{
    sfVertexArray *p = sfVertexArray_create();

    sfVector2f pos = {0.0f, 0.0f};

    sfVertex point = {
        .position = pos,
        .color = color,
        .texCoords = pos,
    };

    sfVertexArray_setPrimitiveType(p, sfPoints);

    double * x = malloc(sizeof(double)*nbpoints);
    double * f_x = malloc(sizeof(double)*nbpoints);

    size_t j = 0;

    for(double i = -20.0f; i <= 20.0f; i += 0.00008f)
    {
        x[j] = i;
        j += 1;
    }

    double pt;

    te_variable vars[] = {{"x", &pt}};

    int err;
    te_expr *n = te_compile(fnct, vars, 1, &err);

    if(n)
    {
        for(unsigned long i = 0; i <= nbpoints; i++)
        {
            pt = x[i];
            f_x[i] = te_eval(n);
            f_x[i] *= -1;
        }
        te_free(n);
    }

    for (unsigned long i = 0; i <= nbpoints; i++)
    {
        sfVector2f pos = {(float) (x[i]*28)+564, (float) (f_x[i]*13)+264};
        point.position = pos;
        point.texCoords = pos;
        sfVertexArray_append(p, point);
    }
    return p;
}



void GrPlot(char * fn1, char * fn2, char * fn3)
{
    sfRenderWindow *window;
    sfVideoMode video_mode = {1138, 532, 32};
    sfEvent MainWindow;

    sfTexture *empty = sfTexture_createFromFile("./Math_Tools/curve/graph.png", NULL);
    sfSprite *img = sfSprite_create();

    window = sfRenderWindow_create(video_mode, "functions",
            sfClose | sfResize, NULL);

    sfSprite_setTexture(img, empty, sfFalse);

    sfVertexArray * p = PlotPoints(fn1, 500000, sfBlue);
    
    sfVertexArray * p2 = PlotPoints(fn2, 500000, sfRed);
    
    sfVertexArray * p3 = PlotPoints(fn3, 500000, sfGreen);


    while(sfRenderWindow_isOpen(window))
    {
        sfRenderWindow_display(window);
        sfRenderWindow_drawSprite(window, img, NULL);
        if(strlen(fn1) != 0)
            sfRenderWindow_drawVertexArray(window, p, NULL);
        if(strlen(fn2) != 0)
            sfRenderWindow_drawVertexArray(window, p2, NULL);
        if(strlen(fn3) != 0)
            sfRenderWindow_drawVertexArray(window, p3, NULL);

        while(sfRenderWindow_pollEvent(window, &MainWindow))
        {
            if(MainWindow.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
            }

        }
    }
}
