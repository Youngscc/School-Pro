`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/18 11:59:15
// Design Name: 
// Module Name: ShowTime
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


module ShowTime(
    clk,tm1,tm2,tm3,Figure1,DN1
    );
    input clk;
    input [9:0]tm1;
    input [9:0]tm2;
    input [9:0]tm3;
    output reg[7:0]Figure1;
    output reg[3:0]DN1;
    wire [7:0]sta5;
    wire [7:0]sta6;
    wire [7:0]sta7;
    reg [31:0]counter;
    initial
        begin
            Figure1 = 0;
            DN1 = 4'b0010;
            counter = 0;
        end
    ShowLight_10 T5(clk, tm1, sta5);
    ShowLight_10 T6(clk, tm2, sta6);
    ShowLight_10 T7(clk, tm3, sta7);
    
    always@(posedge clk)
        counter = counter+1;
    
    always@(posedge counter[15])
    begin
        
        DN1 = DN1<<1;
        if (DN1 == 0)
            DN1 = 4'b0010;
        if (DN1 == 4'b0010) Figure1 = sta5+8'b10000000;
        if (DN1 == 4'b0100) Figure1 = sta6;
        if (DN1 == 4'b1000) Figure1 = sta7;
    end
endmodule
