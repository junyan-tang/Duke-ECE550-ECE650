module add_sub(a, b, aors, sum, cout, overflow);
	input [31:0] a, b;
	input aors;
	output [31:0] sum;
	output cout, overflow;
	
	wire [31:0] not_b, input_b;
	wire ab_s, s_ab, nota, notb, not_s, ch_b;
	
	genvar i;
	generate for (i = 0; i < 32; i = i + 1)begin: not_loop
		not(not_b[i], b[i]);
	end
	endgenerate
	
	mux_16 m16_1(b[15:0], not_b[15:0], aors, input_b[15:0]);
	mux_16 m16_2(b[31:16], not_b[31:16], aors, input_b[31:16]);
	
	CSA_32bits csa1(a, input_b, aors, sum, cout);
	
	not(not_s, sum[31]);
	not(nota, a[31]);
	not(notb, input_b[31]);
	and(ab_s, a[31], input_b[31], not_s);
	and(s_ab, nota, notb, sum[31]);
	or(overflow, ab_s, s_ab);
	
endmodule
