module half_adder(a, b, sum, cout);
	input a, b;
	output sum, cout;
	
	xor(sum, a, b);
	and(cout, a, b);
endmodule
