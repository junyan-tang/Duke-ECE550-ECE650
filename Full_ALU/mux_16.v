module mux_16(a, b, s, out);
	input [15:0] a, b;
	input s;
	output [15:0] out;
	
	wire not_s;
	wire [15:0] and_sa, and_sb;
	
	not(not_s, s);
	
	genvar i;
	generate for (i = 0; i < 16; i = i + 1) begin: mux_loop
		and(and_sa[i], a[i], not_s);
		and(and_sb[i], b[i], s);
		or(out[i], and_sa[i], and_sb[i]);
	end
	endgenerate
	
endmodule

module mux_32(a, b, s, out);
	input [31:0] a, b;
	input s;
	output [31:0] out;
	
	wire not_s;
	wire [31:0] and_sa, and_sb;
	
	not(not_s, s);
	
	genvar i;
	generate for (i = 0; i < 32; i = i + 1) begin: mux_loop
		and(and_sa[i], a[i], not_s);
		and(and_sb[i], b[i], s);
		or(out[i], and_sa[i], and_sb[i]);
	end
	endgenerate
endmodule
