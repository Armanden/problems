#include "raylib.h"
#include <stdlib.h>
#include <string.h>

#define GRID_WIDTH  100
#define GRID_HEIGHT 100
#define CELL_SIZE   8

int main(void) {
    int screenWidth  = GRID_WIDTH  * CELL_SIZE;
    int screenHeight = GRID_HEIGHT * CELL_SIZE;

    InitWindow(screenWidth, screenHeight, "100x100 Grid");
    SetTargetFPS(60);

    bool *grid = (bool *)calloc(GRID_WIDTH * GRID_HEIGHT, sizeof(bool));
    bool *next = (bool *)calloc(GRID_WIDTH * GRID_HEIGHT, sizeof(bool));

    bool paused = true;
    bool dragging = false;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        int mx = (int)mouse.x / CELL_SIZE;
        int my = (int)mouse.y / CELL_SIZE;

        if (mx >= 0 && mx < GRID_WIDTH && my >= 0 && my < GRID_HEIGHT) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                dragging = true;
                grid[my * GRID_WIDTH + mx] = !grid[my * GRID_WIDTH + mx];
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && dragging) {
                grid[my * GRID_WIDTH + mx] = true;
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                dragging = false;
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                grid[my * GRID_WIDTH + mx] = false;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            paused = !paused;
        }
        if (IsKeyPressed(KEY_R)) {
            memset(grid, 0, GRID_WIDTH * GRID_HEIGHT * sizeof(bool));
        }
        if (IsKeyPressed(KEY_G)) {
            for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
                grid[i] = GetRandomValue(0, 1);
            }
        }

        if (!paused) {
            for (int y = 0; y < GRID_HEIGHT; y++) {
                for (int x = 0; x < GRID_WIDTH; x++) {
                    int neighbors = 0;
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            if (dx == 0 && dy == 0) continue;
                            int nx = x + dx;
                            int ny = y + dy;
                            if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                                neighbors += grid[ny * GRID_WIDTH + nx];
                            }
                        }
                    }
                    int idx = y * GRID_WIDTH + x;
                    if (grid[idx]) {
                        next[idx] = (neighbors == 2 || neighbors == 3);
                    } else {
                        next[idx] = (neighbors == 3);
                    }
                }
            }
            bool *tmp = grid;
            grid = next;
            next = tmp;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int x = 0; x < GRID_WIDTH; x++) {
                if (grid[y * GRID_WIDTH + x]) {
                    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE,
                                  CELL_SIZE - 1, CELL_SIZE - 1, GREEN);
                } else {
                    DrawRectangle(x * CELL_SIZE, y * CELL_SIZE,
                                  CELL_SIZE - 1, CELL_SIZE - 1, DARKGRAY);
                }
            }
        }

        DrawText(paused ? "PAUSED (SPACE to run)" : "RUNNING (SPACE to pause)",
                 10, 10, 16, WHITE);
        DrawText("[R]eset  [G]lider gun  LMB:draw  RMB:erase",
                 10, screenHeight - 24, 12, LIGHTGRAY);

        EndDrawing();
    }

    free(grid);
    free(next);
    CloseWindow();

    return 0;
}
