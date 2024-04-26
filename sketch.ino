#include <LiquidCrystal.h>
#include <Keypad.h>

// Define LCD connections (16x2 LCD in 4-bit mode)
LiquidCrystal lcd(14, 13, 12, 27, 26, 25); // RS, E, D4, D5, D6, D7

// Define keypad layout (4x4 matrix)
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

// Keypad GPIO connections
byte rowPins[ROWS] = {21, 19, 18, 5}; // Row pin connections
byte colPins[COLS] = {23, 22, 2, 4}; // Column pin connections

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = ""; // User input as a string
char lastOperation = '\0'; // Last operation
float result = 0; // Current result

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Initialize LCD (16x2 size)
  lcd.print("Simple Calculator"); // Start with a greeting

  delay(2000); // Pause to read
  lcd.clear(); // Clear LCD for further use
}

void loop() {
  char key = keypad.getKey(); // Get keypress from the keypad
  
  if (key) { // If a key is pressed
    if (key == 'C') { // Clear/reset calculator
      resetCalculator(); // Clear LCD and reset state
    } else if (key == '=') { // Calculate result
      calculateResult(); // Perform operation and display result
    } else if (isOperator(key)) { // If operator key is pressed
      handleOperator(key); // Handle operator and display
    } else { // If numeric key is pressed
      input += key; // Append to input string
      lcd.clear(); // Clear LCD before display
      lcd.setCursor(0, 1); // Set cursor to the second line
      lcd.print(input); // Display the current input
      Serial.println(input);
    }
  }
}

bool isOperator(char key) {
  return key == '+' || key == '-' || key == '*' || key == '/';
}

void handleOperator(char oper) {
  if (input.length() > 0) { // If there's input
    float operand = input.toFloat(); // Convert to float
    if (lastOperation == '\0') { // If no prior operation
      result = operand; // Set initial result
    } else { // If there was a previous operation
      result = performOperation(result, lastOperation, operand); // Perform operation
    }
    
    // Update last operation and reset input
    lastOperation = oper;
    input = "";
    
    // Clear LCD, then display result and operation
    lcd.clear(); // Clear the LCD
    lcd.print(result); // Display the current result
    Serial.println(result);
    lcd.setCursor(1, 0); // Move cursor for operator display
    lcd.print(oper); // Show current operator
    Serial.println(oper);
  }
}

void calculateResult() {
  if (input.length() > 0) { // If there's input
    float operand = input.toFloat(); // Convert input to float
    result = performOperation(result, lastOperation, operand); // Perform operation
    
    // Clear input and reset last operation
    input = "";
    lastOperation = '\0';
    
    // Clear LCD and display final result
    lcd.clear();
    lcd.print(result); // Display the result
    Serial.println(result);
  }
}

float performOperation(float a, char op, float b) {
  switch (op) {
    case '+': return a + b; // Addition
    case '-': return a - b; // Subtraction
    case '*': return a * b; // Multiplication
    case '/': 
      if (b == 0) {
        lcd.clear(); // Clear LCD for error message
        lcd.print("Error: Div by 0"); // Handle division by zero
        Serial.println("Error: Div by 0");
        delay(2000); // Pause to allow reading
        lcd.clear(); // Clear LCD after a delay
        return 0; // Default return value on error
      }
      return a / b; // Division
  }
  return b; // Default return
}

void resetCalculator() {
  // Reset calculator state and clear LCD
  input = "";
  lastOperation = '\0';
  result = 0;
  
  lcd.clear(); // Clear the LCD
  lcd.print("Cleared"); // Indicate calculator reset
  Serial.println("Cleared");
  delay(1000); // Delay to read "Cleared"
  lcd.clear(); // Clear LCD after delay for new operations
}