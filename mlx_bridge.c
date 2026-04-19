#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>
#include <stdlib.h>

typedef struct s_mlx {
    SDL_Window *win;
    SDL_Renderer *renderer;
    SDL_Texture *screen_buffer; // The "MiniLibX" persistent canvas
    int (*key_hook)(int, void *);
    void *key_param;
    int (*loop_hook)(void *);   // Stores put_chicken
    void *loop_param;
} t_mlx;

void *mlx_init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);
    t_mlx *mlx = calloc(1, sizeof(t_mlx));
    return mlx;
}

void *mlx_new_window(void *mlx_ptr, int w, int h, char *title) {
    t_mlx *mlx = (t_mlx *)mlx_ptr;
    
    // Create the window
    mlx->win = SDL_CreateWindow(title, 0, 0, w, h, 0);
    
    // THE FIX: Tell SDL not to attempt VSync syncing during creation!
    // This permanently stops the "Cannot set timing mode" red error.
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    
    // Create the renderer
    mlx->renderer = SDL_CreateRenderer(mlx->win, -1, SDL_RENDERER_ACCELERATED);
    
    // Create the persistent canvas
    mlx->screen_buffer = SDL_CreateTexture(mlx->renderer, SDL_PIXELFORMAT_RGBA8888, 
                                           SDL_TEXTUREACCESS_TARGET, w, h);
    
    // Tell SDL to draw everything onto our canvas, not the browser screen
    SDL_SetRenderTarget(mlx->renderer, mlx->screen_buffer);
    SDL_SetRenderDrawColor(mlx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(mlx->renderer);
    
    return mlx;
}

void *mlx_xpm_file_to_image(void *mlx, char *path, int *w, int *h) {
    SDL_Surface *surf = IMG_Load(path);
    if (!surf) return NULL;
    
    SDL_Surface *formatted = SDL_ConvertSurfaceFormat(surf, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surf);
    
    *w = formatted->w; *h = formatted->h;
    SDL_Texture *tex = SDL_CreateTextureFromSurface(((t_mlx*)mlx)->renderer, formatted);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(formatted);
    return tex;
}

void *mlx_new_image(void *mlx_ptr, int width, int height) {
    t_mlx *mlx = (t_mlx *)mlx_ptr;
    SDL_Texture *tex = SDL_CreateTexture(mlx->renderer, SDL_PIXELFORMAT_RGBA8888, 
                                         SDL_TEXTUREACCESS_TARGET, width, height);
    
    // BLENDMODE_NONE tells SDL to completely overwrite the pixels underneath it
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_NONE);
    
    SDL_SetRenderTarget(mlx->renderer, tex);
    
    // SOLID BLACK: R=0, G=0, B=0, Alpha=255
    SDL_SetRenderDrawColor(mlx->renderer, 0, 0, 0, 255); 
    SDL_RenderClear(mlx->renderer);
    
    // Crucial: Go back to drawing on the main canvas!
    SDL_SetRenderTarget(mlx->renderer, mlx->screen_buffer);
    return tex;
}

int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y) {
    t_mlx *mlx = (t_mlx *)mlx_ptr;
    if (!img_ptr || !mlx->renderer) return -1;
    SDL_Rect dst = {x, y, 0, 0};
    SDL_QueryTexture((SDL_Texture *)img_ptr, NULL, NULL, &dst.w, &dst.h);
    
    // Stamp the image onto the canvas
    SDL_RenderCopy(mlx->renderer, (SDL_Texture *)img_ptr, NULL, &dst);
    return 0; // We don't Present here anymore!
}

int mlx_hook(void *win, int ev, int mask, int (*f)(), void *p) {
    t_mlx *mlx = (t_mlx *)win;
    if (ev == 2) { mlx->key_hook = f; mlx->key_param = p; }
    return 0;
}

int mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param) {
    t_mlx *mlx = (t_mlx *)mlx_ptr;
    mlx->loop_hook = f;
    mlx->loop_param = param;
    return 0;
}

void emscripten_main_loop(void *arg) {
    t_mlx *mlx = (t_mlx *)arg;
    SDL_Event event;

    // 1. Check for Key Presses
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN && mlx->key_hook)
            mlx->key_hook(event.key.keysym.sym, mlx->key_param);
    }

    // 2. Run your animation hook (put_chicken)
    if (mlx->loop_hook)
        mlx->loop_hook(mlx->loop_param);

    // 3. Magic: Push the persistent canvas to the actual browser screen
    SDL_SetRenderTarget(mlx->renderer, NULL);
    SDL_RenderCopy(mlx->renderer, mlx->screen_buffer, NULL, NULL);
    SDL_RenderPresent(mlx->renderer);
    
    // 4. Set target back to canvas for the next frame
    SDL_SetRenderTarget(mlx->renderer, mlx->screen_buffer);
}

int mlx_loop(void *mlx_ptr) {
    // 1. Cancel any existing loop so we don't get the "only one loop" crash
    // This allows you to safely restart the game!
    emscripten_cancel_main_loop(); 
    
    // 2. Start the new loop
    emscripten_set_main_loop_arg(emscripten_main_loop, mlx_ptr, 0, 1);
    return 0;
}

int mlx_destroy_image(void *m, void *i) { if(i) SDL_DestroyTexture(i); return 0; }
int mlx_destroy_window(void *mlx_ptr, void *win_ptr) {
    // 1. Stop the browser's game loop immediately
    emscripten_cancel_main_loop(); 
    
    // 2. We deliberately DO NOT call SDL_DestroyWindow! 
    // This leaves the canvas intact so the player can see the final frame,
    // and prevents SDL from crashing the WebGL context.
    return 0;
}
int mlx_get_screen_size(void *mlx_ptr, int *w, int *h) {
    // Ask the browser for the current width and height of the window
    *w = emscripten_run_script_int("window.innerWidth");
    *h = emscripten_run_script_int("window.innerHeight");
    
    return 0;
}