#ifndef _LIBS_H
    #define _LIBS_H 1
    #include <stdbool.h>
    #define isdir(x) \
        _Generic((x), const char*: isdir_wrapper, string*: isdir_s) (x)
    
    #define isfile(x) \
        _Generic((x), char*:isfile_wrapper, const char*: isfile_wrapper, string*: isfile_s) (x)
    
    #define printl(x, begin, end) \
        _Generic((x), char*:printl_c, const char *:printl_c, string*:printl_s)(x)
    
    
    typedef struct{
        char *data;
        unsigned long length;
    
    } string;
    typedef struct{
        string **data;
        unsigned long lines;
    } filebuff;
    

    typedef struct{
        unsigned char begin;
        unsigned long end;
        string *ptr;
    } s_ptr;

    typedef struct{
        string *name;
        string *content;
    } str_json;

    typedef struct{
        char *name;
        char *content;
    }json;
    filebuff *fbuff(const char *filepath, bool syscall);
    void new_string(string *s);
    void append_char(string *s, const char chr);
    void concat(string *s, const char *s2);
    void free_string(string *s);
    void _free_string_arrmem(string **s, unsigned long len);
    char *trim(const char *s);
    void str_resb(string *s, unsigned long len);

    void free_fbuff(filebuff *fbuff);

    bool isdir_wrapper(const char *path);
    bool isdir_c(const char *path);
    bool isdir_s(string *s);
    
    bool isfile_wrapper(const char *path);
    bool isfile_s(string *s);

    string *read_single_line_file(const char *path, bool keep_newline, bool syscall);
    string *f_read_single_line_file(const char *path);

    void *itoa(unsigned int i);
    string *create_simple_json_struct(const char *arg1, ...);
    string *create_simple_json_struct_i(const char *j, ...);
    string *cr_simple_json_struct(const char *j, ...);
    const char *fmt_seg(string *s, unsigned long len); //doesn't return mem just a ptr
    

    //if the beginning index of the string is more than 128 characters? BOOM
    void printl_c
        (const char *text, unsigned char begin, unsigned long end, bool ellipsis);
    void printl_s(string *text, unsigned char begin, unsigned long end, bool ellipsis);
#endif
