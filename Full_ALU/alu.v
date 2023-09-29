module alu(data_operandA, data_operandB, ctrl_ALUopcode, ctrl_shiftamt, data_result, isNotEqual, isLessThan, overflow);

   input [31:0] data_operandA, data_operandB;
   input [4:0] ctrl_ALUopcode, ctrl_shiftamt;

   output [31:0] data_result;
   output isNotEqual, isLessThan, overflow;

   // YOUR CODE HERE //
	wire cout_add,cout_sub;
	wire overflow_add, overflow_sub;
	wire [31:0] cor, result_add, result_sub, result_and, result_or, result_sll, result_sra;
	wire [31:0] stage1_res1, stage1_res2, stage1_res3, stage2_res1;
	wire cond_l1, cond_l2, cond_l3;
	
	//addtion
	add_sub addition(data_operandA, data_operandB, 1'b0, result_add, cout_add, overflow_add);
	
	//subtraction
	add_sub subtraction(data_operandA, data_operandB, 1'b1, result_sub, cout_sub, overflow_sub);
	
	mux m_as_o(overflow_add, overflow_sub, ctrl_ALUopcode[0], overflow);
	
	//isNotEqual
	assign cor[0] = 0;
	genvar i;
	generate
		for( i = 0; i < 31; i = i + 1) begin: equal_eval
			or(cor[i + 1], result_sub[i], cor[i]);
		end
	endgenerate
	
	or(isNotEqual, result_sub[31], cor[31]);
	
	//isLessThan
	and(cond_l1, ~data_operandA[31], ~data_operandB[31], ~overflow_sub, result_sub[31]);
	and(cond_l2, data_operandA[31], data_operandB[31], ~overflow_sub, result_sub[31]);
	and(cond_l3, data_operandA[31], ~data_operandB[31]);
	or(isLessThan, cond_l1, cond_l2, cond_l3);
	
	
	//and
	and_logic and_op(data_operandA, data_operandB, result_and);
	
	//or
	or_logic or_op(data_operandA, data_operandB, result_or);
	
	//sll
	SLL sll(data_operandA, ctrl_shiftamt, result_sll);
	
	//sra
	SRA sra(data_operandA, ctrl_shiftamt, result_sra);
	
	//choose unit
	mux_32 m1_s1(result_add, result_sub, ctrl_ALUopcode[0], stage1_res1);
	mux_32 m2_s1(result_and, result_or, ctrl_ALUopcode[0], stage1_res2);
	mux_32 m3_s1(result_sll, result_sra, ctrl_ALUopcode[0], stage1_res3);
	
	mux_32 m1_s2(stage1_res1, stage1_res2, ctrl_ALUopcode[1], stage2_res1);
	
	mux_32 m1_s3(stage2_res1, stage1_res3, ctrl_ALUopcode[2], data_result);

endmodule
