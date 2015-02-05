#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/ioctl.h>
#include<linux/fb.h>
#include"fb_env.h"


#define T fb_env_t

struct T{
    struct fb_fix_screeninfo    fixed_info;
    struct  fb_var_screeninfo   var_info;
    struct  fb_cmap             colormap;
    char                        *fbname;
    void                        *framebuffer;
    int                         fbdev;
    int                         framebuffer_size;
    int                         ppc_fix;
    int                         page_size;
};



/**
 * initialize work and clear up
 */
T        
fb_env_init(char *fb_name)
{
    //fbname = "/dev/fb0";
    return NULL; 
}
void
fb_env_close(T fb_env)
{
}

/**
 * frame buffer display area size
 */
int
fb_env_width
(T fb_env)
{
    return 0;
}
int
fb_env_height
(T fb_env)
{
    return 0;
}

/**
 * Bit per pixel
 */
int
fb_env_bpp
(T fb_env)
{
    return 32;
}


/**
 * set & get pixel
 * if x or y overstep the boundary
 * then throw fb exception
 */
void
fb_env_set_pixel
(T fb_env, int x, int y, int color)
{
}
int
fb_env_get_pixel
(T fb_env, int x, int y)
{
    return 0;
}

/**
 * get & set pixels of whole screen
 * user should ensure the bbp and 
 * the length of the buffer thenself
 */
void *
fb_env_load_pixels
(T fb_env)
{
    return NULL;
}
void
fb_env_update_pixels
(T fb_env, void *pixels)
{
}
