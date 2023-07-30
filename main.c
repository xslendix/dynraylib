#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include <dlfcn.h>
#include <raylib.h>

#include "dynconf.h"

void *lib_handler = NULL;
char *lib_path;

void (*update_func)(void) = NULL;
void (*init_func)(void) = NULL;

time_t prev_modification_date = 0;
time_t get_modification_date(void) {
  struct stat attr = {0};
  stat(lib_path, &attr);
  return attr.st_mtime;
}

bool reload_lib(void) {
  printf("Reloading. Library: %s\n", lib_path);
  fflush(stdout);

  update_func = NULL;
  if (lib_handler)
    dlclose(lib_handler);

  lib_handler = dlopen(lib_path, RTLD_NOW);

  if (!lib_handler) {
    fprintf(stderr, "Could not load library: %s\n", dlerror());
    return false;
  }

  update_func = dlsym(lib_handler, "rl_update");
  if (!update_func) {
    fprintf(stderr, "Could not load rl_update(): %s\n", dlerror());
    return false;
  }

  init_func = dlsym(lib_handler, "rl_init");
  if (!init_func) {
    fprintf(stderr, "Could not load rl_init(): %s\n", dlerror());
    return false;
  }

  puts("Reload complete.");
  fflush(stdout);

  prev_modification_date = get_modification_date();

  return true;
}

bool running = true;

int main(void) {
  lib_path = strdup("dyn.so");
  char *path = realpath(lib_path, NULL);
  if (path == NULL) {
    printf("cannot find file with name[%s]\n", lib_path);
  } else {
    free(lib_path);
  }
  lib_path = path;

  if (!reload_lib())
    return -1;

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

  init_func();

  while (running) {
    if (WindowShouldClose())
      break;

    if (get_modification_date() > prev_modification_date) {
      WaitTime(0.1);
      reload_lib();
      init_func();
    }

    if (update_func)
      update_func();
  }
  running = false;

  if (lib_handler)
    dlclose(lib_handler);

  CloseWindow();

  return 0;
}
