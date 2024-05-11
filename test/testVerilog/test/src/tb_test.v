`timescale 1ns/1ns
module tb_rom;
    reg clk;
    reg rst_n;
    reg [2:0] addr;
    wire [3:0] data_out;

    initial begin
        clk=1'b0;
        rst_n=1'b0;
        addr=3'b110;
    end

    always #10 clk=~clk;
    
    initial @(posedge clk) begin
        #1 rst_n=1'b1;
    end

    always @(negedge clk) begin
        #9;
        if(addr<3'b111) begin
            addr=addr+1'b1;
        end
        else begin
            addr=3'b000;
        end
    end

    rom rom(
        .clk(clk),
        .rst_n(rst_n),
        .addr(addr),
        .data_out(data_out)
    );

    /* 用iverilog+GTKwave进行仿真所需的临时vcd文件 */
    initial begin
        $dumpfile("wave.vcd"); // 指定VCD的名字为wave.vcd, 仿真信息将记录到此文件
        $dumpvars(0,tb_rom); // 指定层次数为0, 则tb_ 模块及其下面各层次的所有信号将被记录
    end
endmodule