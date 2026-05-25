#include <kernel/shell.h>
#include <kernel/tty.h>
#include <kernel/network.h>
#include <drivers/keyboard.h>
#include <kernel/script.h>
#include <string.h>

extern int mos_load_and_run(const char* path);

#define MAX_CMD_LEN 256

static void handle_command(char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        tty_printf("Commands: ls, dir, cd, copy, move, delete, rename, mkdir, tree, find\n");
        tty_printf("Archive: extract, compress, zip, unzip, tar, 7z\n");
        tty_printf("Network: ping, download, upload, connect, wifi, netinfo, curl, wget\n");
        tty_printf("Package: pkg install, pkg remove, pkg update, pkg search, pkg upgrade\n");
        tty_printf("System: tasklist, kill, meminfo, cpuinfo, shutdown, restart, clear\n");
        tty_printf("Scripting: run <script_code>\n");
        tty_printf("Execute MOS: exec <path>\n");
    } else if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "dir") == 0) {
        tty_printf("bin/  apps/  kernel/  sys/  home/  etc/  var/\n");
    } else if (strncmp(cmd, "run ", 4) == 0) {
        script_run(cmd + 4);
    } else if (strncmp(cmd, "exec ", 5) == 0) {
        mos_load_and_run(cmd + 5);
    } else if (strncmp(cmd, "ping ", 5) == 0) {
        net_ping(cmd + 5);
    } else if (strncmp(cmd, "curl ", 5) == 0) {
        net_curl(cmd + 5);
    } else if (strcmp(cmd, "meminfo") == 0) {
        tty_printf("Memory Total: 1024 MB\nMemory Free: 1012 MB\n");
    } else if (strcmp(cmd, "clear") == 0) {
        tty_clear();
    } else if (strcmp(cmd, "shutdown") == 0) {
        tty_printf("System halted.\n");
        while(1) asm("hlt");
    } else if (strcmp(cmd, "") == 0) {
        // Do nothing
    } else {
        tty_printf("MicroOS: Command not found: %s\n", cmd);
    }
}

void shell_start(void) {
    char cmd[MAX_CMD_LEN];
    int cmd_idx = 0;

    tty_printf("Welcome to MicroOS Shell!\n");
    tty_printf("Type 'help' for a list of commands.\n");
    tty_printf("microos> ");

    while (1) {
        char c = keyboard_get_char();
        if (c > 0) {
            if (c == '\n') {
                tty_putc('\n');
                cmd[cmd_idx] = '\0';
                handle_command(cmd);
                cmd_idx = 0;
                if (strcmp(cmd, "shutdown") != 0) {
                    tty_printf("microos> ");
                }
            } else if (c == '\b') {
                if (cmd_idx > 0) {
                    cmd_idx--;
                }
            } else if (cmd_idx < MAX_CMD_LEN - 1) {
                cmd[cmd_idx++] = c;
                tty_putc(c);
            }
        }
    }
}
