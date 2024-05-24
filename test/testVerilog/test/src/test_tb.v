`timescale 1ns/1ns

module seg_7_tb ();
    reg clk;
    reg rst_n;
    reg [23:0] data_in;
    wire [2:0] sel;
    wire [7:0] seg;

    seg_7 seg_7(
        .clk(clk),
        .rst_n(rst_n),
        .data_in(data_in),
        .sel(sel),
        .seg(seg)
    );

    initial begin
        clk=1'b0;
        rst_n=1'b1;
        data_in=24'b0;

        rst_n=~rst_n;

        #1 rst_n=~rst_n;
    end

    always #2 clk=~clk;

    always begin
        #10
        if(data_in==24'b111111111111111111111111) begin
            data_in=24'b0;
        end
        else begin
            data_in=data_in+1'b1;
        end
    end

    initial begin
        #2000000
        $stop;
    end

    /* 用iverilog+GTKwave进行仿真所需的临时vcd文件 */
    initial begin
        $dumpfile("wave.vcd"); // 指定VCD的名字为wave.vcd, 仿真信息将记录到此文件
        $dumpvars(0,seg_7_tb); // 指定层次数为0, 则tb模块及其下面各层次的所有信号将被记录
    end
endmodule