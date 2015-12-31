
module cpu(input clock);
logic [21:0] RAMdata;
logic [6:0][8:0] r;
logic [9:0] count;
logic [8:0] write, a_out, b_out;
logic [6:0] dec_out;
logic PC_Reset;
logic test = 0;

always_comb
if (r[0] === 9'bxxxxxxxxx|
		r[1] === 9'bxxxxxxxxx|
		r[2] === 9'bxxxxxxxxx|
		r[3] === 9'bxxxxxxxxx|
		r[4] === 9'bxxxxxxxxx|
		r[5] === 9'bxxxxxxxxx|
		r[6] === 9'bxxxxxxxxx)
	test = 0;
else
	test = 1;

PC pc1(clock, PC_Reset, count);
RAM_Test ram1(RAMdata, PC_Reset, count, r, clock);
Decoder dec1(RAMdata[11:9], count, dec_out, RAMdata[21:18]);
Mux8 amux(r[0], r[1], r[2], r[3], r[4], r[5], r[6], 0, RAMdata[17:15], 4'b0000, a_out);
Mux8 bmux(r[0], r[1], r[2], r[3], r[4], r[5], r[6], RAMdata[8:0], RAMdata[14:12], RAMdata[21:18], b_out);
ALU alu(write, a_out, b_out, RAMdata[21:18]);
RegisterBank bank1(clock, write, dec_out, RAMdata[8:0], r, test);
endmodule

module Decoder(input logic [2:0] a, input logic[9:0] count,
							 output logic [6:0] y, input logic[3:0] copy);
	always_comb
		if (copy === 4'b1011)
		y = 7'b0000000;
		else
		case(a)
			3'b000:  y = 7'b0000001;
			3'b001:  y = 7'b0000010;
			3'b010:  y = 7'b0000100;
			3'b011:  y = 7'b0001000;
			3'b100:  y = 7'b0010000;
			3'b101:  y = 7'b0100000;
			3'b110:  y = 7'b1000000;
			default: y = 7'b0000000;
		endcase
endmodule

module PC(input clock, input reset, output logic [9:0]count);
	always_ff @(posedge clock, negedge reset)
	begin
	if (reset)
		count<=9'b000000000;
	else
		count<=count+1;
	end
endmodule

module Mux8 #(parameter width = 9) (input logic [8:0] d0, d1, d2, d3,d4, d5, 
d6, d7, input logic [2:0] s, input logic [3:0] copy, output logic [8:0] y); 
	always_comb
		if(copy === 4'b1000|
				copy === 4'b1001|
				copy === 4'b1010)
			y = d7;
		else
		case(s)
			3'b000: y = d0;
			3'b001: y = d1;
			3'b010: y = d2;
			3'b011: y = d3;
			3'b100:	y = d4;
			3'b101: y = d5;
			3'b110: y = d6;
			default: y = d7;
		endcase
endmodule

module RegisterBank(input clock, input [8:0] alu_in, input [6:0] dec_in,
										input [8:0] data, output [6:0][8:0] registers, input test);
logic [8:0] d0, d1, d2, d3, d4, d5, d6;
	always_comb
	if (!test)
	begin
		case(dec_in)
			7'b0000001: d0 = data;
			7'b0000010: d1 = data;
			7'b0000100: d2 = data;
			7'b0001000: d3 = data; 
			7'b0010000: d4 = data;
			7'b0100000: d5 = data;
			7'b1000000: d6 = data;
			default:    ;
		endcase
	end
	else
	begin
		case(dec_in)
			7'b0000001: d0 = alu_in;
			7'b0000010: d1 = alu_in;
			7'b0000100: d2 = alu_in;
			7'b0001000: d3 = alu_in; 
			7'b0010000: d4 = alu_in;
			7'b0100000: d5 = alu_in;
			7'b1000000: d6 = alu_in;
			default:    ;
		endcase
	end
	Register R0(clock, dec_in[0], d0, registers[0]);
	Register R1(clock, dec_in[1], d1, registers[1]);
	Register R2(clock, dec_in[2], d2, registers[2]);
	Register R3(clock, dec_in[3], d3, registers[3]);
	Register R4(clock, dec_in[4], d4, registers[4]);
	Register R5(clock, dec_in[5], d5, registers[5]);
	Register R6(clock, dec_in[6], d6, registers[6]);
endmodule

module Register(input clock, write,
								input logic [8:0] d,
								output logic [8:0] q);
	always_ff @(negedge clock)
		if(write)
			 q <= d;
endmodule
