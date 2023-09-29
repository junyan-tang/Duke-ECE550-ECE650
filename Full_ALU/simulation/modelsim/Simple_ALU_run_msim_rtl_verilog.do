transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/full_adder.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/alu.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/RCA_16bits.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/add_sub.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/mux_16.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/CSA_32bits.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/mux.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/and_logic.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/or_logic.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/SLL.v}
vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/SRA.v}

vlog -vlog01compat -work work +incdir+C:/ECE550/Full_ALU {C:/ECE550/Full_ALU/alu_tb.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L cycloneive_ver -L rtl_work -L work -voptargs="+acc"  alu_tb

add wave *
view structure
view signals
run -all
