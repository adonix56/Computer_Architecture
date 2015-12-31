module ex4_38(input logic clk, reset, up, output logic [2:0] q);
	typedef enum logic[2:0] {S0, S1, S2, S3, S4, S5, S6, S7} statetype;
	statetype state, nextstate;

	always_ff @ (posedge clk or posedge reset)
			if(reset)
				state <= S0;
			else
				state <= nextstate;

	always_comb
		case(state)
			S0:	if(up)	nextstate = S1;
					else		nextstate = S7;
			S1:	if(up)	nextstate = S2;
					else		nextstate = S0;
			S2:	if(up)	nextstate = S3;
					else		nextstate = S1;
			S3:	if(up)	nextstate = S4;
					else		nextstate = S2;
			S4:	if(up)	nextstate = S5;
					else		nextstate = S3;
			S5:	if(up)	nextstate = S6;
					else		nextstate = S4;
			S6:	if(up)	nextstate = S7;
					else		nextstate = S5;
			S7:	if(up)	nextstate = S0;
					else		nextstate = S6;
		endcase
	assign q[2] = (state == S4 | state == S5 | state == S6 | state == S7);
	assign q[1] = (state == S2 | state == S3 | state == S4 | state == S5);
	assign q[0] = (state == S1 | state == S2 | state == S5 | state == S6);
endmodule
