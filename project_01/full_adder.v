module full_adder(a, b, cin, sum, cout);
	input a, b, cin;
	output sum, cout;
	
	wire xor_a_b;
	wire and_cin;
	wire and_a_b;
	
	xor(x_a_b, a,b);
	and(and_cin, cin, x_a_b);
	and(and_a_b, a, b);
	xor(sum, x_a_b, cin);
	or(cout, and_cin, and_a_b);
endmodule
