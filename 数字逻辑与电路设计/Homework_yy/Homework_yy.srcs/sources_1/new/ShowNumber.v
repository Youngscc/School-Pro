`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 12:54:57
// Design Name: 
// Module Name: ShowNumber
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


module ShowNumber(
    clk,cd1,cd2,cd3,cd4,Figure0,DN0
    );
    input clk;
    input [7:0]cd1;
    input [7:0]cd2;
    input [7:0]cd3;
    input [7:0]cd4;
    output reg[7:0]Figure0;
    output reg[3:0]DN0;
    wire [7:0]sta1;
    wire [7:0]sta2;
    wire [7:0]sta3;
    wire [7:0]sta4;
    reg [31:0]counter;
    initial
        begin
            Figure0 = 0;
            DN0 = 4'b0001;
            counter = 0;
        end
    ShowLight_8 T1(clk, cd1, sta1);
    ShowLight_8 T2(clk, cd2, sta2);
    ShowLight_8 T3(clk, cd3, sta3);
    ShowLight_8 T4(clk, cd4, sta4);
    
    always@(posedge clk)
        counter = counter+1;
    
    always@(posedge counter[15])
    begin
        DN0 = DN0<<1;
        if (DN0 == 0)
            DN0 = 4'b0001;
        if (DN0 == 4'b0001) Figure0 = sta1;
        if (DN0 == 4'b0010) Figure0 = sta2;
        if (DN0 == 4'b0100) Figure0 = sta3;
        if (DN0 == 4'b1000) Figure0 = sta4;

    end
endmodule
