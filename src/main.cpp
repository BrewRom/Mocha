#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include "SDL2/SDL.h"
#include <unistd.h>

#define SOCKET_PATH "/tmp/sdlx_input.sock"

int main() {
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("SDL failed to initialize");
        return -1;
    }

    if (SDL_NumJoysticks() > 0) {
        if (!SDL_IsGameController(0)) {
            printf("Game controller 0 is not a game controller");
            return -1;
        }

        SDL_GameControllerOpen(0);
    }

    int unix_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (unix_socket < 0) {
        perror("socket");
        return -1;
    }

    
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);

    printf("Waiting for GTKX to connect...\n");
    while (connect(unix_socket, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        sleep(1);
    }
    printf("Connected to GTKX!\n");


    return 1;
}