`timescale 1ns/1ps

module reg_group (
    clk,
    rst,
    en_in,
    reg_en,
    d_in,
    rd,
    rs,
    en_out,
    rd_q,
    rs_q
);
    input clk,rst,en_in;//时钟信号,复位信号,操作四个寄存器的使能信号
    input wire [3:0] reg_en;//用于实例化寄存器的使能信号
    input wire [15:0] d_in;//输入数据
    input wire [1:0] rd,rs;//用于选择如何分配寄存器的值给两个输出信号,两个输出信号均有4中取值(共有四个寄存器,每个信号读取其中一个寄存器)
    output reg en_out;//输出使能
    output reg [15:0] rd_q,rs_q;//输出信号 目标寄存器和源寄存器

    wire [15:0] q0,q1,q2,q3;//每个寄存器的输出

    register reg0(
        .clk(clk),
        .rst(rst),
        .en(reg_en[0]),
        .d(d_in),
        .q(q0)
    );

    register reg1(
        .clk(clk),
        .rst(rst),
        .en(reg_en[1]),
        .d(d_in),
        .q(q1)
    );

    register reg2(
        .clk(clk),
        .rst(rst),
        .en(reg_en[2]),
        .d(d_in),
        .q(q2)
    );

    register reg3(
        .clk(clk),
        .rst(rst),
        .en(reg_en[3]),
        .d(d_in),
        .q(q3)
    );

    always @(posedge clk or negedge rst) begin
        if(rst==0) begin
            rd_q<=0;
            rs_q<=0;
            en_out<=0;
        end
        else begin
            if(en_in==1) begin
                en_out<=1;
                case ({rd[1:0],rs[1:0]})
                    4'b0000: begin
                        rd_q<=q0;
                        rs_q<=q0;
                    end
                    4'b0001: begin
                        rd_q<=q0;
                        rs_q<=q1;
                    end
                    4'b0010: begin
                        rd_q<=q0;
                        rs_q<=q2;
                    end
                    4'b0011: begin
                        rd_q<=q0;
                        rs_q<=q3;
                    end
                    4'b0100: begin
                        rd_q<=q1;
                        rs_q<=q0;
                    end
                    4'b0101: begin
                        rd_q<=q1;
                        rs_q<=q1;
                    end
                    4'b0110: begin
                        rd_q<=q1;
                        rs_q<=q2;
                    end
                    4'b0111: begin
                        rd_q<=q1;
                        rs_q<=q3;
                    end
                    4'b1000: begin
                        rd_q<=q2;
                        rs_q<=q0;
                    end
                    4'b1001: begin
                        rd_q<=q2;
                        rs_q<=q1;
                    end
                    4'b1010: begin
                        rd_q<=q2;
                        rs_q<=q2;
                    end
                    4'b1011: begin
                        rd_q<=q2;
                        rs_q<=q3;
                    end
                    4'b1100: begin
                        rd_q<=q3;
                        rs_q<=q0;
                    end
                    4'b1101: begin
                        rd_q<=q3;
                        rs_q<=q1;
                    end
                    4'b1110: begin
                        rd_q<=q3;
                        rs_q<=q2;
                    end
                    4'b1111: begin
                        rd_q<=q3;
                        rs_q<=q3;
                    end
                    default: begin
                        rd_q<=0;
                        rs_q<=0;
                    end
                endcase
            end
            else begin
                en_out<=0;
            end
        end
    end
endmodule

/*
    在每个时钟上升沿,确定如何将哪些寄存器中的值赋值给rd_q和rs_q,rd_q和rs_q将作用于给alu_a和alu_b赋值
*/