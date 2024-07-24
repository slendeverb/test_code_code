`timescale 1ns/1ps

module cpu_tb ();
    reg clk,rst,en_in,en_ram_out;
    reg [15:0] ins;
    wire en_ram_in;
    wire [15:0] addr;

    cpu test_cpu(
        .clk(clk),
        .rst(rst),
        .en_in(en_in),
        .en_ram_in(en_ram_in),
        .ins(ins),
        .en_ram_out(en_ram_out),
        .addr(addr)
    );

    parameter Tclk = 10;

    initial begin
        clk=0;
    end

    initial begin
        rst=1;
        rst=~rst;
        #1 rst=~rst;
    end

    initial begin
        en_in=0;
        en_ram_out=0;
    end

    initial begin
        ins=16'b0000_0000_0000_0001;
        #(Tclk*20)
        ins=16'b0000_0100_0000_0010;
        #(Tclk*20)
        ins=16'b1010_1111_1100_0010;
    end

    always #Tclk clk=~clk;

    initial begin
        #(Tclk*400) $stop;
    end

    /* 用iverilog+GTKwave进行仿真所需的临时vcd文件 */
    initial begin
        $dumpfile("wave.vcd"); // 指定VCD的名字为wave.vcd, 仿真信息将记录到此文件
        $dumpvars(0,cpu_tb); // 指定层次数为0, 则tb模块及其下面各层次的所有信号将被记录
    end
endmodule