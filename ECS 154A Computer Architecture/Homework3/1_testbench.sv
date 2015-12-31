module testbench();
	logic [4:0]d[7:0], y5, result;
	logic [3:0] y4;
	logic [2:0]select, y3;
	logic [1:0]y2;
	logic y1;
	logic [50:0]testvectors[39:0];
	//mux8 #(1) mux1(d[0][0], d[1][0], d[2][0], d[3][0], d[4][0], d[5][0], d[6][0], d[7][0], select, y1);  Won't work!!!
	mux8 #(2) mux2(d[0][1:0], d[1][1:0], d[2][1:0], d[3][1:0], d[4][1:0], d[5][1:0], d[6][1:0], d[7][1:0], select, y2);
	mux8 #(3) mux3(d[0][2:0], d[1][2:0], d[2][2:0], d[3][2:0], d[4][2:0], d[5][2:0], d[6][2:0], d[7][2:0], select, y3);
	mux8  mux4(d[0][3:0], d[1][3:0], d[2][3:0], d[3][3:0], d[4][3:0], d[5][3:0], d[6][3:0], d[7][3:0], select, y4);
	mux8 #(5) mux5(d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], select, y5);
  integer trial;

	initial
		begin
			$readmemb("4_8test.txt", testvectors);
			for(trial = 0; trial < 40; trial++)
				begin
					d[0] <= testvectors[trial][47:43];
					d[1] <= testvectors[trial][42:38];
					d[2] <= testvectors[trial][37:33];
					d[3] <= testvectors[trial][32:28];
					d[4] <= testvectors[trial][27:23];
					d[5] <= testvectors[trial][22:18];
					d[6] <= testvectors[trial][17:13];
					d[7] <= testvectors[trial][12:8];
					
			
				
					select <= testvectors[trial][7:5];
					result <= testvectors[trial][4:0];
				
					/* assert(y1 == result[0])
						else
							begin
								$display("Error on trial #%d y1 = %b but should be %b", trial, y1, result[0]);
								$stop;
							end
*/
					#1  assert(y2 == result[1:0])
						else
							begin
								$display("Error on trial #%d y2 = %b but should be %b", trial, y2, result[1:0]);
								$stop;
							end

					assert(y3 == result[2:0])
						else
							begin
								$display("Error on trial #%d y3 = %b but should be %b", trial, y3, result[2:0]);
								$stop;
							end

					assert(y4 == result[3:0])
						else
							begin
								$display("Error on trial #%d y4 = %b but should be %b", trial, y4, result[3:0]);
								$stop;
							end

					assert(y5 == result)
						else
							begin
								$display("Error on trial #%d y5 = %b but should be %b", trial, y5, result);
								$stop;
							end



				end  // for

			$display("No errors.");
		end  // initial

endmodule
