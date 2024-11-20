#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#include "lexer.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

Token t;
LexicalAnalyzer lexer;

//A map for location mapping of variable name to the index where it is stored in the mem array
map<string, int> varMap;

//index in mem array
int indexInmem = 0;

struct InstructionNode* parse_generate_intermediate_representation();
struct InstructionNode* parse_program();
struct InstructionNode* parse_instr_list();
struct InstructionNode* parse_body();


/*
struct InstructionNode * parse_generate_intermediate_representation()
{

   
    // Sample program for demonstration purpose only
    // Replace the following with a parser that reads the program from stdin &
    // creates appropriate data structures to be executed by execute_program()
    // This is the imaginary input for the following construction:
    
    // a, b, c, d;
    // {
    //     input a;
    //     input b;
    //     c = 10;
    // 
    //     IF c <> a
    //     {
    //         output b;
    //     }
    // 
    //     IF c > 1
    //     {
    //         a = b + 900;
    //         input d;
    //         IF a > 10
    //         {
    //             output d;
    //         }
    //     }
    // 
    //     d = 0;
    //     WHILE d < 4
    //     {
    //         c = a + d;
    //         IF d > 1
    //         {
    //             output d;
    //         }
    //         d = d + 1;
    //     }
    // }
    // 1 2 3 4 5 6
    
    // Assigning location for variable "a"
    int address_a = next_available;
    mem[next_available] = 0;
    next_available++;

    // Assigning location for variable "b"
    int address_b = next_available;
    mem[next_available] = 0;
    next_available++;

    // Assigning location for variable "c"
    int address_c = next_available;
    mem[next_available] = 0;
    next_available++;

    // Assigning location for variable "d"
    int address_d = next_available;
    mem[next_available] = 0;
    next_available++;

    // Assigning location for constant 10
    int address_ten = next_available;
    mem[next_available] = 10;
    next_available++;

    // Assigning location for constant 1
    int address_one = next_available;
    mem[next_available] = 1;
    next_available++;

    // Assigning location for constant 900
    int address_ninehundred = next_available;
    mem[next_available] = 900;
    next_available++;

    // Assigning location for constant 3
    int address_three = next_available;
    mem[next_available] = 3;
    next_available++;

    // Assigning location for constant 0
    int address_zero = next_available;
    mem[next_available] = 0;
    next_available++;

    // Assigning location for constant 4
    int address_four = next_available;
    mem[next_available] = 4;
    next_available++;

    struct InstructionNode * i1 = new InstructionNode;
    struct InstructionNode * i2 = new InstructionNode;
    struct InstructionNode * i3 = new InstructionNode;
    struct InstructionNode * i4 = new InstructionNode;
    struct InstructionNode * i5 = new InstructionNode;
    struct InstructionNode * i6 = new InstructionNode;
    struct InstructionNode * i7 = new InstructionNode;
    struct InstructionNode * i8 = new InstructionNode;
    struct InstructionNode * i9 = new InstructionNode;
    struct InstructionNode * i10 = new InstructionNode;
    struct InstructionNode * i11 = new InstructionNode;
    struct InstructionNode * i12 = new InstructionNode;
    struct InstructionNode * i13 = new InstructionNode;
    struct InstructionNode * i14 = new InstructionNode;
    struct InstructionNode * i15 = new InstructionNode;
    struct InstructionNode * i16 = new InstructionNode;
    struct InstructionNode * i17 = new InstructionNode;
    struct InstructionNode * i18 = new InstructionNode;
    struct InstructionNode * i19 = new InstructionNode;
    struct InstructionNode * i20 = new InstructionNode;
    struct InstructionNode * i21 = new InstructionNode;
    struct InstructionNode * i22 = new InstructionNode;

    i1->type = IN;                                      // input a
    i1->input_inst.var_index = address_a;
    i1->next = i2;

    i2->type = IN;                                      // input b
    i2->input_inst.var_index = address_b;
    i2->next = i3;

    i3->type = ASSIGN;                                  // c = 10
    i3->assign_inst.left_hand_side_index = address_c;
    i3->assign_inst.op = OPERATOR_NONE;
    i3->assign_inst.operand1_index = address_ten;
    i3->next = i4;

    i4->type = CJMP;                                    // if c <> a
    i4->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    i4->cjmp_inst.operand1_index = address_c;
    i4->cjmp_inst.operand2_index = address_a;
    i4->cjmp_inst.target = i6;                          // if not (c <> a) skip forward to NOOP
    i4->next = i5;

    i5->type = OUT;                                     // output b
    i5->output_inst.var_index = address_b;
    i5->next = i6;

    i6->type = NOOP;                                    // NOOP after IF
    i6->next = i7;

    i7->type = CJMP;                                    // if c > 1
    i7->cjmp_inst.condition_op = CONDITION_GREATER;
    i7->cjmp_inst.operand1_index = address_c;
    i7->cjmp_inst.operand2_index = address_one;
    i7->cjmp_inst.target = i13;                         // if not (c > 1) skip forward to NOOP (way down)
    i7->next = i8;

    i8->type = ASSIGN;                                  // a = b + 900
    i8->assign_inst.left_hand_side_index = address_a;
    i8->assign_inst.op = OPERATOR_PLUS;
    i8->assign_inst.operand1_index = address_b;
    i8->assign_inst.operand2_index = address_ninehundred;
    i8->next = i9;

    i9->type = IN;                                      // input d
    i9->input_inst.var_index = address_d;
    i9->next = i10;

    i10->type = CJMP;                                   // if a > 10
    i10->cjmp_inst.condition_op = CONDITION_GREATER;
    i10->cjmp_inst.operand1_index = address_a;
    i10->cjmp_inst.operand2_index = address_ten;
    i10->cjmp_inst.target = i12;                        // if not (a > 10) skipp forward to NOOP
    i10->next = i11;

    i11->type = OUT;                                    // output d
    i11->output_inst.var_index = address_d;
    i11->next = i12;

    i12->type = NOOP;                                   // NOOP after inner IF
    i12->next = i13;

    i13->type = NOOP;                                   // NOOP after outer IF
    i13->next = i14;

    i14->type = ASSIGN;                                 // d = 0
    i14->assign_inst.left_hand_side_index = address_d;
    i14->assign_inst.op = OPERATOR_NONE;
    i14->assign_inst.operand1_index = address_zero;
    i14->next = i15;

    i15->type = CJMP;                                   // if d < 4
    i15->cjmp_inst.condition_op = CONDITION_LESS;
    i15->cjmp_inst.operand1_index = address_d;
    i15->cjmp_inst.operand2_index = address_four;
    i15->cjmp_inst.target = i22;                        // if not (d < 4) skip whole WHILE body
    i15->next = i16;

    i16->type = ASSIGN;                                 // c = a + d
    i16->assign_inst.left_hand_side_index = address_c;
    i16->assign_inst.op = OPERATOR_PLUS;
    i16->assign_inst.operand1_index = address_a;
    i16->assign_inst.operand2_index = address_d;
    i16->next = i17;

    i17->type = CJMP;                                   // if d > 1
    i17->cjmp_inst.condition_op = CONDITION_GREATER;
    i17->cjmp_inst.operand1_index = address_d;
    i17->cjmp_inst.operand2_index = address_one;
    i17->cjmp_inst.target = i19;                        // if not (d > 1) skip body of IF
    i17->next = i18;

    i18->type = OUT;                                    // output d
    i18->output_inst.var_index = address_d;
    i18->next = i19;

    i19->type = NOOP;                                   // NOOP after body of IF
    i19->next = i20;

    i20->type = ASSIGN;                                 // d = d + 1
    i20->assign_inst.left_hand_side_index = address_d;
    i20->assign_inst.op = OPERATOR_PLUS;
    i20->assign_inst.operand1_index = address_d;
    i20->assign_inst.operand2_index = address_one;
    i20->next = i21;

    i21->type = JMP;
    i21->jmp_inst.target = i15;
    i21->next = i22;

    i22->type = NOOP;                                   // NOOP after body of WHILE
    i22->next = NULL;

    // Inputs
    inputs.push_back(1);
    inputs.push_back(2);
    inputs.push_back(3);
    inputs.push_back(4);
    inputs.push_back(5);
    inputs.push_back(6);

    return i1;
}
*/

