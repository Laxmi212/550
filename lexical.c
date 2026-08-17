#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN 100

/* List of keywords */
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(keywords[0]))

/* Check whether a word is a keyword */
int isKeyword(char *word) {
    int i;

    for (i = 0; i < KEYWORD_COUNT; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

/* Check whether character is a separator */
int isSeparator(char ch) {
    return (ch == '(' || ch == ')' ||
            ch == '{' || ch == '}' ||
            ch == '[' || ch == ']' ||
            ch == ';' || ch == ',' ||
            ch == ':' );
}

/* Check whether character is an operator */
int isOperator(char ch) {
    return (ch == '+' || ch == '-' ||
            ch == '*' || ch == '/' ||
            ch == '%' || ch == '=' ||
            ch == '<' || ch == '>' ||
            ch == '!' || ch == '&' ||
            ch == '|' || ch == '^');
}

int main() {
    FILE *fp;
    char filename[100];
    char ch, next;
    char token[MAX_TOKEN];
    int i;

    int keywordsCount = 0;
    int identifiersCount = 0;
    int operatorsCount = 0;
    int constantsCount = 0;
    int stringLiteralsCount = 0;
    int separatorsCount = 0;
    int specialSymbolsCount = 0;
    int commentsCount = 0;

    printf("Enter source file name: ");
    scanf("%99s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    printf("\nTOKEN TYPE\n");
    printf("------------------------------------------------\n");

    while ((ch = fgetc(fp)) != EOF) {

        /* Ignore white spaces */
        if (isspace(ch))
            continue;

        /* Handle comments and division operator */
        if (ch == '/') {
            next = fgetc(fp);

            /* Single-line comment */
            if (next == '/') {
                commentsCount++;

                while ((ch = fgetc(fp)) != EOF && ch != '\n')
                    ;

                continue;
            }

            /* Multi-line comment */
            if (next == '*') {
                commentsCount++;

                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '*') {
                        next = fgetc(fp);

                        if (next == '/')
                            break;

                        ungetc(next, fp);
                    }
                }

                continue;
            }

            /* Division operator */
            ungetc(next, fp);
            printf("%-15s Operator\n", "/");
            operatorsCount++;
            continue;
        }

        /* Identifier or keyword */
        if (isalpha(ch) || ch == '_') {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isalnum(ch) || ch == '_')) {
                if (i < MAX_TOKEN - 1)
                    token[i++] = ch;
            }

            token[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(token)) {
                printf("%-15s Keyword\n", token);
                keywordsCount++;
            } else {
                printf("%-15s Identifier\n", token);
                identifiersCount++;
            }

            continue;
        }

        /* Numeric constant */
        if (isdigit(ch)) {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                   (isdigit(ch) || ch == '.')) {
                if (i < MAX_TOKEN - 1)
                    token[i++] = ch;
            }

            token[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            printf("%-15s Constant\n", token);
            constantsCount++;

            continue;
        }

        /* String literal */
        if (ch == '"') {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF) {
                if (i < MAX_TOKEN - 1)
                    token[i++] = ch;

                if (ch == '"')
                    break;
            }

            token[i] = '\0';

            printf("%-15s String Literal\n", token);
            stringLiteralsCount++;

            continue;
        }

        /* Character constant */
        if (ch == '\'') {
            i = 0;
            token[i++] = ch;

            while ((ch = fgetc(fp)) != EOF) {
                if (i < MAX_TOKEN - 1)
                    token[i++] = ch;

                if (ch == '\'')
                    break;
            }

            token[i] = '\0';

            printf("%-15s Constant\n", token);
            constantsCount++;

            continue;
        }

        /* Operators */
        if (isOperator(ch)) {
            char op[3];

            op[0] = ch;
            op[1] = '\0';

            next = fgetc(fp);

            /* Check two-character operators */
            if ((ch == '=' && next == '=') ||
                (ch == '!' && next == '=') ||
                (ch == '<' && (next == '=' || next == '<')) ||
                (ch == '>' && (next == '=' || next == '>')) ||
                (ch == '+' && (next == '+' || next == '=')) ||
                (ch == '-' && (next == '-' || next == '=')) ||
                (ch == '*' && next == '=') ||
                (ch == '%' && next == '=') ||
                (ch == '&' && next == '&') ||
                (ch == '|' && next == '|')) {

                op[1] = next;
                op[2] = '\0';
            } else {
                if (next != EOF)
                    ungetc(next, fp);
            }

            printf("%-15s Operator\n", op);
            operatorsCount++;

            continue;
        }

        /* Separators */
        if (isSeparator(ch)) {
            printf("%-15c Separator\n", ch);
            separatorsCount++;
            continue;
        }

        /* Special symbols */
        printf("%-15c Special Symbol\n", ch);
        specialSymbolsCount++;
    }

    fclose(fp);

    printf("\n------------------------------------------------\n");
    printf("Token Count\n");
    printf("Keywords       : %d\n", keywordsCount);
    printf("Identifiers    : %d\n", identifiersCount);
    printf("Operators      : %d\n", operatorsCount);
    printf("Constants      : %d\n", constantsCount);
    printf("String Literals: %d\n", stringLiteralsCount);
    printf("Separators     : %d\n", separatorsCount);
    printf("Special Symbols: %d\n", specialSymbolsCount);
    printf("Comments       : %d\n", commentsCount);

    return 0;
}
