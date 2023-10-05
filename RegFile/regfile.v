module regfile (
    clock,
    ctrl_writeEnable,
    ctrl_reset, ctrl_writeReg,
    ctrl_readRegA, ctrl_readRegB, data_writeReg,
    data_readRegA, data_readRegB
);

   input clock, ctrl_writeEnable, ctrl_reset;
   input [4:0] ctrl_writeReg, ctrl_readRegA, ctrl_readRegB;
   input [31:0] data_writeReg;

   output [31:0] data_readRegA, data_readRegB;
	
	//write data
	wire [31:0] write_reg, write_enable;
	wire [31:0] q [0:31];
	decoder w_decoder(ctrl_writeReg, write_reg);
	
	genvar i;
	generate
		for (i = 0; i < 32; i = i + 1) begin: write_data
			and w_a(write_enable[i], write_reg[i], ctrl_writeEnable);
		end
	endgenerate
	
	register r(32'b0, 1'b0, clock, ctrl_reset, q[0]);
		
	generate
		for (i = 1; i < 32; i = i + 1) begin: regs_32
			register r(data_writeReg, write_enable[i], clock, ctrl_reset, q[i]);
		end
	endgenerate
	
	
	//read data
	wire [31:0] read_enableA;
	wire [31:0] read_enableB;
	
	decoder r_decoderA(ctrl_readRegA, read_enableA);
	decoder r_decoderB(ctrl_readRegB, read_enableB);
	
	//Register 0 is always read as 0
	tristate_buffer tb_0a(q[0], read_enableA[0], data_readRegA);
	tristate_buffer tb_0b(q[0], read_enableB[0], data_readRegB);
	
	genvar j;
	generate
		for (j = 1; j < 32; j = j + 1) begin: buffer_AB
			tristate_buffer tb_A(q[j], read_enableA[j], data_readRegA);
			tristate_buffer tb_B(q[j], read_enableB[j], data_readRegB);
		end
	endgenerate
endmodule
