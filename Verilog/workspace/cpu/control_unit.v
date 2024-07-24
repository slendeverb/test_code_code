module control_unit (
    clk,
    rst,
    en,
    en_alu,
    en_ram_out,
    ins,
    offset_addr,
    en_ram_in,
    en_group_pulse,
    en_pc_pulse,
    reg_en,
    alu_in_sel,
    alu_func,
    pc_ctrl
);
    /*
        en: Control_Unit的使能信号
        en_alu: alu的输出使能信号,即用于告诉control unit此时alu有输出
        en_ram_out: RAM的输出使能信号,即用于告诉control unit此时RAM有输出
        ins: 当前的指令
    */
    input clk,rst,en,en_alu,en_ram_out;
    input [15:0] ins;

    /*
        en_ram_in: RAM输入使能,告诉RAM此时有数据输入
        en_group_pulse: 与datapath同步时钟信号?
        en_pc_pulse: 连datapath的en_pc_pulse
        alu_in_sel: 连datapath的alu_in_sel
        offset_addr: 连datapath的offset_addr
        reg_en: 连datapath的reg_en
        alu_func: 连datapath的alu_func
        pc_ctrl: 连datapath的pc_ctrl
    */
    output en_ram_in,en_group_pulse,en_pc_pulse,alu_in_sel;
    output reg [7:0] offset_addr;
    output [3:0] reg_en;
    output [2:0] alu_func;
    output [1:0] pc_ctrl;

    wire [15:0] ir_out;
    wire en_out;

    ir ir1(
        .clk(clk),
        .rst(rst),
        .ins(ins),
        .en_in(en_ram_out),
        .en_out(en_out),
        .ir_out(ir_out)
    );

    state_transition state_transition1(
        .clk(clk),
        .rst(rst),
        .en_in(en),
        .en1(en_out),
        .en2(en_alu),
        .rd(ir_out[11:10]),
        .opcode(ir_out[15:12]),
        .en_fetch_pulse(en_ram_in),
        .en_group_pulse(en_group_pulse),
        .en_pc_pulse(en_pc_pulse),
        .pc_ctrl(pc_ctrl),
        .reg_en(reg_en),
        .alu_in_sel(alu_in_sel),
        .alu_func(alu_func)
    );

    always @(en_out or ir_out) begin
        offset_addr=ir_out[7:0];
    end
endmodule