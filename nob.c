#define NOB_IMPLEMENTATION
#include "nob.h"

static const char* CC = "gcc";

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    bool debug = false;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "debug") == 0) {
            debug = true;
        }
    }

    Nob_Cmd cmd = {0};

    nob_cmd_append(&cmd, CC);
    nob_cmd_append(&cmd, "-Wall");
    nob_cmd_append(&cmd, "-Wextra");
    nob_cmd_append(&cmd, "-lm");

    if (debug) {
        nob_cmd_append(&cmd, "-DDEBUG");
        nob_cmd_append(&cmd, "-O0");
        nob_cmd_append(&cmd, "-g");
    } else {
        nob_cmd_append(&cmd, "-DNDEBUG");
        nob_cmd_append(&cmd, "-O3");
    }

    nob_cmd_append(&cmd, "-o");
    nob_cmd_append(&cmd, "bin/main");
    nob_cmd_append(&cmd, "src/main.c");

    nob_mkdir_if_not_exists("bin");

    if (!nob_cmd_run(&cmd))
        return 1;

    return 0;
}
