module mux8 #(parameter width = 4) (input logic [width-1:0] d0, d1, d2, d3,d4, d5, 
d6, d7, input logic [2:0] s, output logic [width-1:0] y); 
	always_comb
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
