`timescale 1ns/1ns
module adder32_tb;
    reg [32:1] A;
    reg [32:1] B;
    wire [32:1] S;
    wire c32;

    adder32 adder32(
        .A(A),
        .B(B),
        .S(S),
        .C32(c32)
    );

    initial begin
        A=32'd0; B=32'd0;
        #5; A=32'd456; B=32'd234;
        #5; A=32'd245; B=32'd678;
        #5;
        $stop; 
    end
endmodule