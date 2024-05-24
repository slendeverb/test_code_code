module seg_7 (
    input clk,
    input rst_n,
    input [23:0] data_in,
    output reg [2:0] sel,
    output reg [7:0] seg
);
    parameter CNT_1K = 15'd24999;
    
    reg [3:0] data_tmp;
    reg [14:0] cnt_1k;
    reg flag_1k;

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            cnt_1k<=15'd0;
        end
        else if(cnt_1k==CNT_1K) begin
            cnt_1k<=15'd0;
        end
        else begin
            cnt_1k<=cnt_1k+1'b1;
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            flag_1k<=1'b0;
        end
        else if(cnt_1k==CNT_1K) begin
            flag_1k<=1'b1;
        end
        else begin
            flag_1k<=1'b0;
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            sel<=3'd0;
        end
        else if(sel==3'd5 && flag_1k==1'b1) begin
            sel<=3'd0;
        end
        else if(flag_1k==1'b1) begin
            sel<=sel+1'b1;
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            data_tmp<=4'd0;
        end
        else begin
            case (sel)
                3'd0:data_tmp<=data_in[23:20];
                3'd1:data_tmp<=data_in[19:16];
                3'd2:data_tmp<=data_in[15:12];
                3'd3:data_tmp<=data_in[11:8];
                3'd4:data_tmp<=data_in[7:4];
                3'd5:data_tmp<=data_in[3:0]; 
                default: data_tmp<=4'd0;
            endcase
        end
    end

    always @(posedge clk or negedge rst_n) begin
        if(!rst_n) begin
            seg<=8'b01000000;
        end
        else begin
            case (data_tmp)
                4'h0:seg<=8'b11000000;
                4'h1:seg<=8'b11111001;
                4'h2:seg<=8'b10100100;
                4'h3:seg<=8'b10110000;
                4'h4:seg<=8'b10011001;
                4'h5:seg<=8'b10010010;
                4'h6:seg<=8'b10000010;
                4'h7:seg<=8'b11111000;
                4'h8:seg<=8'b10000000;
                4'h9:seg<=8'b10010000;
                4'ha:seg<=8'b10001000;
                4'hb:seg<=8'b10000011;
                4'hc:seg<=8'b10000110;
                4'hd:seg<=8'b10100001;
                4'he:seg<=8'b10000110;
                4'hf:seg<=8'b10001110; 
            endcase
        end
    end
    
endmodule