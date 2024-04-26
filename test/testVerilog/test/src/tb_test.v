`timescale 1ns / 1ps
module tb_led_twinkle();
//输入
reg sys_clk;
reg sys_rst_n;
//输出
wire [1:0] led;
//信号初始化
initial begin
 sys_clk = 1'b0;
 sys_rst_n = 1'b0;
 #200
 sys_rst_n = 1'b1;
end
//生成时钟
always #10 sys_clk = ~sys_clk;
//例化待测设计
run_led u_run_led(
 .sys_clk (sys_clk),
 .sys_rst_n (sys_rst_n),
 .led (led)
 );

/* 用iverilog+GTKwave进行仿真所需的临时vcd文件 */
initial begin
   $dumpfile("wave.vcd"); //指定VCD的名字为wave.vcd, 仿真信息将记录到此文件
   $dumpvars(0,tb_led_twinkle ); //指定层次数为0, 则tb_ 模块及其下面各层次的所有信号将被记录
end
endmodule
