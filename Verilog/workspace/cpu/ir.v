module ir (
    clk,
    rst,
    ins,
    en_in,
    en_out,
    ir_out
);
    input clk,rst;
    input [15:0] ins;
    input en_in;
    output reg en_out;
    output reg [15:0] ir_out;

    always @(posedge clk or negedge rst) begin
        if(!rst) begin
            ir_out<=16'b0000000000000000;
            en_out<=1'b0;
        end
        else begin
            if(en_in) begin
                en_out<=1'b1;
                ir_out<=ins;
            end
            else begin
                en_out<=1'b0;
            end
        end
    end
endmodule

/*
    IR: Instruction Register,用于存放当前即将执行的指令
    在使能有效时,将指令输出给state_transition完成状态转移
*/