// Description: water led
// Revision: V1.1
// Additional Comments:
//1) _i PIN input
//2) _o PIN output
//3) _n PIN active low
//4) _dg debug signal
//5) _r reg delay
//6) _s state machine
//
module run_led(
input sys_clk , //系统时钟
input sys_rst_n, //系统复位，低电平有效
output [1:0] led //LED灯
);
//reg define
reg [25:0] cnt ;
//*****************************************************
//** main code
//*****************************************************
//对计数器的值进行判断，以输出LED的状态
//assign led = (cnt < 26'd2500_0000) ? 2'b01 : 2'b10 ;
assign led = (cnt < 26'd5) ? 2'b01 : 2'b10 ; //仅用于仿真
//计数器在0~5000_000之间进行计数
always @ (posedge sys_clk or negedge sys_rst_n) begin
 if(!sys_rst_n)
 cnt <= 26'd0;
// else if(cnt < 26'd5000_0000)
 else if(cnt < 26'd10) //仅用于仿真
 cnt <= cnt + 1'b1;
 else
 cnt <= 26'd0;
end
endmodule
