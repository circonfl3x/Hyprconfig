#include <stdio.h>
#include "libs.h"
#include <stdlib.h>
int main(void){
    
    string *ssid = read_single_line_file("iwgetid -r", false, true);
    if(ssid == NULL)
        fprintf(stderr, "Install iwgetid");

    if(*ssid->data == '\0'){
        printf("No connection");
    }else {
        printl_s(ssid, 0, 10, true);
    }
    free_string(ssid);
    free(ssid);
    return 0;

}
