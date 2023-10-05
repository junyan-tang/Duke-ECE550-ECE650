# Register File
Author: &nbsp; Junyan Tang

NetID: &nbsp; jt418

Implementation of register file using Verilog. This module supports two read ports and one write port while being composed of 32 registers(32-bit wide each). Register 0 must always be read as 0(no matter what is written to it).

- `dffe.v`:
Rising-Edge D Flip-Flop. Transfers value on its D input to its Q output when an active edge transition occurs on its clock input. The Q output will be held until the next clock cycle. 
- `register.v`: 
32-bit register composed of 32 D Flip-Flops. Holds 32-bit number until the next clock cycle.
- `decoder.v`: 
5-to-32 binary decoder. Performs transition from 5-bit register address to one-hot output.
- `tristate_buffer.v`: 
Tri-state buffers. When select is 0, it outputs 32'bz which means it is disconnected from the output bus. When select is 1, its output is the same with the 32-bit input.
- `regfile.v`: 
Register File(Top-Level Entity). It consists of three decoders, one is for readRegA, one is for readRegB and the other is for writeReg. The output of these decoders will decide which register to read/write from 32 registers. Each Q value of 32 registers is connected to 2 tri-state buffers for being read as data_readRegA or data_readRegB.
- `regfile_tb.v`: 
Testbench file. Compares generated results with expected results.
