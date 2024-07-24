`timescale 1ns/1ps

module pc (
    clk,
    rst,
    en_in,
    pc_ctrl,//控制指令寄存器的下一取值
    offset_addr,
    pc_out
);
    input clk,rst,en_in;
    input wire [1:0] pc_ctrl;
    input wire [7:0] offset_addr;
    output reg [15:0] pc_out;

    always @(posedge clk or negedge rst) begin
        if(rst==0) begin
            pc_out<=0;
        end
        else begin
            if(en_in==1) begin
                case (pc_ctrl)
                    2'b00: pc_out<=pc_out;
                    2'b01: pc_out<=pc_out+1;
                    2'b10: pc_out<={8'b00000000,offset_addr[7:0]};//jump去指定的地址
                    2'b11: pc_out<=pc_out+offset_addr;
                    default: pc_out<=pc_out;
                endcase
            end
        end
    end
endmodule

/*
    pc: program counter
*/