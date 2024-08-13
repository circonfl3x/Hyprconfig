#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libs.h"

typedef struct{
    
    string *name;
    bool connected;
    int8_t battery;
} bluedevice;

void bfree(bluedevice *b){
    free_string(b->name);
    free(b->name);
}
int main(void){
    
    const char *cmd = "bluetoothctl devices | cut -f2 -d ' ' | while read uuid;do bluetoothctl info $uuid;done | grep -e 'Device\\|Connected\\|Name'";
    filebuff *fb = fbuff(cmd, true);
    if(fb == NULL){
        fprintf(stderr, "No bluetooth");
        
        return EXIT_FAILURE;
    }
    bluedevice *b = malloc(sizeof(bluedevice));
    b->name = malloc(sizeof(string));
    new_string(b->name);
    b->connected = false;
    char *p;
    bool connect = false;
    for(int i = 0; i < fb->lines; ++i){
        // printf("%s\n", trim(fb->data[i]->data));
        char connected;
        int8_t acc;
        if(*fb->data[i]->data == 'D'){
            // printf("%s\n", fb->data[i]->data);
            if(i+2 < fb->lines && (connected = fb->data[i+2]->data[12]) == 'n'){
                    i+=2; 
            }else{
                ++acc;
                if(i+1 < fb->lines){
                    ++acc;
                    char *name = fb->data[i+1]->data;
                    name+=7; //hardcoded tab width lmao (100% won't backfire)
                    // printf("%s\n", name);
                    if(i+2 < fb->lines){
                        ++acc;
                        // char *cn = fb->data[i+2]->data;
                        // cn+=12; //this just fucking works idk
                        // printf("%s\n", cn);
                        if(connected == 'y'){ //will skip this check in the future?
                            connect = true;
                            concat(b->name, name);
                            b->connected = true;
                            break;
                        }
                    }
                }
                i+=acc-1; //subract one magic number?
            }
        }
    }
    if(!b->connected){
        printf("󰂲\n");
    }
    else printf("%s\n", b->name->data);
    
    bfree(b);
    free(b);
    free_fbuff(fb);
    free(fb->data);
    free(fb);

    // free_string(b->name);
    // bfree(b);
    return 0;
}
