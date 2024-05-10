`timescale 1ns/1ns
module tb_adder32;
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

    
    /* 用iverilog+GTKwave进行仿真所需的临时vcd文件 */
    initial begin
        $dumpfile("wave.vcd"); //指定VCD的名字为wave.vcd, 仿真信息将记录到此文件
        $dumpvars(0,tb_adder32); //指定层次数为0, 则tb_ 模块及其下面各层次的所有信号将被记录
    end
endmodule