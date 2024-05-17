`timescale 1ns/1ns

module cache_and_ram_tb;
    reg [31:0] address,data;
    reg mode,clk;
    wire [31:0] out;

    cache_and_ram tb(
        .address(address),
        .data(data),
        .mode(mode),
        .clk(clk),
        .out(out)
    );

    always #25 clk=~clk;

    initial begin
        clk=1'b1;

        address=32'b00000000000000000000000000000000;
        data=32'b00000000000000000011100011000000;
        mode=1'b1;

        #200
        address=32'b10100111111001011111101111011100;
        data=32'b00000000000010000000100001010101;
        mode=1'b1;

        #200
        address=32'b00000000000011110100011111010001;
        data=32'b00000001100000110001101100010110;
        mode=1'b1;

        #200
        address=32'b10100111111001011111101111011100;
        data=32'b00000000000000000011100011000000;
        mode=1'b1;

        #200
        address=32'b00000000000011110100011111010001;
        data=32'b00000000000000000011100011000000;
        mode=1'b1;

        #200
        address=32'b00000000000011110100011111010001;
        data=32'b00000000000000000000000000000000;
        mode=1'b0;

        #200
        address=32'b10100111111001011111101111011100;
        data=32'b00000000000000000000000000000000;
        mode=1'b0;

        #200
        address=32'b00000000000000000000000000000000;
        data=32'b00000000000000000011100011000000;
        mode=1'b0;
    end

    // initial begin
    //     $monitor("address = %d data = %d mode = %d out = %d",address%4096,data,mode,out);
    // end

    initial begin
        #2000
        $stop;
    end

    /* 用iverilog+GTKwave进行仿真所需的临时vcd文件 */
    initial begin
        $dumpfile("wave.vcd"); // 指定VCD的名字为wave.vcd, 仿真信息将记录到此文件
        $dumpvars(0,cache_and_ram_tb); // 指定层次数为0, 则tb_ 模块及其下面各层次的所有信号将被记录
    end
endmodule