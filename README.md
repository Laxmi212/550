Lexical Analyzer & Token Counter
1. Title

Lexical Analyzer & Token Counter using C

2. Objective

The objective of this project is to develop a lexical analyzer in C that reads a source-code file and identifies different types of tokens.

The program classifies tokens into:

Keywords
Identifiers
Operators
Constants
String Literals
Separators
Special Symbols
Comments

The program also counts the total number of tokens belonging to each category.

3. Problem Statement

Develop a C program that reads a source-code file and performs lexical analysis.

The program should scan the source code character by character and identify different types of tokens. It should recognize keywords, identifiers, operators, constants, string literals, separators, special symbols, and comments.

After lexical analysis, the program should display each identified token along with its token type and display the count of each token category.

4. Algorithm
Start the program.
Declare a list of C keywords.
Ask the user to enter the source-code filename.
Open the source file using fopen().
If the file cannot be opened, display an error message and terminate.
Read the source file character by character using fgetc().
Ignore whitespace characters.
Check for comments:
If // is found, skip characters until the end of the line.
If /* is found, skip characters until */.
Check whether the current character starts an identifier or keyword.
Read the complete word and compare it with the keyword list.
If the word is present in the keyword list, classify it as a Keyword.
Otherwise, classify it as an Identifier.
Check for numeric values and classify them as Constants.
Check for text enclosed in double quotes and classify it as a String Literal.
Check for characters enclosed in single quotes and classify them as Constants.
Check for operators such as +, -, *, /, =, <, > and multi-character operators such as ==, !=, >=, <=, ++, and --.
Check for separators such as (, ), {, }, [, ], ;, ,, and :.
Classify any remaining recognized characters as Special Symbols.
Increment the appropriate token counter.
Display all tokens and their types.
Display the total count of each token category.
Close the source file.
Stop the program.
5. Source Code

The complete source code is available in lexical.c.

The program uses standard C libraries:

#include <stdio.h>
#include <string.h>
#include <ctype.h>


The main functions used are:

isKeyword() — checks whether a word is a C keyword.
isSeparator() — checks whether a character is a separator.
isOperator() — checks whether a character is an operator.
main() — reads the source file, performs lexical analysis, and displays the results.
6. Sample Input

The sample source-code file sample.txt contains:

int sum = a + b;
float average = sum / 2.0;

// Calculate average
if (average > 50)
printf("Pass");

7. Sample Output
TOKEN TYPE
------------------------------------------------
int             Keyword
sum             Identifier
=               Operator
a               Identifier
+               Operator
b               Identifier
;               Separator
float           Keyword
average         Identifier
=               Operator
sum             Identifier
/               Operator
2.0             Constant
;               Separator
if              Keyword
(               Separator
average         Identifier
>               Operator
50              Constant
)               Separator
printf          Identifier
(               Separator
"Pass"          String Literal
)               Separator
;               Separator

------------------------------------------------
Token Count
Keywords       : 3
Identifiers    : 7
Operators      : 4
Constants      : 2
String Literals: 1
Separators     : 7
Special Symbols: 0
Comments       : 1


Note: The original assignment states Separators : 8, but the supplied sample input contains only 7 separators. Therefore, the correct separator count for this input is 7.

8. Token Classification
Token Type	Description	Examples
Keyword	Reserved words of the C language	int, float, if
Identifier	Names of variables, functions, etc.	sum, average, printf
Operator	Symbols used to perform operations	=, +, /, >
Constant	Numeric and character constant values	50, 2.0, 'A'
String Literal	Text enclosed within double quotes	"Pass"
Separator	Symbols used to separate program elements	;, (, ), {, }
Special Symbol	Symbols not classified into the other categories	Language-dependent symbols
Comment	Text ignored during lexical analysis	// comment, /* comment */
9. Test Cases
Test Case 1: Keywords and Identifiers

Input:

int number = 10;
float value = 20.5;


Expected classification:

int → Keyword
number → Identifier
= → Operator
10 → Constant
; → Separator
float → Keyword
value → Identifier
20.5 → Constant
Test Case 2: Arithmetic Operators

Input:

int result = a + b * c;


Expected classification:

int → Keyword
result, a, b, c → Identifiers
=, +, * → Operators
; → Separator
Test Case 3: Conditional Statement

Input:

if (average >= 50)
printf("Pass");


Expected classification:

if → Keyword
average, printf → Identifiers
>= → Operator
50 → Constant
"Pass" → String Literal
(, ), ; → Separators
Test Case 4: Comments

Input:

// Single-line comment
int x = 10;

/* Multi-line
   comment */
x++;


Expected behavior:

The program ignores both single-line and multi-line comments and increments the comment counter.

Test Case 5: Multiple Operators

Input:

x++;
y--;
a == b;
a != b;
a >= b;


Expected classification:

x, y, a, b → Identifiers
++, --, ==, !=, >= → Operators
; → Separators
10. Conclusion

The Lexical Analyzer & Token Counter successfully performs the lexical analysis phase of a compiler by reading source code from a file and identifying different types of tokens.

The program can recognize keywords, identifiers, operators, constants, string literals, separators, special symbols, and comments. It also maintains separate counters for each token category and displays the results clearly.

This project provides a basic understanding of how a compiler's lexical analyzer processes source code and converts it into meaningful tokens.
