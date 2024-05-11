module rom (
    input clk,
    input rst_n,
    input [2:0] addr,
    output reg [3:0] data_out
);
    reg [3:0] mem[8];
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            mem[0]<=4'd0;
            mem[1]<=4'd1;
            mem[2]<=4'd3;
            mem[3]<=4'd5;
            mem[4]<=4'd7;
            mem[5]<=4'd9;
            mem[6]<=4'd11;
            mem[7]<=4'd13;
        end
        else begin
            data_out<=mem[addr];
        end
    end
endmodule