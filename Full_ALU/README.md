# Full ALU
Author: &nbsp; Junyan Tang

NetID: &nbsp; jt418

Implementation of Arithmetic Logic Unit totally using structural verilog. Functions of this design include addition & subtraction, bitwise AND & OR and 32-bit barrel shifter(logical left-shift & arithmetic right-shift). After a SUBTRACT operation, ALU outputs the numerical relationship between data_operandA and data_operandB.

- `half_adder.v`:
Half adder. Performs binary addition of two single-bit binary numbers. It has two inputs, a and b, and two outputs, sum and cout.
- `full_adder.v`: 
Full adder. Performs binary addition of three inputs. The first two inputs are single-bit binary numbers, a and b. The third input is input carry, cin. It has two outputs, sum and cout.
- `mux.v`: 
Multiplexer. Includes three modules, implementing 1-bit, 16-bit, 32-bit multiplexers respectively.
- `RCA_16bits.v`: 
Ripple-Carry Adder. Performs binary addition of two 16-bit binary numbers using 16 full adders.
- `CSA_32bits.v`: 
Carry Select Adder. Performs binary addition of two 32-bit binary numbers using three 16-bit RCAs.
- `add_sub.v`: 
Addition and Subtraction. Performs addition or subtraction of two 32-bit signed binary numbers. It has three inputs, a, b, and aors which chooses addition or subtraction. It has three outputs, sum, cout and overflow.
- `and_logic.v`: 
Logical AND. Performs bitwise AND.
- `or_logic.v`: 
Logical OR. Performs bitwise OR. 
- `SLL.v`: 
Logical left-shift. Performs left-shift based on shift amount.
- `SRA.v`:
Arithmetic right-shift. Performs right-shift based on shift amount.
- `alu.v`:
Arithmetic Logic Unit. Combines all functions in this module. The outputs are determined based on ALU operation code.
- `alu_tb.v`:
Testbench file. Compares generated results with expected results.
