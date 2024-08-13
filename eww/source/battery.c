#include "libs.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
static const char *capacity="/sys/class/power_supply/BAT0/capacity";
static const char *charging_status = "/sys/class/power_supply/BAT0/status";
static const char *stop_threshold = "/sys/class/power_supply/BAT0/charge_stop_threshold";
static const char *start_threshold = "/sys/class/power_supply/BAT0/charge_start_threshold";
int8_t get_curr_charge();
int8_t get_full_capacity();
string *gfc();
bool is_charging();
//returns mem
char *f_readbuff(const char *path){
    char *buff = malloc(16);

    FILE *f = fopen(path, "r");
    if(!f){
        return NULL;
    }
    
    fgets(buff, 16, f);
    fclose(f);
    return buff;



}
int main(int argc, char **argv){
    string *wh = gfc(); 
    bool charge = is_charging();
    char *ch_s = itoa(charge);
    // string *json = create_simple_json_struct(wh->data, ch_s,NULL);
    string *json = create_simple_json_struct_i("c",wh->data, "p",ch_s, NULL);
    printf("%s\n", json->data);

    free(ch_s);
    free_string(json);
    free_string(wh);
    free(wh);
    free(json);
    // int8_t t = 66;
    return 0;
}
bool is_charging(){
   FILE *f = fopen(charging_status, "r");
   int ch = fgetc(f);
   if(ch == 'N') return false;
   else return true;
}
int8_t get_curr_charge(){
}

int8_t get_full_capacity(){
    int8_t capacity;
    string *data = 
        read_single_line_file("/sys/class/power_supply/BAT0/capacity", false, false);
    if(data == NULL) return -1;
    printf("%s", data->data);
    capacity = atoi(data->data); 
    free_string(data);
    free(data); 
    /*char *d = f_readbuff("/sys/class/power_supply/BAT0/capacity");
    if(d==NULL) return -1;
    printf("%s", d);
    capacity = atoi(d);
    free(d);*/

    return capacity;
}


string *gfc(){
    string *data = 
        read_single_line_file("/sys/class/power_supply/BAT0/capacity", false, false);
    

    return data;

}
