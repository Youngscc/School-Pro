`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:41:48
// Design Name: 
// Module Name: SowLinght_8_sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module SowLinght_8_sim(
    clk,cd,num
    );
    reg clk;
    reg [9:0]cd;
    wire [6:0]num;
    ShowLight_8 T(clk,cd,num);
    initial
    begin
        clk = 0;
        cd = 0;
    end
    always #1
        clk = clk + 1;
    always #5
    begin
        cd = 8'b00_000_001;
        #5 cd =8'b00_000_010;
        #5 cd = 8'b00_000_100;
        #5 cd = 8'b00_001_000;
        #5 cd = 8'b00_100_000;
        #5 cd = 8'b01_000_000;
        #5 cd = 8'b10_000_000;
        #5 cd = 8'b00_000_000;
    end
endmodule
