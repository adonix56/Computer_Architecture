module testbench4_38();
 	logic up, reset = 1, clk;
	logic [2:0] q, result;
	ex4_38 fsm(clk, reset, up, q);
	logic [4:0] testvectors[1000];
	integer trial;

	initial
		begin
			$readmemb("4_38test.txt", testvectors);
			trial = 0;
			clk = 1;
		end

	always
		#5 clk = ~clk;

	always_ff @ (negedge clk)
		begin
			reset <= testvectors[trial][4];
			up <= testvectors[trial][3];
			result = testvectors[trial - 1][2:0];

	  	assert(trial < 2 || q == testvectors[trial - 1][2:0])
				else
					begin
						$display("At trial #%d, reset = %b, up = %b, %b should be %b", trial, reset, up, q, result);
						$stop;
					end
			
			trial++;

			if(trial == 1000)
				begin
					$display("No errors found!");
					$stop;
				end
		end  // alway_ff

		
endmodule