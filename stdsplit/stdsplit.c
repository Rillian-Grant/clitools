#include <getopt.h>
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <regex>\n", argv[0]);
        fprintf(stderr, "\nDiverts any matching lines to standard error.\n");
        exit(EXIT_FAILURE);
    }

    char *regex = argv[1];
    // Compile the regex
    regex_t compiled_regex;
    int ret = regcomp(&compiled_regex, regex, REG_EXTENDED);
    if (ret != 0) {
        perror("Error compiling regex\n");
        exit(EXIT_FAILURE);
    }
    
    char *line;
    size_t line_len;
    ssize_t read, written;
    while ((read = getline(&line, &line_len, stdin)) != -1) {
        // Match the line
        regmatch_t match;
        FILE *out;
        ret = regexec(&compiled_regex, line, 1, &match, 0);
        if (!ret) out = stderr;
        else if (ret == REG_NOMATCH) out = stdout;
        else {
            //regerror(ret, &compiled_regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", line);
            exit(1);
        }
        
        if (written = fwrite(line, sizeof(char), read, out) == -1) {
            perror("fwrite");
            exit(EXIT_FAILURE);
        }
    }
    
    free(line);
}