void syntax_error()
{
    cout << "Syntax Error" << endl;
    exit(1);
}

void error(string message)
{
    cout << "Error: " << message << endl;
    exit(1);
}


Token match(TokenType expected_type)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type) {
        syntax_error();
    }
    return t; 
}


InstructionNode* get_last(InstructionNode* list)
{
    while (list->next != NULL) 
        list = list->next;
    return list;
}

void parse_id_list()
{
    Token id, l;

    //a, b
    id = match(ID);  //get a

    //Add location and name of variable to map
    varMap[id.lexeme] = indexInmem;
    indexInmem++;

    //Get all comma separated variables
    while (lexer.peek(1).token_type == COMMA) {
        match(COMMA);

        //Get the var after the comma, eg. a, b
        id = match(ID);
        //Add location and name of variable to map
        varMap[id.lexeme] = indexInmem;
        indexInmem++;
    }
}

void parse_var_section()
{
    parse_id_list();
    match(SEMICOLON);
}

int atoi(string s)
{
    int i = 0;
    for (int n = 0; n < s.length(); n++) {
        i = i * 10;
        i += (s[n] - '0');
    }
    return i;
}


int get_operand_index() {
    Token t = lexer.GetToken();

    //if operand1 is a variable, it's index is already stored in mem
    if (t.token_type == ID) 
        return varMap[t.lexeme];

    //If operand1 is a number, store it in mem and return it's index
    if (t.token_type == NUM) {
        mem[indexInmem] = atoi(t.lexeme);
        indexInmem++;
        //return the index of the num operand 1
        return (indexInmem - 1);
        
    }
    
    cout << "Operand1 is not a ID or a number " << t.lexeme << endl;
    syntax_error();
    return -1;
}

