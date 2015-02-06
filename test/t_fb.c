#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"fb_env.h"


int make_color_32(int r, int g, int b){

}

int
main
(int argc, char *argv[])
{
    fb_env_t    fb;
    int purple, green;
    int x, y, width;

    fb = fb_env_init(NULL);

    if(NULL != fb){

        printf("Fb env %dx%d, bpp:%d\n",
                fb_env_width(fb),
                fb_env_height(fb),
                fb_env_bpp(fb));
        
        width = fb_env_width(fb);

        purple = fb_env_makecolor_32(fb,
                        100, 155, 16, 155);

        green = fb_env_makecolor_32(fb,
                        100, 16, 225, 16);
        for(y=125; y < 150; y++)
            for(x=125; x <  150; x += 1){
                fb_env_set_pixel_32(fb, x, y, purple);
            }
        
        for(y=100; y < 200; y++)
            for(x=100; x <  200; x += 1){
                fb_env_set_pixel_32(fb, x, y, green);
            }

        fb_env_close(fb);
    }else{

        printf("Create fb env error: %s.\n",
                strerror(errno));
    }
}


