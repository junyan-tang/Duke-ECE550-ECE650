module tristate_buffer(data, select, buffer_out);
	input [31:0] data;
	input select;
	output [31:0] buffer_out;
	
	genvar i;
	generate for(i = 0; i < 32; i = i + 1)begin: buffer_o
		assign buffer_out[i] = select ? data[i] : 1'bz;
	end
	endgenerate
endmodule