bool is_op(TokenType type)
{
    return type == PLUS || type == MINUS || type == MULT || type == DIV;
}

ArithmeticOperatorType get_op(TokenType t) {
    if (t == PLUS) {
        return OPERATOR_PLUS;
    }
    if (t == MINUS) {
        return OPERATOR_MINUS;
    }
    if (t == DIV) {
        return OPERATOR_DIV;
    }
    if (t == MULT) {
        return OPERATOR_MULT;
    }
    return OPERATOR_NONE;
}

struct InstructionNode* parse_input() 
{
    Token t;
    InstructionNode* instr = new InstructionNode;
    instr->type = IN;

    //Check that it is an input instruction and move token index forward to the next token
    t = match(INPUT);

    //Get the variable
    t = match(ID);

    //Assign the index of the variable in mem to var_index of the input instruction
    instr->output_inst.var_index = varMap[t.lexeme];

    match(SEMICOLON);

    instr->next = NULL;

    return instr;

}

struct InstructionNode* parse_output()
{
    Token t;
    InstructionNode* instr = new InstructionNode;
    instr->type = OUT;

    //Check that it is an output instruction and move token index forward to the next token
    t = match(OUTPUT);

    //Get the variable
    t = match(ID);

    //Assign the index of the variable in mem to var_index of the output instruction
    instr->output_inst.var_index = varMap[t.lexeme];

    match(SEMICOLON);

    instr->next = NULL;
    
    return instr;
}


struct InstructionNode* parse_assign()
{
    Token t;
    InstructionNode* stmt = new InstructionNode;
    stmt->type = ASSIGN;

    //AssignmentStatement* st = new AssignmentStatement;
    //stmt->assign_stmt = st;

    Token left = match(ID);
    //st->left_hand_side = get_value_node(left.lexeme);

    //get the index where this variable is stored in the mem array
    //That index will be assigned to left_hand_side_index
    stmt->assign_inst.left_hand_side_index = varMap[left.lexeme];

    match(EQUAL);

    //Assign statement operand 1 is either a number or an ID
    //Get its index and assign it to the struct
    stmt->assign_inst.operand1_index = get_operand_index();

    //Now see whether the next token is an operator 
    t = lexer.peek(1);

    //If operation, then get the op type and the second operand
    //a = b + c; 
    if (is_op(t.token_type)) {
        Token opTok = match(t.token_type);
        stmt->assign_inst.op = get_op(opTok.token_type);
        stmt->assign_inst.operand2_index = get_operand_index();
    }
    else {
        //Not an operation, then it is a plain assign 
        stmt->assign_inst.op = OPERATOR_NONE;
        stmt->assign_inst.operand2_index = NULL;
    }

    //end of assign
    match(SEMICOLON);

    stmt->next = NULL;

    return stmt;
}

ConditionalOperatorType parse_condOp()
{
    Token t = lexer.GetToken();
    if (t.token_type == NOTEQUAL) {
        return CONDITION_NOTEQUAL;
    }
    else if (t.token_type == GREATER) {
        return CONDITION_GREATER;
    }
    else if (t.token_type == LESS) {
        return CONDITION_LESS;
    }
    else {
        syntax_error();
    }

}

