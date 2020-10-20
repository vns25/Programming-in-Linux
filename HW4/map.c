#include <stdio.h>
#include <string.h>

void printLine(int num) {
    for(int i=0; i<num; i++) {
        printf("\t+------+------+------+------+\n");
    }
}

int main(int argc, char *argv[])
{
    int mask = 0xFF;

    printf("\n\t+------+------+------+------+ FFFFFFFF\n");
    printLine(3); 

    int charC=0; 
    for(int i=0; i<argc; i++) {
        charC += (strlen(argv[i]) + 1); 
    }

    int rem = charC % 4;
    int q= charC / 4; 
    int box = 4-rem; 
    int lines; 
    
    if( rem == 0 ) {
        lines = q; 
    }
    else {
        lines = q + 1; 
    }

    int memAddr[lines]; 
    int addr0 = (int)*(argv); 
    int mem=0; 
    for(int i=0; i<lines ; i++) {
        memAddr[i] = addr0+mem;  
        mem+=4; 
    }

    for(int i=0; i<box; i++){
        if(i == 0) {
            printf("\t"); 
        }
           
        printf("|      "); 
    }

    int lineC = lines-1; 
    for (int i = argc-1; i>=0; i--)
    {   
        int len = strlen( *( argv + i)) ; 
        for( int j = len; j>=0; j--){
            char c = *( *(argv+i) + j); 
            
            if(box<4) {
                if( c != '\0' ) {
                    printf("| %x(%c)", c, c); 
                }
                else if (c == '\0'){
                    printf("|%02x(%s)", c, "\\0" ); 
                }
                box++; 
            }
            else {
                box=0; 
                if( c != '\0' ) {
                     printf("| %08x\n\t+------+------+------+------+\n\t| %x(%c)",memAddr[lineC],c, c); 
                }
                else if (c == '\0'){
                     printf("|\n\t+------+------+------+------+\n\t|%02x(%s)",memAddr[lineC], "\\0"); 
                } 
                box++; 
                lineC--; 
            }
        }  
    } 
    printf("| %08x\n", addr0); 
    printLine(4); 

    int nullArg = (int)argv[argc]; 
    printf("\t|  %02x  |  %02x  |  %02x  |  %02x  | %x \n", nullArg >>24, nullArg>>16, nullArg>>8 & mask, nullArg>>0 & mask, (int)&argv[argc] ); 
    printLine(1); 

     for (int arg = argc-1; arg >= 0; arg--)
    {
        int add = (int)*(argv+arg); 
        printf("argv+%d  |  %02x  |  %02x  |  %02x  |  %02x  | %x \n", arg, add >>24 & mask, add>>16 & mask, add>>8 & mask, add>>0 & mask, (int)&argv[arg] ); 
        printf("\t+------+------+------+------+\n"); 
    }
    
    int c = (int)argc; 
    int v = (int)argv; 

    printLine(3); 
    printf("argc    |  %02x  |  %02x  |  %02x  |  %02x  | %x \n", c>>24 & mask, c>>16 & mask,c>>8 & mask,c>>0 & mask, (int)&argc);
    printf("\t+------+------+------+------+\n");
    printf("argv    |  %02x  |  %02x  |  %02x  |  %02x  | %x \n", v>>24 & mask, v>>16 & mask,v>>8 & mask, v>>0 & mask, (int)&argv);
    printLine(3); 
    printf("\t+------+------+------+------+ 00000000 \n");
    return 0; 

}
