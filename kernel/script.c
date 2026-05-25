#include <kernel/script.h>
#include <kernel/tty.h>
#include <string.h>

void script_run(const char* code) {
    tty_printf("MicroOS Scripting Engine: Executing script...\n");

    if (strncmp(code, "loop ", 5) == 0) {
        int count = code[5] - '0';
        tty_printf("Running loop %d times...\n", count);
        for(int i = 0; i < count; i++) {
            tty_printf("Hello from script loop %d!\n", i + 1);
        }
    } else if (strncmp(code, "print ", 6) == 0) {
        tty_printf("%s\n", code + 6);
    } else {
        tty_printf("Script Error: Unknown syntax.\n");
    }
}
