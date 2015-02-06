#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/ioctl.h>
#include<linux/fb.h>
#include"assert.h"
#include"except.h"
#include"mem.h"
#include"fb_env.h"


#define T fb_env_t
#define DEFAULT_FB "/dev/fb0"

struct T{
    struct fb_fix_screeninfo    fixed_info;
    struct  fb_var_screeninfo   var_info;
    struct  fb_cmap             colormap;
    u_int16_t                   r, g, b;
    const char                 *fbname;
    void                        *framebuffer;
    int                         fbdev;
    ssize_t                     framebuffer_size;
    ssize_t                     ppc_fix;
    ssize_t                     page_size;
};



/**
 * initialize work and clear up
 */
T        
fb_env_init(const char *fbname)
{
    T fb;

    NEW(fb);
    
    if(NULL == fbname)
        fb->fbname = DEFAULT_FB;
    else
        fb->fbname = fbname;


    fb->fbdev = open(fb->fbname, O_RDWR);
    if(fb->fbdev < 0)
        goto OPEN_FAILED;

    if(ioctl(fb->fbdev, FBIOGET_FSCREENINFO, &(fb->fixed_info)) < 0)
        goto IO_FAILED;
    if(ioctl(fb->fbdev, FBIOGET_VSCREENINFO, &(fb->var_info)) < 0)
        goto IO_FAILED;

    fb->page_size = getpagesize();
    fb->ppc_fix = (((long) fb->fixed_info.smem_start) - 
                ((long)fb->fixed_info.smem_start & ~(fb->page_size-1)));
    fb->framebuffer_size = fb->fixed_info.smem_len + fb->ppc_fix;
    fb->framebuffer = mmap(NULL,
                fb->framebuffer_size,
                PROT_READ | PROT_WRITE,
                MAP_SHARED,
                fb->fbdev,
                0);

    if(NULL == fb->framebuffer)
        goto MMP_FAILED;

    /**
     * when need set  palette
    if(FB_VISUAL_PSEUDOCOLOR == fb->fixed_info.visual ||
       FB_VISUAL_DIRECTCOLOR == fb->fixed_info.visual){

        fb->r = 0xFFFF;
        fb->g = 0xFFFF;
        fb->b = 0xFFFF;
        
        fb->colormap.start = 255;
        fb->colormap.len = 1;
        fb->colormap.red = &r;
        fb->colormap.green = &g;
        fb->colormap.blue = &b;
        fb->colormap.transp = NULL;

        if(ioctl(fbdev, FBIOPUTCMAP, &colormap) < 0)
            goto COLORMAP_FAILED;
    }*/

    return fb;

COLORMAP_FAILED:
MMP_FAILED:
IO_FAILED:
    close(fb->fbdev);
OPEN_FAILED:
    FREE(fb);
    fb = NULL;
    return fb;
}
void
fb_env_close(T fb_env)
{
    assert(fb_env);

    munmap(fb_env->framebuffer, fb_env->framebuffer_size);
    close(fb_env->fbdev);
    FREE(fb_env);
}

/**
 * frame buffer display area size
 */
int
fb_env_width
(T fb_env)
{
    assert(fb_env);
    return fb_env->var_info.xres;
}
int
fb_env_height
(T fb_env)
{
    assert(fb_env);
    return fb_env->var_info.yres;
}

/**
 * Bit per pixel
 */
int
fb_env_bpp
(T fb_env)
{
    assert(fb_env);
    return fb_env->var_info.bits_per_pixel;
}


/**
 * set & get pixel
 * if x or y overstep the boundary
 * then throw fb exception
 */
void
fb_env_set_pixel_32
(T fb_env, int x, int y, int color)
{
    u_int32_t *buff;
    
    buff = (u_int32_t *)fb_env->framebuffer;

    *(buff + fb_env->fixed_info.line_length/4 * y + x) = color;
}
int
fb_env_get_pixel_32
(T fb_env, int x, int y)
{
    return 0;
}

int 
fb_env_makecolor_32
(T fb_env, byte a, byte r, byte g, byte b)
{
    int pixel_value;
        
    pixel_value = (((a >> (8-fb_env->var_info.transp.length)) <<
                    fb_env->var_info.transp.offset) + 
                   ((r >> (8-fb_env->var_info.red.length)) <<
                    fb_env->var_info.red.offset) + 
                   ((g >> (8-fb_env->var_info.green.length)) <<
                    fb_env->var_info.green.offset) + 
                   ((b >> (8-fb_env->var_info.blue.length)) <<
                    fb_env->var_info.blue.offset));
    return pixel_value;
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
