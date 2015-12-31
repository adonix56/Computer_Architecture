module testbench();
	logic s, r, q, qbar;
	srlatch latch(s, r, q, qbar);
	
	initial
		begin
			s = 0; r = 1;
	#1	assert(q == 0 && qbar == 1)
				else
					begin
						$display("For original q = x, s = %b, r = %b, q was %b, qbar was %b, q should be 0 and qbar should be 1", 
							s, r, q, qbar);
						$stop;
					end 

				s = 1; r = 0;
	#1		assert(q == 1 && qbar == 0)
				else
					begin
						$display("For original q = x, s = %b, r = %b, q was %b, qbar was %b, q should be 1 and qbar should be 0", 
							s, r, q, qbar);
						$stop;
					end 
			s = 0; r = 1;
	#1	s = 0; r = 0;
	#1	assert(q == 0 && qbar == 1)
				else
					begin
						$display("For original q = 0, s = %b, r = %b, q was %b, qbar was %b, q should be 0 and qbar should be 1", 
							s, r, q, qbar);
						$stop;
					end 

			s = 0; r = 1;
	#1	s = 0; r = 1;
	#1	assert(q == 0 && qbar == 1)
				else
					begin
						$display("For original q = 0, s = %b, r = %b, q was %b, qbar was %b, q should be 0 and qbar should be 1", 
							s, r, q, qbar);
						$stop;
					end 

			s = 0; r = 1;
	#1	s = 1; r = 0;
	#1	assert(q == 1 && qbar == 0)
				else
					begin
						$display("For original q = 0, s = %b, r = %b, q was %b, qbar was %b, q should be 1 and qbar should be 0", 
							s, r, q, qbar);
						$stop;
					end 

			s = 1; r = 0;
	#1	s = 0; r = 0;
	#1	assert(q == 1 && qbar == 0)
				else
					begin
						$display("For original q = 1, s = %b, r = %b, q was %b, qbar was %b, q should be 1 and qbar should be 0", 
							s, r, q, qbar);
						$stop;
					end 

			s = 1; r = 0;
	#1	s = 0; r = 1;
	#1	assert(q == 0 && qbar == 1)
				else
					begin
						$display("For original q = 1, s = %b, r = %b, q was %b, qbar was %b, q should be 0 and qbar should be 1", 
							s, r, q, qbar);
						$stop;
					end 

			s = 1; r = 0;
	#1	s = 1; r = 0;
	#1	assert(q == 1 && qbar == 0)
				else
					begin
						$display("For original q = 1, s = %b, r = %b, q was %b, qbar was %b, q should be 1 and qbar should be 0", 
							s, r, q, qbar);
						$stop;
					end
 
			$display("No errors found!");
		end // initial
endmodule // testbench

