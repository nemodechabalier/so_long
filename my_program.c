#include "minilibx-linux/mlx.h"

int main() {
    void *mlx;
    void *window;

    // Initialize the MiniLibX connection
    mlx = mlx_init();

    // Create a new window
    window = mlx_new_window(mlx, 800, 600, "My first window");

    // Draw a pixel at (400, 300) with the color white (0xFFFFFF)
    mlx_pixel_put(mlx, window, 400, 300, 0xFFFFFF);

    // Enter the event loop to keep the window open
    mlx_loop(mlx);

    return 0;
}
