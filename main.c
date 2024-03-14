#include <raylib.h>
#include <stdlib.h>

typedef enum {
     Menu,
     Game,
     Paused,
} g;

int game_state;

Vector2 w;

void state_machine(Vector2 canvas);

int main (void) {
     SetConfigFlags (FLAG_WINDOW_RESIZABLE);
     SetTraceLogLevel (LOG_ERROR);
     int factor = 100;
     w.x = 16*factor, w.y = 9*factor;
     InitWindow (w.x, w.y, "Menu");
     game_state = Menu;
     while (!WindowShouldClose()) {
          BeginDrawing();
               ClearBackground(GREEN);
               state_machine(w);
          EndDrawing();
     }
     CloseWindow();
     return 0;
}

void state_machine(Vector2 canvas) {
     Rectangle rec = {
          .x = 0,
          .y = 0,
          .width = canvas.x,
          .height = canvas.y
     };
     Color pause_color = BLACK;
     pause_color.a = 100;
     switch (game_state) {
          case Menu: {
               DrawRectangleRec (rec, SKYBLUE);
               DrawText ("Hello World", canvas.x/2, canvas.y/2, canvas.x/50, WHITE);
               if (IsKeyPressed(KEY_W)) game_state = Game;
               if (IsKeyPressed(KEY_Q)) exit(EXIT_SUCCESS);
          } break;
          case Game: {
               DrawRectangleRec (rec, GREEN);
               DrawText ("We Started!", canvas.x/2, canvas.y/2, canvas.x/50, WHITE);
               if (IsKeyPressed(KEY_Q)) game_state = Menu;
               if (IsKeyPressed(KEY_P)) game_state = Paused;
          } break;
          case Paused: {
               DrawRectangleRec (rec, pause_color);
               DrawText ("Paused", canvas.x/2, canvas.y/2, canvas.x/50, WHITE);
               if (IsKeyPressed (KEY_P) || IsKeyPressed (KEY_Q))
                    game_state = Game;
          } break;    
          default: {
               TraceLog (LOG_ERROR, "Unreachable state.\n");                  
          }
     }
}
