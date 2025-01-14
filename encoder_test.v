// iverilog -o test .\encoder.v .\encoder_test.v
// vvp .\test
// gtkwave.exe .\encoder_test.vcd

module encoder_test();
    
    reg enable;
    reg [15:0] encoder_in; 
    wire [3:0] binary_out;
    
    initial begin
        $dumpfile("encoder_test.vcd");  // for gtkwave
        $dumpvars(0,encoder_test);

        $monitor("%g\t %b %b %b",$time,enable,encoder_in,binary_out);

        enable = 0;
        #5 enable = 1;
        #6 encoder_in = 16'h0004;
        #7 encoder_in = 16'h0040;
        #8 encoder_in = 16'h0400;
        #9 encoder_in = 16'h4000;
        #10 $finish;        
    end

    encoder myencoder(binary_out,encoder_in,enable);

endmodule
