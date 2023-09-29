module mux(a, b, s, out);
	input a, b;
	input s;
	output out;
	
	wire not_s;
	wire and_sa, and_sb;
	
	not(not_s, s);
	and(and_sa, a, not_s);
	and(and_sb, b, s);
	or(out, and_sa, and_sb);
endmodule
