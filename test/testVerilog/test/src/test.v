module cache ();
    parameter size = 64;
    parameter index_size = 6;

    reg [31:0] cache [0:size-1];
    reg [11-index_size:0] tag_array [0:size-1];
    reg valid_array [0:size-1];

    initial begin:initialization
        integer i;
        for(i=0;i<size;i=i+1)
        begin
            valid_array[i]=1'b0;
            tag_array[i]=6'b000000;
        end
    end
endmodule

module ram ();
    parameter size = 4096;
    reg [31:0] ram [0:size-1];
endmodule

module cache_and_ram (
    input [31:0] address,
    input [31:0] data,
    input clk,
    input mode,
    output [31:0] out
);
    ram ram();
    cache cache();

    reg [31:0] prev_address, prev_data;
    reg prev_mode;
    reg [31:0] temp_out;

    reg [6-1:0] index;
    reg [11-6:0] tag;

    initial begin
        index=0;
        tag=0;
        prev_address=0;
        prev_data=0;
        prev_mode=0;
    end

    always @(posedge clk) begin
        if(prev_address!=address||prev_data!=data||prev_mode!=mode)
        begin
            prev_address=address%ram.size;
            prev_data=data;
            prev_mode=mode;
            tag=prev_address>>cache.index_size;
            index=address%cache.size;

            if(mode==1)
            begin
                ram.ram[prev_address]=data;
                if(cache.valid_array[index]==1&&cache.tag_array[index]==tag)
                begin
                    cache.cache[index]=data;
                end
            end
            else
            begin
                if(cache.valid_array[index]!=1||cache.tag_array[index]!=tag)
                begin
                    cache.valid_array[index]=1;
                    cache.tag_array[index]=1;
                    cache.cache[index]=ram.ram[prev_address];
                end
                temp_out=cache.cache[index];
            end
        end
    end

    assign out=temp_out;
endmodule