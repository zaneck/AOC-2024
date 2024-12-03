#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

char *read_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Could not open input.txt\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = malloc(fsize + 1);
    if (!str)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fread(str, 1, fsize, file);
    fclose(file);

    str[fsize] = '\0';
    return str;
}

int mul_regex(char *p)
{
    int res = 0;
    regex_t regex;
    int reti = regcomp(&regex, "mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED);
    char msgbuf[100];
    regmatch_t pmatch[1];

    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    while ((reti = regexec(&regex, p, 1, pmatch, 0)) == 0)
    {
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
    if (reti != REG_NOMATCH)
    {
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(EXIT_FAILURE);
    }
    regfree(&regex);

    return res;
}

int doDont_regex(char *q)
{
    int reg_flag = 0;
    int res = 0;
    char msgbuf[100];
    regmatch_t pmatch[1];

    regex_t regex[2];
    int reti;

    // dont
    reti = regcomp(&regex[0], "don't\\(\\)", REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }
    // do
    reti = regcomp(&regex[1], "do\\(\\)", REG_EXTENDED);
    if (reti)
    {
        fprintf(stderr, "Could not compile regex\n");
        exit(EXIT_FAILURE);
    }

    while (regexec(&regex[reg_flag], q, 1, pmatch, 0) == 0)
    {
        char match[pmatch[0].rm_eo + 1];
        snprintf(match, sizeof(match), "%.*s", (int)(pmatch[0].rm_eo), q);
        if (reg_flag == 0)
        {
            res += mul_regex(match);
        }
        q += pmatch[0].rm_eo;
        reg_flag = (reg_flag + 1) % 2;
    }
    if (reg_flag == 0)
    {
        res += mul_regex(q);
    }
    regfree(&regex[0]);
    regfree(&regex[1]);
    return res;
}

int main()
{
    char *str = read_file("input.txt");
    int resOne = 0;
    int resTwo = 0;
    char *p = str;
    char *q = str;

    resOne = mul_regex(p);
    resTwo = doDont_regex(q);

    free(str);
    printf("Part one result: %d\n", resOne);
    printf("Part two result: %d\n", resTwo);
    exit(EXIT_SUCCESS);
}