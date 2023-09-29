module CSA_32bits(a, b, cin, sum, cout);	
	input [31:0] a, b;
	input cin;
	output [31:0] sum;
	output cout;
	
	wire c1, c2, c3;
	wire [15:0] s1, s2;
	
	RCA_16bits rca1(a[15:0], b[15:0], cin, sum[15:0], c1);
	RCA_16bits rca2(a[31:16], b[31:16], 0, s1, c2);
	RCA_16bits rca3(a[31:16], b[31:16], 1, s2, c3);
	
	mux_16 m_16(s1, s2, c1, sum[31:16]);
	mux m1(c2, c3, c1, cout);
	
endmodule
	