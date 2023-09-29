module SLL(a, s, res);
	input [31:0] a;
	input [4:0] s;
	output [31:0] res;
	
	wire [31:0] c1, c2, c3, c4;
	
	genvar i;
	generate
		//first layer
		mux m1(a[0], 1'b0, s[0], c1[0]);	
		for ( i = 1; i < 32; i = i + 1) begin: sll_loop_m1
			mux m_1(a[i], a[i-1], s[0], c1[i]);
		end
		
		//second layer
		for ( i = 0; i < 2; i = i + 1) begin: sll_init_m2
			mux m2(c1[i], 1'b0, s[1], c2[i]);
		end
		for ( i = 2; i < 32; i = i + 1) begin: sll_loop_m2
			mux m_2(c1[i], c1[i-2], s[1], c2[i]);
		end
		
		//third layer
		for ( i = 0; i < 4; i = i + 1) begin: sll_init_m3
			mux m3(c2[i], 1'b0, s[2], c3[i]);
		end
		for ( i = 4; i < 32; i = i + 1) begin: sll_loop_m3
			mux m_3(c2[i], c2[i-4], s[2], c3[i]);
		end
		
		//forth layer
		for ( i = 0; i < 8; i = i + 1) begin: sll_init_m4
			mux m4(c3[i], 1'b0, s[3], c4[i]);
		end
		for ( i = 8; i < 32; i = i + 1) begin: sll_loop_m4
			mux m_4(c3[i], c3[i-8], s[3], c4[i]);
		end
		
		//fifth layer
		for ( i = 0; i < 16; i = i + 1) begin: sll_init_m5
			mux m5(c4[i], 1'b0, s[4], res[i]);
		end
		for ( i = 16; i < 32; i = i + 1) begin: sll_loop_m5
			mux m_5(c4[i], c4[i-16], s[4], res[i]);
		end
	endgenerate
		
endmodule
