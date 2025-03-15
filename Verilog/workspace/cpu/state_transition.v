module state_transition (
    clk,
    rst,
    en_in,
    en1,
    en2,
    rd,
    opcode,
    en_fetch_pulse,
    en_group_pulse,
    en_pc_pulse,
    pc_ctrl,
    reg_en,
    alu_in_sel,
    alu_func
);
    input clk,rst;
    input en_in;//表示此时有指令需要处理,从空闲状态转为取指状态
    input en1;//接收指令寄存器的使能,只有有指令来临时,才会进行状态转移
    input en2;//接收alu的输出
    input [1:0] rd;//destination register目的寄存器
    input [3:0] opcode;//指令中的操作码,不同的操作码对应不同的next_state

    /*
        en_ram_in: RAM输入使能,告诉RAM此时有数据输入
        en_group_pulse: 与datapath同步时钟信号?
        en_pc_pulse: 连datapath的en_pc_pulse
        alu_in_sel: 连datapath的alu_in_sel
        reg_en: 连datapath的reg_en
        alu_func: 连datapath的alu_func
        pc_ctrl: 连datapath的pc_ctrl
    */
    output reg en_fetch_pulse;
    output reg en_group_pulse;
    output reg en_pc_pulse;
    output reg [1:0] pc_ctrl;
    output reg [3:0] reg_en;
    output reg alu_in_sel;
    output reg [2:0] alu_func;

    reg en_fetch_reg,en_fetch;
    reg en_group_reg,en_group;//group reg的写控制信号和读控制信号
    reg en_pc_reg,en_pc;
    reg [3:0] current_state,next_state;

    parameter Initial = 4'b0000;
    parameter Fetch = 4'b0001;
    parameter Decode = 4'b0010;
    parameter Execute_Moveb = 4'b0011;
    parameter Execute_Add = 4'b0100;
    parameter Execute_Sub = 4'b0101;
    parameter Execute_And = 4'b0110;
    parameter Execute_Or = 4'b0111;
    parameter Execute_Jump = 4'b1000;
    parameter Write_back = 4'b1001;

    always @(posedge clk or negedge rst) begin //有限状态机的现态和次态的转移
        if(!rst) begin
            current_state<=Initial;
        end
        else begin
            current_state<=next_state;
        end
    end

    always @(current_state or en_in or en1 or en2 or opcode) begin
        case (current_state)
            Initial: begin
                if(en_in) begin
                    next_state=Fetch;
                end
                else begin
                    next_state=Initial;
                end
            end
            Fetch: begin
                if(en1) begin
                    next_state=Decode;
                end
                else begin
                    next_state=current_state;
                end
            end
            Decode: begin
                case (opcode)
                    4'b0000: next_state=Execute_Moveb;
                    4'b0010: next_state=Execute_Add;
                    4'b0101: next_state=Execute_Sub;
                    4'b0111: next_state=Execute_And;
                    4'b1001: next_state=Execute_Or;
                    4'b1010: next_state=Execute_Jump;
                    default: next_state=current_state;
                endcase
            end
            Execute_Moveb: begin
                if(en2) begin //如果此时alu确实有数输出,证明这个状态完成了
                    next_state=Write_back;
                end
                else begin
                    next_state=current_state;
                end
            end
            Execute_Add: begin
                if(en2) begin //如果此时alu确实有数输出,证明这个状态完成了
                    next_state=Write_back;
                end
                else begin
                    next_state=current_state;
                end
            end
            Execute_Sub: begin
                if(en2) begin //如果此时alu确实有数输出,证明这个状态完成了
                    next_state=Write_back;
                end
                else begin
                    next_state=current_state;
                end
            end
            Execute_And: begin
                if(en2) begin //如果此时alu确实有数输出,证明这个状态完成了
                    next_state=Write_back;
                end
                else begin
                    next_state=current_state;
                end
            end
            Execute_Or: begin
                if(en2) begin //如果此时alu确实有数输出,证明这个状态完成了
                    next_state=Write_back;
                end
                else begin
                    next_state=current_state;
                end
            end
            Execute_Jump: next_state=Fetch;
            Write_back: next_state=Fetch;
            default: next_state=current_state;
        endcase
    end

    //用于控制输出信号
    always @(rst or next_state) begin
        if(!rst) begin
            en_fetch=1'b0;
            en_group=1'b0;
            en_pc=1'b0;
            pc_ctrl=2'b00;
            reg_en=4'b0000;
            alu_in_sel=1'b0;
            alu_func=3'b000;
        end
        else begin
            case (next_state)
                Initial: begin
                    en_fetch=1'b0;
                    en_group=1'b0;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b000;
                end
                Fetch: begin
                    en_fetch=1'b1;//此时需要取指
                    en_group=1'b0;
                    en_pc=1'b1;
                    pc_ctrl=2'b01;//取下一个指令
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b000;
                end
                Decode: begin
                    en_fetch=1'b0;
                    en_group=1'b0;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b000;
                end
                Execute_Moveb: begin
                    en_fetch=1'b0;
                    en_group=1'b1;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b000;
                end
                Execute_Add: begin
                    en_fetch=1'b0;
                    en_group=1'b1;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b001;
                end
                Execute_Sub: begin
                    en_fetch=1'b0;
                    en_group=1'b1;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b001;
                end
                Execute_And: begin
                    en_fetch=1'b0;
                    en_group=1'b1;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b001;
                end
                Execute_Or: begin
                    en_fetch=1'b0;
                    en_group=1'b1;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b001;
                end
                Execute_Jump: begin
                    en_fetch=1'b0;
                    en_group=1'b1;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b001;
                end
                Write_back: begin
                    case (rd)
                        2'b00: reg_en=4'b0001;
                        2'b01: reg_en=4'b0010;
                        2'b10: reg_en=4'b0100;
                        2'b11: reg_en=4'b1000;
                        default: reg_en=4'b0000;
                    endcase
                end
                default: begin
                    en_fetch=1'b0;
                    en_group=1'b0;
                    en_pc=1'b0;
                    pc_ctrl=2'b00;
                    reg_en=4'b0000;
                    alu_in_sel=1'b0;
                    alu_func=3'b000;
                end
            endcase
        end
    end

    always @(posedge clk or negedge rst) begin
        if(!rst) begin
            en_fetch_reg<=1'b0;
            en_pc_reg<=1'b0;
            en_group_reg<=1'b0;
        end
        else begin
            en_fetch_reg<=en_fetch;
            en_pc_reg<=en_pc;
            en_group_reg<=en_group;
        end
    end

    always @(en_fetch or en_fetch_reg) begin
        en_fetch_pulse=en_fetch&(~en_fetch_reg);
    end

    always @(en_pc or en_pc_reg) begin
        en_pc_pulse=en_pc&(~en_pc_reg);//此时需要读入下一条指令,且当此时指令寄存器中为空时,请求下一条指令
    end

    always @(en_group or en_group_reg) begin
        en_group_pulse=en_group&(~en_group_reg);
    end
endmodule