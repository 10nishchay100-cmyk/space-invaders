#include <iostream>
#include "../include/raylib.h"
struct player{
    float vx=0;
    float vy=0;
    float s=1;
    int health=2;
    Texture2D img;
    Rectangle rec;
    Rectangle scale={0.0f,0.0f,64.0f,64.0f};
    Vector2 pos={373.0f,500.0f};
    void init(){
        img=LoadTexture("assets/shooter.png");
        rec={0.0f,0.0f,(float)img.width,(float)img.height};
    }
    void draw(){
        scale.x = pos.x;
        scale.y = pos.y;
        DrawTexturePro(img,rec,scale,{0.0f,0.0f},0,WHITE);
        DrawRectanglePro(scale, {0.0f, 0.0f}, 0, Fade(RED, (3 - health) * 0.3f));
    }
    void unload(){
        UnloadTexture(img);
    }
struct bullet{
    float vx=0;
    float vy=0;
    float s=1;
    bool active=false;
    Vector2 pos={373.0f,500.0f};
    Texture2D img;
    Rectangle rec;
    Rectangle scale={0.0f,0.0f,16.0f,16.0f};
    void init(){
        img=LoadTexture("assets/bullet.png");
        rec={0.0f,0.0f,(float)img.width,(float)img.height};
    }
    void draw(){
        scale.x = pos.x;
        scale.y = pos.y;
        DrawTexturePro(img,rec,scale,{0.0f,0.0f},0,WHITE);
        scale.x = pos.x+52;
        scale.y = pos.y;
        DrawTexturePro(img,rec,scale,{0.0f,0.0f},0,WHITE);
    }
    void unload(){
        UnloadTexture(img);
    }
};
struct enemy{
    Texture2D img;
    int ix[15];
    int x[15];
    int y[15];
    int al[15];
    bool awd[15];
    Rectangle rec;
    Rectangle scale={0.0f,0.0f,50.0f,50.0f};
    void init(){
        for (int a=0; a<15; a++){
            ix[a]=a%5*160+55;
            x[a]=a%5*160+55;
            y[a]=(a/5)*80+55;
            al[a]=3;
            awd[a]=false;
        }
        img=LoadTexture("assets/enemy.png");
        rec={0.0f,0.0f,(float)img.width,(float)img.height};
    }
    void draw(){
        for (int a=0; a<15; a++){
            if (al[a]>0){
                scale.x=x[a];
                scale.y=y[a];
                DrawTexturePro(img,rec,scale,{0.0f,0.0f},0,WHITE);
                DrawRectanglePro(scale,{0.0f,0.0f},0,Fade(RED,(3-al[a])*0.3));
            }
        }
    }
    void unload(){
        UnloadTexture(img);
    }
};
int main(){
    InitWindow(800,600,"Shooter");
    SetTargetFPS(60);
    player pla;
    bullet bul;
    enemy ene;
    bool KeyPressed[5];
    pla.init();
    bul.init();
    ene.init();
    Texture2D bg=LoadTexture("assets/wall.png");
    while(!WindowShouldClose()){
        if (IsKeyDown(KEY_W)||IsKeyDown(KEY_UP)) KeyPressed[0]=true;else KeyPressed[0]=false;
        if (IsKeyDown(KEY_A)||IsKeyDown(KEY_LEFT)) KeyPressed[1]=true;else KeyPressed[1]=false;
        if (IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN)) KeyPressed[2]=true;else KeyPressed[2]=false;
        if (IsKeyDown(KEY_D)||IsKeyDown(KEY_RIGHT)) KeyPressed[3]=true;else KeyPressed[3]=false;
        if (IsKeyPressed(KEY_SPACE)||IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) KeyPressed[4]=true; else KeyPressed[4]=false;
        if (KeyPressed[0]) pla.vy-=2; else if (KeyPressed[2]) pla.vy+=2;
        if (KeyPressed[1]) pla.vx-=2; else if (KeyPressed[3]) pla.vx+=2;
        if (KeyPressed[4] && !bul.active){
            bul.active=true;
            bul.pos.x=pla.pos.x-2;
            bul.pos.y=pla.pos.y+32;
        } 
        if (bul.active) {
            bul.pos.y-=30;
            if (bul.pos.y<-32) bul.active=false;
        }
        pla.pos.x+=pla.vx;
        pla.pos.y+=pla.vy;
        pla.vx*=0.9;
        pla.vy*=0.9;
        if (pla.pos.x<0) pla.pos.x=0; else if (pla.pos.x>736) pla.pos.x=736;
        if (pla.pos.y<300) pla.pos.y=300; else if (pla.pos.y>543) pla.pos.y=543;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(bg,{0.0f,0.0f,(float)bg.width,(float)bg.height},{0.0f,0.0f,800.0f,600.0f},{0.0f,0.0f},0,WHITE);
        if (bul.active) bul.draw();
        pla.draw();
        ene.draw();
        EndDrawing();
    }
    pla.unload();
    bul.unload();
    ene.unload();
    UnloadTexture(bg);
    CloseWindow();
}
