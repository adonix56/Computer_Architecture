module CLA(output logic [2:0] carries, output logic cout, input logic [2:0] ps, gs, input cin);
	always_comb
		begin
			carries[0] = cin;
			carries[1] = gs[0] | (ps[0] & carries[0]);
			carries[2] = gs[1] | (ps[1] & gs[0]) | (ps[1] & ps[0] & carries[0]);
			cout = gs[2] | (ps[2] & gs[1]) | (ps[2] & ps[1] & gs[0]) | (ps[2] & ps[1] & ps[0] & carries[0]);
		end
endmodule

module adder(output logic [8:0] out, input [8:0] a, b, input cin);
	logic [8:0] ps, gs, carries;
	logic [2:0] carries1, carries2, carries3;
	logic cout1, cout2, cout3;
	assign ps = a ^ b;
	assign gs = a & b;
	CLA cla1(carries1, cout1, ps[2:0], gs[2:0], cin);
	CLA cla2(carries2, cout2, ps[5:3], gs[5:3], cout1);
	CLA cla3(carries3, cout3, ps[8:6], gs[8:6], cout2);
	assign carries = {carries3, carries2, carries1};
	assign out = ps ^ carries;
endmodule

module ALU(output logic [8:0] out, input [8:0] a, b, input[3:0] opcode);
	logic [8:0] addsum, subsum;
	adder add(addsum, a, b, 1'b0);
	adder sub(subsum, a, ~b, 1'b1);
	always_comb
		begin
			case(opcode)
				4'b0000:	out = a & b;
				4'b0001:	out = a | b;
				4'b0010:	out = ~a;
				4'b0011:	out = addsum;
				4'b0100:	out = a;
				4'b0101:	out = {a[7:0], 1'b0};
				4'b0110:	out = {1'b0, a[8:1]};
				4'b0111:	out = subsum;
				4'b1000:	out = addsum;//a + b;
				4'b1001:	out = subsum;//a - b;
				4'b1010:	out = b;
				4'b1011:	;
				4'b1111:	$finish;
				default:	out = 9'b000000000;
			endcase
		end				
endmodule
