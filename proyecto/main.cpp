#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
using namespace std;
SDL_Window* window;
SDL_Renderer* renderer,*renderer2;
SDL_Event Event;
SDL_Texture *background,*b2,*character,*character2,*character3,*character4,*character6, *my_image;
SDL_Rect rect_background,rect_b2,rect_character,rect_character2,rect_character3,rect_character4,rect_character6, my_rect;

int screen_width = 500;
int screen_height = 250;

vector<SDL_Texture*> personaje_texture;
SDL_Rect rect_personaje;
int current_personaje = 0;

bool estaColisionando(SDL_Rect a, SDL_Rect b)
{
    a= rect_personaje;
    b= rect_character4;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}bool c2(SDL_Rect a, SDL_Rect b)
{
    a= rect_personaje;
    b= rect_character2;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}
int main( int argc, char* args[] )
{
    int i=0;
//Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
//Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
//SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }
    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1200;
    rect_background.h = 600;
    b2 = IMG_LoadTexture(renderer,"fondo2.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_b2.x = 1200;
    rect_b2.y = 0;
    rect_b2.w = 1200;
    rect_b2.h = 600;
    character2 = IMG_LoadTexture(renderer, "b1.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character2.x = 400;
    rect_character2.y = 0;
    rect_character2.w = 100;
    rect_character2.h = 50;
    character = IMG_LoadTexture(renderer, "suelo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 500;
    rect_character.w = 1200;
    rect_character.h = 200;
    character4 = IMG_LoadTexture(renderer, "b2.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character4.x = 1000;
    rect_character4.y = 500;
    rect_character4.w = 100;
    rect_character4.h = 50;

    character6 = IMG_LoadTexture(renderer, "logo.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character6.x = 1000;
    rect_character6.y = 500;
    rect_character6.w = 100;
    rect_character6.h = 50;
    personaje_texture.push_back(IMG_LoadTexture(renderer, "p1.png"));
    personaje_texture.push_back(IMG_LoadTexture(renderer, "p2.png"));
    rect_personaje.x = 0;
    rect_personaje.y = 300;
    my_image = IMG_LoadTexture(renderer, "image.png");
    my_rect.x = 1200;
    my_rect.y = 600;
    my_rect.w = 50;
    my_rect.h = 50;
    int velocidad = 5;
     int frames = 0;
//Main Loop
    char orien= 'u';
    char tation= 'a';
    bool game_over = false;
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            i++;
//mover background
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    rect_background.x--;
                if(Event.key.keysym.sym == SDLK_RIGHT)
                    rect_b2.x--;
                if(Event.key.keysym.sym == SDLK_LEFT)
                    rect_background.x++;
                if(Event.key.keysym.sym == SDLK_LEFT)
                    rect_b2.x++;
            }
        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
// p1,p2
        if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
        {
            rect_personaje.x--;
        }
        if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
        {
            rect_personaje.x++;
        }
//mover y regresar b1
        if(rect_character2.y>600)
        {
            orien='u';
        }
        if(rect_character2.y<0)
        {
            orien='d';
        }
        if(orien =='d')
        {
            rect_character2.y+=1;
        }
        if(orien == 'u')
        {
            rect_character2.y-=1;
        }
//mover y regresar b2
        if(rect_character4.y>600)
        {
            tation='b';
        }
        if(rect_character4.y<0)
        {
            tation='a';
        }
        if(tation =='a')
        {
            rect_character4.y+=1;
        }
        if(tation == 'b')
        {
            rect_character4.y-=1;
        }
//colision
        if(estaColisionando(rect_character,my_rect))
        {
            return game_over;
        }

        if(c2(rect_character,my_rect))
        {
            return game_over;
        }
     if(frames%10==0)
        {
            current_personaje++;
            if(current_personaje >= personaje_texture.size())
            {
                current_personaje = 0;
            }
        }
        frames++;
        if(!game_over)
        {
            if(rect_personaje.x>1200)
            {return game_over;
            }
        }
    SDL_QueryTexture(personaje_texture[0], NULL, NULL, &rect_personaje.w, &rect_personaje.h);
        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, b2, NULL, &rect_b2);
        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderCopy(renderer, character2, NULL, &rect_character2);
        SDL_RenderCopy(renderer, character3, NULL, &rect_character3);
        SDL_RenderCopy(renderer, character4, NULL, &rect_character4);
        SDL_RenderCopy(renderer, character6, NULL, &rect_character6);
        SDL_RenderCopy(renderer, my_image, NULL, &my_rect);
         SDL_RenderCopy(renderer, personaje_texture[current_personaje], NULL, &rect_personaje);
        SDL_RenderPresent(renderer);
        SDL_Delay(5);
    }
    return 0;
}
