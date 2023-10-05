module decoder(w_addr, choice);
	input [4:0] w_addr;
	output [31:0] choice;
	
	wire [4:0] not_addr;
	
	genvar i;
	generate for(i = 0; i < 5; i = i + 1) begin: not_loop
		not(not_addr[i], w_addr[i]);
	end
	endgenerate
	
	and a0(choice[0], not_addr[4], not_addr[3], not_addr[2], not_addr[1], not_addr[0]);
	and a1(choice[1], not_addr[4], not_addr[3], not_addr[2], not_addr[1], w_addr[0]);
	and a2(choice[2], not_addr[4], not_addr[3], not_addr[2], w_addr[1], not_addr[0]);
	and a3(choice[3], not_addr[4], not_addr[3], not_addr[2], w_addr[1], w_addr[0]);
	and a4(choice[4], not_addr[4], not_addr[3], w_addr[2], not_addr[1], not_addr[0]);
	and a5(choice[5], not_addr[4], not_addr[3], w_addr[2], not_addr[1], w_addr[0]);
	and a6(choice[6], not_addr[4], not_addr[3], w_addr[2], w_addr[1], not_addr[0]);
	and a7(choice[7], not_addr[4], not_addr[3], w_addr[2], w_addr[1], w_addr[0]);
	
	and a8(choice[8], not_addr[4], w_addr[3], not_addr[2], not_addr[1], not_addr[0]);
	and a9(choice[9], not_addr[4], w_addr[3], not_addr[2], not_addr[1], w_addr[0]);
	and a10(choice[10], not_addr[4], w_addr[3], not_addr[2], w_addr[1], not_addr[0]);
	and a11(choice[11], not_addr[4], w_addr[3], not_addr[2], w_addr[1], w_addr[0]);
	and a12(choice[12], not_addr[4], w_addr[3], w_addr[2], not_addr[1], not_addr[0]);
	and a13(choice[13], not_addr[4], w_addr[3], w_addr[2], not_addr[1], w_addr[0]);
	and a14(choice[14], not_addr[4], w_addr[3], w_addr[2], w_addr[1], not_addr[0]);
	and a15(choice[15], not_addr[4], w_addr[3], w_addr[2], w_addr[1], w_addr[0]);
	
	and a16(choice[16], w_addr[4], not_addr[3], not_addr[2], not_addr[1], not_addr[0]);
	and a17(choice[17], w_addr[4], not_addr[3], not_addr[2], not_addr[1], w_addr[0]);
	and a18(choice[18], w_addr[4], not_addr[3], not_addr[2], w_addr[1], not_addr[0]);
	and a19(choice[19], w_addr[4], not_addr[3], not_addr[2], w_addr[1], w_addr[0]);
	and a20(choice[20], w_addr[4], not_addr[3], w_addr[2], not_addr[1], not_addr[0]);
	and a21(choice[21], w_addr[4], not_addr[3], w_addr[2], not_addr[1], w_addr[0]);
	and a22(choice[22], w_addr[4], not_addr[3], w_addr[2], w_addr[1], not_addr[0]);
	and a23(choice[23], w_addr[4], not_addr[3], w_addr[2], w_addr[1], w_addr[0]);
	and a24(choice[24], w_addr[4], w_addr[3], not_addr[2], not_addr[1], not_addr[0]);
	and a25(choice[25], w_addr[4], w_addr[3], not_addr[2], not_addr[1], w_addr[0]);
	and a26(choice[26], w_addr[4], w_addr[3], not_addr[2], w_addr[1], not_addr[0]);
	and a27(choice[27], w_addr[4], w_addr[3], not_addr[2], w_addr[1], w_addr[0]);
	and a28(choice[28], w_addr[4], w_addr[3], w_addr[2], not_addr[1], not_addr[0]);
	and a29(choice[29], w_addr[4], w_addr[3], w_addr[2], not_addr[1], w_addr[0]);
	and a30(choice[30], w_addr[4], w_addr[3], w_addr[2], w_addr[1], not_addr[0]);
	and a31(choice[31], w_addr[4], w_addr[3], w_addr[2], w_addr[1], w_addr[0]);
	
endmodule
