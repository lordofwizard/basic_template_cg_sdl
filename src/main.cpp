#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int red[4] = { 255,0,0,0 };

class Game{
    SDL_Event event;
    SDL_Window * window;
    SDL_Renderer * renderer;
        void set_color(int color[4]){
            SDL_SetRenderDrawColor(renderer,
                    color[0],
                    color[1],
                    color[2],
                    color[3]);
        };
        void putpixel(int x, int y){
            SDL_RenderDrawPoint(renderer,x,y);
            SDL_RenderPresent(renderer);
        };
    
        int DDA(int X0, int Y0, int X1, int Y1){
            // calculate dx & dy
            int dx = X1 - X0;
            int dy = Y1 - Y0;
     
            // calculate steps required for generating pixels
            int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
     
            // calculate increment in x & y for each steps
            float Xinc = dx / (float)steps;
            float Yinc = dy / (float)steps;
     
            // Put pixel for each step
            float X = X0;
            float Y = Y0;
            for (int i = 0; i <= steps; i++) {
                if( SDL_PollEvent(&event) && event.type == SDL_QUIT) break;
                putpixel(round(X), round(Y)); // put pixel at (X,Y)
                X += Xinc; // increment in x at each step
                Y += Yinc; // increment in y at each step
                SDL_Delay(100); // for visualization of line-
            }
            return 0;
        };
    void game_loop(){
        int i = 1;
        set_color(red);
        while (true){
            if( SDL_PollEvent(&event) && event.type == SDL_QUIT) break;
            DDA(100,200,1000,586);
            //for(int i = 1, i < WINDOW_HEIGHT, i++){
             //   putpixel(i,i);
           // }
           i++;
           break;
        }
    };
public:
    Game(){
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,0,&window,&renderer);
        SDL_SetRenderDrawColor(renderer,    0,  0,  0,  0);
        SDL_RenderClear(renderer);
        game_loop();
    };

    ~Game(){
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        std::cout << "Everything destroyed well " << std::endl;
    };
    
};

Game g;

int main(){
    return 0;
}
