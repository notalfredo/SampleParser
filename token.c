/*This code is not mine  the follwing code 
can be found in the following book

Programming Languages Principles and practice
Kenneth C. Louden & Kenneth A. Lambert

*/
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int token; /*holds the current input character for the parse*/

/*decloration to allow arbitrary recursion*/
void command();
int expr();
int term();
int factor();
int number();
int digit();


void error(char* message){
    printf("parse error :  %s\n", message);
    exit(1);
}

void getToken(){
    /*Tokens are characters*/
    token = getchar();
}

void match(char c, char* message){
    if (token == c){
        getToken();
    }
    else error(message);
}

void command(){
    /* command -> expr*/
    int result = expr();
    if (token == '\n'){ 
        printf("the result is : %d\n", result);
    }
    else error("tokens after end of expressoin");
}

int expr(){
    /*expr -> term ( '+' term)*/
    int result = term();
    while (token == '+')
    {
        match('+' , "+ expectred");
        result += term();
    }
    return result;
}

int term(){
    /*term -> factor { '*' factor}*/
    int result = factor();
    while(token == '*')
    {
        match('*', "* expectred");
        result *= factor();
    }
    return result;
}

int factor(){
    /*factor -> '(' expr ')' | number*/
    int result;
    if (token == '(')
    {
        match('(', "( expectred");
        result = expr();
        match (')' , ") expectred");
    }
    else{
        result = number();
    }
    return result;
}

int number(){
    /*number -> digit {digit}*/
    int result = digit();
    while(isdigit(token))
    {
        /*The value of a number with a new trailing digit
        is its previouse value shifted by a decimal place
        plus the valiue of the new digit*/
        result = 10 * result + digit();
    }
    return result;
}

int digit(){
    /*digit -> '0' | '1' | ... '9'*/
    int result;
    if (isdigit(token))
    {
        /*The numeric value of a digit character is 
        the difference between its ascii value and the
        asci value of the character '0'*/
        result = token - '0';
        match(token, "( expectred");
    }
    else{
        error("digit expectred");
    }
    return result;
}

void parse(){
    getToken();
    command();
}



int main()
{
    parse();
    return 0;   
}