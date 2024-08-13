#include "libs.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

//static const char *bg = "brightnessctl g";
//static const char *bm = "brightnessctl m";

//Not using syscalls is 8-10 times faster (bruh)
static const char *bg = "/sys/class/backlight/intel_backlight/brightness";
static const char *bm = "/sys/class/backlight/intel_backlight/max_brightness";

int main(void){
    string *cmax = read_single_line_file(bm, false, false);
    string *ccurr = read_single_line_file(bg, false, false);

    float br = strtod(ccurr->data, NULL)/strtod(cmax->data, NULL);
    printf("%.0f", ceil(br*100));

    free_string(cmax);
    free_string(ccurr);
    free(cmax);
    free(ccurr);
    return 0;
}
