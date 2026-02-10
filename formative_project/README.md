# QUESTION 1- C Program Lifecycle

a. An operating system is a real-world example of C programming. For example, the Linux operating system is built mostly with C, and C is fast and efficient while giving access to the hardware making it really good for system programming and embedded systems like the traffic lights system.

b. A syntax error is what happens when the code breaks the rule of the langauge, e.g, when a semicolon is omitted at the end of a code line and it doesn't run, while a Semantic error is what happens when the code is written well but without a proper logic, e.g, diving by the wrong number.

c. There are 4 stages that happens when a C program is compiled:
   1. Preprocessing: This is where all preprocessor directives like #include are handled, the comments get removed and the header files are expanded.
   2. Compilation: This stage checks the C code for syntax errors, then translate it into assembly langauge.
   3. Assembly: The assembly code translates it into machine langauge, and the output is an object file.
   4. Linking: In this stage, the linker combines the object file with necessary libraries and produce the final executable file that can be run.

# QUESTION 2- Control flow & Repetition

SAMPLE INPUT/OUTPUT

(SIMPLE CALCULATOR MENU)
1. Add two numbers
2. Subtract two numbers
3. Multiply two numbers
4. Exit
Enter your choice: 1
Enter first number: 5
Enter second number: 3
Result: 8.00

(SIMPLE CALCULATOR MENU)
1. Add two numbers
2. Subtract two numbers
3. Multiply two numbers
4. Exit
Enter your choice: 4
Exiting program...

PROGRAM LOGIC;

This program implements a simple menu-driven calculator. It uses a while loop to repeatedly display the menu until the user chooses to exit.

The user selects an option by entering a number. Than a switch statement is used to perform the selected operation (addition, subtraction, or multiplication).

If the user enters an invalid option, an if statement detects it and the continue statement restarts the loop. When the user selects option 4, the break statement terminates the loop and ends the program.


# QUESTION 3- Functions & Recursions

Advantages of Recursion:

1. Recursion simplifies problems that have a repeatitive or nested structure, e.g, factorials.
2. In recursion, the codes are usually shorter and easy to read.
3. Each recursive call handles a smaller piece of the given problem.

Limitations of Recursion:

1. Recursive calls use stack memory which can cause a stack overflow when too many calls are made.
2. Sometimes, recursion can be slower than iterative due to function call overhead.
3. Debugging recursion can be trickier for beginners.

# QUESTION 4- Embedded Systems

Block Circuit Diagram;

+-------------------+      +-------------------+      +-------------------+
|   TMP36 Sensor    | ---> |   Arduino Uno     | ---> |       LED         |
|   (Temperature)   |      |   (Controller)    |      |   (Actuator)      |
+-------------------+      +-------------------+      +-------------------+

Sensor → Controller → Actuator

Pseudocope;

START
Initialize sensor and LED pin
Start serial communication

LOOP:
    Read temperature sensor value
    Convert to Celsius
    IF temperature > 30°C
        Turn LED ON
    ELSE
        Turn LED OFF
    Wait 500 ms
END LOOP


Short explaination:

This system uses a TMP36 temperature sensor to measure ambient temperature. The Arduino reads the analog voltage from the sensor and converts it into degrees Celsius. If the temperature exceeds 30°C, the Arduino activates an LED as a warning indicator. Otherwise, the LED remains off. The system demonstrates the data flow from sensor to controller to actuator.

# QUESTION 5- Integration

Control flow determines how a system react to different conditions and events, ensuring the program executes the operation in correct order while the Function breaks the program into reusable blocks of code so it could be easy to manage, maintain and debug. On the otherhand, the Embedded system uses sensors, controllers and actuators to interact with the physical world, as it collects data to which the controller procceses, and the actuator performs actions based on the logic defined by control flow and actions.

For example,in a temperature-controlled fan system, the sensor reads the temperature, a function calculates if the fan should turn on, and control flow decides the function of the actuator.
