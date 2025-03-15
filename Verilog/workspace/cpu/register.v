`timescale 1ns/1ps

module register (
    clk,
    rst,
    en,
    d,
    q
);
    input clk,rst,en;
    input wire [15:0] d;
    output reg [15:0] q;

    always @(posedge clk or negedge rst) begin
        if(rst==0) begin
            q<=0;
        end
        else begin
            if(en==1) begin
                q<=d;
            end
            else begin
                q<=q;
            end
        end
    end
endmodule

/*
    寄存器模块,在时钟上升沿且Control Unit给出的控制信号en为高时,更新寄存器,否则锁存数据
*/