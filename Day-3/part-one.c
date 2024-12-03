#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

char * read_file(char *filename){
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Could not open input.txt\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = malloc(fsize + 1);
    if (!str) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fread(str, 1, fsize, file);
    fclose(file);

    str[fsize] = '\0';
    return str;
}

int main() {
    char *str = read_file("input.txt");
    regex_t regex;
    int reti;
    char msgbuf[100];

    // Compile regular expression
    reti = regcomp(&regex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED);
    

    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    // Execute regular expression

    regmatch_t pmatch[1];
    const char *p = str;
    int res = 0;

    while ((reti = regexec(&regex, p, 1, pmatch, 0)) == 0) {
        // Extract the matched substring
        char match[pmatch[0].rm_eo - pmatch[0].rm_so + 1];
        snprintf(match, sizeof(match), "%.*s", (int)(pmatch[0].rm_eo - pmatch[0].rm_so), p + pmatch[0].rm_so);

        // Extract the numbers from the matched substring
        int x, y;
        sscanf(match, "mul(%d,%d)", &x, &y);

        // update res
        res += x * y;

        p += pmatch[0].rm_eo;
    }

    if (reti != REG_NOMATCH) {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }

    // Free compiled regular expression and string
    regfree(&regex);
    free(str);
    printf("Result: %d\n", res);
    exit(EXIT_SUCCESS);
}