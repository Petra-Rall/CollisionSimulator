#include<iostream>
#include<vector>
#include<raylib.h>
#include<math.h>
using namespace std;

class Circle{
    public:
    float x, y;
    int speed_x, speed_y;
    float radius;
    Color color;
    void Draw(){
        DrawCircle(x, y, radius, color);
    }
    void Update(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius - 100 <= 0){
            speed_y *= -1;
        }
        if(x + radius >= GetScreenWidth() || x - radius <= 0){
            speed_x *= -1;
        } 
    }

};


Circle ball1, ball2, ball3;

void Collision(Circle &a, Circle &b) {
    if (CheckCollisionCircles(Vector2{a.x, a.y}, a.radius, Vector2{b.x, b.y}, b.radius)) {
        float m1 = a.radius * a.radius;
        float m2 = b.radius * b.radius;
        float u1 = a.speed_x;
        float u2 = b.speed_x;

        float v1 = ((m1 - m2) / (m1 + m2)) * u1 + ((2 * m2) / (m1 + m2)) * u2;
        float v2 = ((m2 - m1) / (m1 + m2)) * u2 + ((2 * m1) / (m1 + m2)) * u1;

        a.speed_x = v1;
        b.speed_x = v2;

        float dx = b.x - a.x;
    float dist = fabsf(dx);
    float minDist = a.radius + b.radius;
    if (dist < minDist && dist > 0) {
        float overlap = 0.5f * (minDist - dist);
        float direction = dx / dist;  // -1 or 1
        a.x -= overlap * direction;
        b.x += overlap * direction;
    }
    }
    
}



int main(){

    const int screen_width = 1280;
    const int screen_height = 800;
    const int center_x = screen_width/2;
    const int center_y = screen_height/2;
    InitWindow(screen_width, screen_height, "CollisionSim");
    SetTargetFPS(60);

    vector<int> starpos_x; 
    vector<int> starpos_y; 
    for( int i = 0; i < 300; i++){
        int x = GetRandomValue(1,screen_width-1);
        int y =  GetRandomValue(1, screen_height-1);
        starpos_x.push_back(x);
        starpos_y.push_back(y);
            
    }

    //Ball1
    ball1.x = 30;
    ball1.y = screen_height/2;
    ball1.radius = 30;
    ball1.speed_x = 10;
    ball1.speed_y = 1;
    ball1.color = BLUE;

    ball2.x = screen_width - 60;
    ball2.y = screen_height/2;
    ball2.radius = 20;
    ball2.speed_x = 20;
    ball2.speed_y = 1;
    ball2.color = BLUE;

    ball3.x = screen_width/2;
    ball3.y = screen_height/2 - 20;
    ball3.radius = 20;
    ball3.speed_x = 1;
    ball3.speed_y = 1;
    ball3.color = BLUE;

    vector<Circle> balls;
    int n = GetRandomValue(15,20);
    for(int i = 0; i < n; i++){
        Circle ball;
        ball.radius = GetRandomValue(20, 30);
        ball.x = GetRandomValue(ball.radius+5, screen_width - ball.radius - 5);
        ball.y = GetRandomValue(100, screen_height - ball.radius - 5);
        ball.speed_x = GetRandomValue(10, 20);
        ball.speed_y = 0;
        ball.color = WHITE;
        balls.push_back(ball);
    }



    while(WindowShouldClose() == false){
        BeginDrawing();
        
        //Update
        ball1.Update();
        ball2.Update();
        ball3.Update();
        for(int i = 0; i < n; i++){
            balls[i].Update();
        }

        ClearBackground(BLACK);

        //Checking for collisions
        Collision(ball1, ball2);
        Collision(ball1, ball3);
        Collision(ball2, ball3);
        for(int i = 0; i < n; i++){
            Collision(ball1, balls[i]);
            Collision(ball2, balls[i]);
            Collision(ball3, balls[i]);
            for(int j = i + 1; j < n; j++){
                Collision(balls[i], balls[j]);
            }
        }

        //Drawing

        //Stars
        for( int i = 0; i < 300; i++){
            DrawCircle(starpos_x[i], starpos_y[i], 1, RAYWHITE);
        }

        ball1.Draw();
        ball2.Draw();
        ball3.Draw();

        for(int i = 0; i < n; i++){
            balls[i].Draw();
        }

        DrawText(TextFormat("Total Balls: %i", n+3), 20, 20, 20, WHITE);

        DrawText(TextFormat("X-Velocities: %i,   %i,   %i,   ", ball1.speed_x, ball2.speed_x, ball3.speed_x), 20, 50, 20, WHITE);
        for (int i = 0; i < n; i++) {
            DrawText(TextFormat("%i, ",balls[i].speed_x), 300 + 50 * i, 50, 20, WHITE);
        }


        EndDrawing();
    }

    CloseWindow();
    return 0;
}