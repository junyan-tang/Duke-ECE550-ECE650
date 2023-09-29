module SRA(a, s, res);
	input [31:0] a;
	input [4:0] s;
	output [31:0] res;
	
	wire [31:0] c1, c2, c3, c4;
	wire neg_pos;
	
	mux m_np (1'b0, 1'b1, a[31], neg_pos);
	
	genvar i;	
	generate
		//first layer
		mux m1(a[31], neg_pos, s[0], c1[31]);
		for( i = 31; i > 0; i = i - 1) begin:sra_loop_m1
			mux m_1(a[i - 1], a[i], s[0], c1[i - 1]);
		end
		
		//second layer
		for( i = 31; i > 29; i = i - 1) begin:sra_initial_m2
			mux m2(c1[i], neg_pos, s[1], c2[i]);
		end
		for ( i = 31; i > 1; i = i - 1) begin:sra_loop_m2
			mux m_2(c1[i - 2], c1[i], s[1], c2[i - 2]);
		end
		
		//third layer
		for( i = 31; i > 27; i = i - 1) begin:sra_initial_m3
			mux m3(c2[i], neg_pos, s[2], c3[i]);
		end
		for ( i = 31; i > 3; i = i - 1) begin:sra_loop_m3
			mux m_3(c2[i - 4], c2[i], s[2], c3[i - 4]);
		end
		
		//fourth layer
		for( i = 31; i > 23; i = i - 1) begin:sra_initial_m4
			mux m4(c3[i], neg_pos, s[3], c4[i]);
		end
		for( i = 31; i > 7; i = i - 1) begin:sra_loop_m4
			mux m_4(c3[i - 8], c3[i], s[3], c4[i - 8]);
		end
		
		//fifth layer
		for( i = 31; i > 15; i = i - 1) begin:sra_initial_m5
			mux m5(c4[i], neg_pos, s[4], res[i]);
		end
		for( i = 31; i > 15; i = i - 1) begin:sra_loop_m5
			mux m_5(c4[i - 16], c4[i], s[4], res[i - 16]);
		end
	endgenerate
endmodule
