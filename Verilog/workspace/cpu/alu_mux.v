module alu_mux (
    clk,
    rst,
    en_in,
    offset,
    rd_q,
    rs_q,
    alu_in_sel,
    alu_a,
    alu_b,
    en_out
);
    input [15:0] rd_q,rs_q;
    input clk,rst,en_in,alu_in_sel;
    input [7:0] offset;
    output reg [15:0] alu_a,alu_b;
    output reg en_out;

    always @(negedge rst or posedge clk) begin
        if(rst==1'b0) begin
            alu_a<=16'b0000_0000_0000_0000;
            alu_b<=16'b0000_0000_0000_0000;
            en_out<=1'b0;
        end
        else begin
            if(en_in==1'b1) begin
                alu_a<=rd_q;
                en_out<=1'b1;
                if(alu_in_sel==1'b0) begin
                    alu_b<={{8{offset[7]}},offset[7:0]};
                end
                else begin
                    alu_b<=rs_q;
                end
            end
            else begin
                en_out<=1'b0;
            end
        end
    end
endmodule

/*
    alu_mux;
    用于给alu输入数据,若alu_in_sel==0,则说明只需要一个操作数
    若alu_in_sel==1,则需要两个操作数
    当en_in使能有效时,输出使能有效
*/