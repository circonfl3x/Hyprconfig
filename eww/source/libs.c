#include "libs.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <stdarg.h>

void new_string(string *s){
    s->data = malloc(1);
    s->length = 1;
    *(s->data) = '\0';
}

void append_char(string *s, const char chr){
    s->length++;
    s->data = realloc(s->data, s->length);
    s->data[s->length-2] = chr;
    s->data[s->length-1] = '\0';

}

void free_string(string *s){
    free(s->data);
}
filebuff *fbuff(const char *filepath, bool syscall)
{
    filebuff *fb = malloc(sizeof(filebuff));
    
    FILE *f;
    f = syscall ? popen(filepath, "r") : fopen(filepath, "r");
    if(!f){
        return NULL;
    } 
    int ch;
    fb->data = malloc(sizeof(string*));
    fb->lines = 0;
    fb->data[fb->lines] = malloc(sizeof(string));
    new_string(fb->data[fb->lines]);

    //TODO: Would probs be faster to calculate then just fgets that but welp
    while((ch = fgetc(f)) != EOF){
        // printf("%c", ch);
        if(ch == '\n'){
            fb->lines++;
            fb->data = realloc(fb->data, sizeof(string*)*(fb->lines+1));
            fb->data[fb->lines] = malloc(sizeof(string));
            new_string(fb->data[fb->lines]);
        }
        else append_char(fb->data[fb->lines], ch); 
    }


    fclose(f);

    return fb;
}
void free_fbuff(filebuff *fbuff){
   for(int i = 0; i <= fbuff->lines; ++i){
        // free(fbuff->data[i]->data);
        // free_string(fbuff->data[i]);
        free_string(fbuff->data[i]);
        free(fbuff->data[i]);
   } 
}
void concat(string *s, const char *s2){
    size_t s2_len = strlen(s2);
    s->data = realloc(s->data, s->length + s2_len +1);
    strncat(s->data, s2, s2_len);
    s->length += s2_len;
}


// void free_fbuff(filebuff *fbuff){
    // _free_string_arrmem(fbuff->data, fbuff->lines);
    // for(int i = 0; i < fbuff->lines; ++i){
        // free_string(fbuff->data[i]);
        // free(fbuff->data[i]);
    // }
//
    // for(int i = 0; i < fbuff->lines; ++i){
        // free_string(fbuff->data[i]);
        // free(fbuff->data[i]);
        // free(fbuff->data);
    // }

// }

//deprecated for now
char *trim(const char *s){
}


void _free_string_arrmem(string **s, unsigned long len){
    for(unsigned long i = 0; i < len; ++i){
        free_string(s[i]);
        free(s[i]);
        
    }
    free(s);
}
bool isdir_wrapper(const char *path){
    struct stat s;
    int d = stat(path, &s);
    switch(d){
        case EACCES:
            fprintf(stderr, "Cannot access filepath");
            return false;
        break;

        case ENOTDIR:
            return false;
        break;


    }

    switch(s.st_mode & S_IFMT){
        case S_IFDIR:
            return true;
        break;

        default:
            return false;
        break;
    }
}

bool isdir_s(string *s){
    return isdir_wrapper(s->data);
}


bool isfile_wrapper(const char *path){
    struct stat s;
    int d = stat(path, &s);
    switch(d){
        case EACCES:
            fprintf(stderr, "Cannot access filepath");
            return false;
        break;

        case ENOTDIR:
            // return false;
        break;


    }

    // printf("%d %d\n", s.st_mode & S_IFMT, S_IFREG);
    switch(s.st_mode & S_IFMT){

        case S_IFREG:
            return true;
        break;

        default:
            return false;
        break;
    }
}

bool isfile_s(string *s){
    return isfile_wrapper(s->data);
}


string *read_single_line_file(const char *path, bool keep_newline, bool syscall){
    
    // if(!isfile(path)) return NULL;
    FILE *f;
    f = syscall ? popen(path, "r") : fopen(path, "r");
    if(!f){
        // perror("Cannot open path");
        return NULL;
    }
    string *s = malloc(sizeof(string));
    new_string(s);
    int ch;
    if(!keep_newline){
        while((ch=fgetc(f))!=EOF && ch != '\n'){
            append_char(s, ch);
        }
    }else{
        while((ch=fgetc(f))!=EOF){
            append_char(s, ch); 
        }
    }
    fclose(f);
    return s;

}


//returns memory 
//has no error checking (for json strings)
string *create_simple_json_struct(const char *arg1, ...){
    va_list arg;
    string *s = malloc(sizeof(string));
    new_string(s);
    append_char(s, '{');
    bool round = false;
    for(va_start(arg, arg1); arg1 != NULL; arg1 = va_arg(arg, const char *)){
        if(!round) round= true;   
        else append_char(s, ',');
        
        concat(s, arg1);
    }
    append_char(s, '}');
    return s;
    

}

//for now only really returns a char*
void *itoa(unsigned int i){
    size_t len;
    len = i == 0 ? 0 : ceil(log10(i));
    char *mem = malloc(len == 0 ? 2 : len + 1);
    sprintf(mem, "%d", i);
    return mem;
}

const char *fmt_seg(string *s, unsigned long len){

}

void printl_c(const char *text, unsigned char begin, unsigned long end, bool ellipsis){
    for(size_t i = begin; i < end && *text != '\0'; ++i){
        printf("%c", text[i]);
    }
    if(ellipsis) printf("...");
}

void printl_s(string *text, unsigned char begin, unsigned long end, bool ellipsis){
    printl_c(text->data, begin, end, ellipsis);
}


string *cr_simple_json_struct(const char *j, ...)
{
    va_list list;
    string *js = malloc(sizeof(json));
    new_string(js);
    append_char(js, '{');
    bool round = false;
    bool name = false;
    for(va_start(list, j); j!=NULL; j=va_arg(list, const char*)){
        
        // if(!round) round= true;   
        if(name == false){
            if(!round) round = true;
            else append_char(js, ',');
            append_char(js,'"');
            concat(js,j);
            name = true;
            // concat(js, "\":\"");
            // concat(js,j->content);
            // append_char(js, '"');
        }else{
            concat(js, "\":\"");
            concat(js, j);
            append_char(js, '"');
            name = false;
            
        }
    }
    append_char(js, '}');
    if(name == true) fprintf(stderr, "Incomplete JSON struct\n");;
    return js;
}


string *create_simple_json_struct_i(const char *j, ...){
    
    va_list list;
    string *js = malloc(sizeof(json));
    new_string(js);
    append_char(js, '{');
    bool round = false;
    bool name = false;
    for(va_start(list, j); j!=NULL; j=va_arg(list, const char*)){
        
        // if(!round) round= true;   
        if(name == false){
            if(!round) round = true;
            else append_char(js, ',');
            append_char(js,'"');
            concat(js,j);
            name = true;
            // concat(js, "\":\"");
            // concat(js,j->content);
            // append_char(js, '"');
        }else{
            concat(js, "\": ");
            concat(js, j);
            // append_char(js, '"');
            name = false;
            
        }
    }
    append_char(js, '}');
    if(name == true) fprintf(stderr, "Incomplete JSON struct\n");;
    return js;
}
