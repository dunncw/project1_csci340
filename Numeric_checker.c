#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

bool check(char *string){
    char *end;
    
    strtol(*string, &end, 10);

    if(*end != '\0' || end == numbers) 
        return 0;
    else 
        return 1;


    return 0;
}
