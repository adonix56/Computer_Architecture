module srlatch(input logic s, r, output logic q, qbar);
	always_latch
		begin
			if(r == 1)
				begin
					q <= 0;
					qbar <= 1;
				end
			else if(s == 1)
				begin
					q <= 1;
					qbar <= 0;
				end
		end
endmodule
