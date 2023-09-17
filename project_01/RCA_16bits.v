module RCA_16bits(a, b, cin, sum, cout);
	parameter N = 16;
	
	input [N-1:0] a, b;
	input cin;
	output [N-1:0] sum;
	output cout;
	
	wire [N:0] c;
	
	genvar i;
	generate for (i = 0; i< N; i = i+1) begin: fulladder_loop
		full_adder( a[i], b[i], c[i], sum[i], c[i+1]);
	end
	endgenerate
	
	assign c[0] = cin;
	assign cout = c[N];
	
endmodule
