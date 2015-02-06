#ifndef FB_ENV_INCLUDE
#define FB_ENV_INCLUDE

#define T fb_env_t

typedef unsigned char byte;

typedef struct T *T;


/**
 * initialize work and clear up
 */
extern T        fb_env_init(const char *fbname);
extern void     fb_env_close(T fb_env);

/**
 * frame buffer display area size
 */
extern int      fb_env_width(T fb_env);
extern int      fb_env_height(T fb_env);

/**
 * Bit per pixel
 */
extern int      fb_env_bpp(T fb_env);


/**
 * set & get pixel
 * if x or y overstep the boundary
 * then throw fb exception
 */
extern void     fb_env_set_pixel_32(T fb_env, int x, int y, int color);
extern int      fb_env_get_pixel_32(T fb_env, int x, int y);
extern int      fb_env_makecolor_32(T fb_env, byte a, byte r, byte g, byte b);

/**
 * get & set pixels of whole screen
 * user should ensure the bbp and 
 * the length of the buffer themself
 */
extern void    *fb_env_load_pixels(T fb_env);
extern void     fb_env_update_pixels(T fb_env, void *pixels);


#undef T
#endif /*FB_ENV_INCLUDE*/
