/*
 ============================================================================
 Name        : lnx_wayland_simple.c

 https://hdante.wordpress.com/2014/07/08/the-hello-wayland-tutorial
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wayland-client.h>


static const unsigned WIDTH = 320;
static const unsigned HEIGHT = 200;

static const unsigned CURSOR_WIDTH = 100;
static const unsigned CURSOR_HEIGHT = 59;

static const int32_t CURSOR_HOT_SPOT_X = 10;
static const int32_t CURSOR_HOT_SPOT_Y = 35;

static bool done = false;

void on_button(uint32_t button) {
    done = true;
}

int main(void) {
    struct wl_shm_pool *pool;
    struct wl_buffer *buffer;
    struct wl_shell_surface *surface;
    int fd_img;

    hello_setup_wayland();

    fd_img = open("images.bin", O_RDWR);

    if (fd_img < 0) {
        perror("Error opening surface image");
        return EXIT_FAILURE;
    }

    pool = hello_create_memory_pool(fd_img);
    surface = hello_create_surface();
    buffer = hello_create_buffer(pool, WIDTH, HEIGHT);
    hello_bind_buffer(buffer, surface);

    hello_set_cursor_from_pool(pool,
    		                   CURSOR_WIDTH, CURSOR_HEIGHT,
    		                   CURSOR_HOT_SPOT_X, CURSOR_HOT_SPOT_Y);

    hello_set_button_callback(surface, on_button);

    while (!done) {
        if (wl_display_dispatch(display) < 0) {
            perror("Main loop error");
            done = true;
        }
    }

    fprintf(stderr, "Exiting sample wayland client...\n");

    hello_free_cursor();
    hello_free_buffer(buffer);
    hello_free_surface(surface);
    hello_free_memory_pool(pool);
    close(fd_img);
    hello_cleanup_wayland();

    return EXIT_SUCCESS;
}
