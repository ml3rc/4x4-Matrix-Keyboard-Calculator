/*
 * main.c
 *
 * Created: 4/27/2026 8:57:54 AM
 *  Author: maell
 */

/* Include Files */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <util/delay.h>
#include "lib/keyboard_lib/matrix_keyboard.h"
#include "lib/lcd_lib/HD44780.h"

/* Define */
#define LOOP_DELAY_MS 1

/* Enumerations */
enum State {
    STATE_CLEAR,
    STATE_OPERAND_1,
    STATE_OPERAND_2,
    STATE_OPERATOR,
};


/* Main Function */
int main(void) {
    KB_Init();
    DISP_InitPins();
    DISP_InitDisplay();
    DISP_ClearDisplay();

    enum State state = STATE_CLEAR;

    float_t op1 = 0;
    float_t op2 = 0;
    float_t result = 0;
    char op = 0;
    char buffer[16];

    while (1) {
        //read keyboard state
        char key = KB_UpdateKeyboard();

        switch (state) {
            // clear display and reset all variables
            case STATE_CLEAR:
                DISP_ClearDisplay();

                op1 = 0;
                op2 = 0;
                op = 0;
                result = 0;

                state = STATE_OPERAND_1;
                break;
            
            // input of the first operand and the operator
            case STATE_OPERAND_1:
                // Key handling
                switch (key) {
                    //digit keys
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        op1 = op1 * 10 + (key - '0'); //recalculate operand 1 with new digit
                        DISP_PrintChar(key); // Print the new digit
                        break;

                    // operator keys
                    case '+': case '-': case '*': case '/':
                        // Print operator
                        DISP_PrintChar(key);

                        op = key;
                        state = STATE_OPERAND_2;
                        break;

                    // clear key
                    case 'C':
                        state = STATE_CLEAR;
                        break;
                }

                break;
            
            // Wait for the operator input, this state is used to do a calculation with the result of the previous calculation
            case STATE_OPERATOR:
                // Key handling
                switch (key) {
                    // operator keys
                    case '+': case '-': case '*': case '/':
                        // Print operator
                        DISP_PrintChar(key);

                        op = key;
                        state = STATE_OPERAND_2;
                        break;

                    // clear key
                    case 'C':
                        state = STATE_CLEAR;
                        break;
                }

                break;
            
            // input of the second operand and calculation
            case STATE_OPERAND_2:
                // Key handling                
                switch (key) {
                    //digit keys
                    case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9':
                        op2 = op2 * 10 + (key - '0'); //recalculate operand 2 with new digit
                        DISP_PrintChar(key); // Print the new digit
                        break;

                    // calculation key
                    case '=':
                        // Perform calculation and transition to STATE_WAIT
                        switch (op) {
                            case '+': result = (float_t)(op1 + op2); break;
                            case '-': result = (float_t)(op1 - op2); break;
                            case '*': result = (float_t)(op1 * op2); break;
                            case '/': result = (op2 != 0) ? ((float_t)op1 / (float_t)op2) : 0; break;
                        }
                        DISP_ClearDisplay();
                        sprintf(buffer, "%f", result);
                        DISP_PrintString(buffer); // Print the new digit
                        
                        // Soft Reset for next calculation
                        op2 = 0;
                        op1 = result; // Use the result as the first operand for the next calculation

                        state = STATE_OPERATOR;
                        break;

                    // clear key
                    case 'C':
                        state = STATE_CLEAR;
                        break;
                }

                break;
        }
        
        //loop delay
        _delay_ms(LOOP_DELAY_MS);
    }
}