InstructionNode* make_no_op()
{
    InstructionNode* no_op = new InstructionNode;
    no_op->next = NULL;
    no_op->type = NOOP;
    return no_op;
}

struct InstructionNode* parse_if_stmt() {

    InstructionNode* instr = new InstructionNode;
    instr->type = CJMP;

    match(IF);

    //eg. IF a > b
    instr->cjmp_inst.operand1_index = get_operand_index();
    instr->cjmp_inst.condition_op = parse_condOp();
    instr->cjmp_inst.operand2_index = get_operand_index();

    //Branch to next instructions in body if condition is true
    instr->next = parse_body();

    //Create no-op node
    InstructionNode* no_op = new InstructionNode;
    no_op->next = NULL;
    no_op->type = NOOP;

    //Get to the end of the body
    //Append the no-op to the body, so that it the if block ends up here after executing the body
    get_last(instr)->next = no_op;

    //Assign the false-branch to the no-op as well, so both true and false branches end up in the same place
    instr->cjmp_inst.target = no_op;

    return instr;

}

struct InstructionNode* parse_while_stmt() {

    InstructionNode* instr = new InstructionNode;
    instr->type = CJMP;

    match(WHILE);

    //eg. WHILE a > b
    instr->cjmp_inst.operand1_index = get_operand_index();
    instr->cjmp_inst.condition_op = parse_condOp();
    instr->cjmp_inst.operand2_index = get_operand_index();

    instr->next = parse_body();

    //Create jmp node of type JMP
    InstructionNode* instrJmp = new InstructionNode;
    instrJmp->type = JMP;

    //Set jmp target to inst
    instrJmp->jmp_inst.target = instr;

    //append jmp node to end of body of while
    get_last(instr)->next = instrJmp;

    //create no-op and attach it to the list of instructions after the jmp node
    InstructionNode* no_op = new InstructionNode;
    no_op->next = NULL;
    no_op->type = NOOP;

    instrJmp->next = no_op;

    //set instr target to point to no-op mode
    instr->cjmp_inst.target = no_op;

    return instr;


}

struct InstructionNode* parse_instr_list()
{
    InstructionNode* instr; // Instruction 
    InstructionNode* instrList; // Instruction list 

    Token t1, t2;
    t1 = lexer.peek(1);
    instr = new InstructionNode;

    //assign statement begins with ID
    //a = 1; a = b; a = b + 1; a = b + c; etc
    if (t1.token_type == ID) {
        instr = parse_assign();
    }
    else if (t1.token_type == OUTPUT) {
        instr = parse_output();
    }
    else if (t1.token_type == INPUT) {
        instr = parse_input();
    }
    else if (t1.token_type == IF) {
        instr = parse_if_stmt();
    }
    else if (t1.token_type == WHILE) {
        instr = parse_while_stmt();
    }
    /*
    else if (t1.token_type == PRINT) {
        st = parse_print_stmt();
    }
    

    else if (t1.token_type == SWITCH) {
        st = parse_switch_stmt();
    }
    else if (t1.token_type == FOR) {
        st = parse_for_stmt();
    } */
    else {
        syntax_error();
    }


    t2 = lexer.peek(1);
    if (t2.token_type != RBRACE) {
        instrList = parse_instr_list();
    }
    else {
        instrList = NULL;
    }

    get_last(instr)->next = instrList;

    return instr;
}

void parse_input_values() {

    Token t;

    //Move past the end RBRACE 
    //t = lexer.GetToken();

    //Get all the nums and push them into the inputs vector
    while (lexer.peek(1).token_type != END_OF_FILE)
    {
        t = lexer.GetToken();
        inputs.push_back(atoi(t.lexeme));
    }
   
}

struct InstructionNode* parse_body()
{
    struct InstructionNode* st1;

    match(LBRACE);
    st1 = parse_instr_list();
    match(RBRACE);

    return st1;
}

struct InstructionNode* parse_program()
{
    struct InstructionNode* n1 = NULL;

    parse_var_section(); // variables declared here
    
    n1 = parse_body(); 	// program code graph generated in here
     
    parse_input_values();

    return n1;
}


struct InstructionNode* parse_generate_intermediate_representation() {
    return parse_program();
}
    