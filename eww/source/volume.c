#include "libs.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
static const char *vol_path = "wpctl get-volume @DEFAULT_SINK@";

int main(void){
    
    string *s = read_single_line_file(vol_path, false, true);
    s->data+=8; //hard coded add 8 to remove 'Volume:' nothing can go wrong
    // int8_t vol;
    // if(s->length > 12){
    // }
    char *t = "[";
    int8_t vol = (strtod(s->data,&t)*100); //TODO: error handling
    // printf("%d\n", vol);
    s->length > 13 ? printf("{\"m\":1,\"v\":%d}", vol) : printf("{\"m\":0,\"v\":%d}", vol);
    s->data -= 8;
    free_string(s);
    // free(s->data);
    free(s);
    

    return 0;
}
