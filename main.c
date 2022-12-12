#include <stdio.h>


#define BUFSIZE 4096

char dataStream[BUFSIZE];
int charCounters[26];
int main()
{
    FILE *pf = stdin;

    #ifndef DEBUG
        pf = fopen("input.txt", "r");
        if(!pf){
            fprintf(stderr, "Can't open input.txt\n");
            return 1;
        }
    #endif

    fgets(dataStream, sizeof(dataStream), pf);
    fclose(pf);

    int uniqueChars = 0;
    int windowFront = 0;
    int windowRear = 0;
    int count, charIndex;
    for(; windowFront < 14; windowFront++){
        charIndex = dataStream[windowFront]-'a';
        count = charCounters[charIndex];
        if(count == 0){
            uniqueChars++;
        }
        charCounters[charIndex] = count+1;
    }

    for(;uniqueChars < 14; windowFront++, windowRear++)
    {
        //pop rear
        charIndex = dataStream[windowRear]-'a';
        count = charCounters[charIndex];
        if(count == 1){
            uniqueChars--;
        }
        charCounters[charIndex] = count-1;

        //push front
        charIndex = dataStream[windowFront]-'a';
        count = charCounters[charIndex];
        if(count == 0){
            uniqueChars++;
        }
        charCounters[charIndex] = count+1;
    }

    printf("%d\n", windowFront);
}

