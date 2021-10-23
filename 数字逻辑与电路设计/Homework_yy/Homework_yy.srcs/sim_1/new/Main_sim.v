`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 16:53:04
// Design Name: 
// Module Name: Main_sim
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


module Main_sim(

    );
    reg clk;
    reg [7:0]cd;
    wire [7:0]Figure0;
    wire [7:0]Figure1;
    wire [3:0]DN0;
    wire [3:0]DN1;
    wire sta1;
    wire sta2;
    wire [5:0]lsd2;
    wire [7:0]lsd;
    reg reset,Maintain;
    Main LOCK(clk,cd,Figure0,Figure1,DN0,DN1,sta1,sta2,lsd,reset,Maintain,lsd2);
    initial
        begin
            cd = 0;
            clk = 0;
            Maintain = 0;
            reset = 0;
        end
    always #1
        clk = clk + 1;
    always #40000
    begin
        #5000 cd = 8'b000_000_01;
        #5000 cd = 8'b000_000_00;
        #5000 cd = 8'b000_000_01;
        #5000 cd = 8'b000_000_00;
        #5000 cd = 8'b000_000_01;
        #5000 cd = 8'b000_000_00;
        #5000 cd = 8'b000_000_01;
        #5000 cd = 8'b000_000_00;
        #5000 Maintain = 1;
        #5000 cd = 8'b000_001_00;
        #5000 cd = 8'b000_000_00;
        #5000 cd = 8'b000_001_00;
        #5000 cd = 8'b000_000_00;
        #5000 cd = 8'b000_001_00;
        #5000 cd = 8'b000_000_00;
        #5000 cd = 8'b000_001_00;
        #5000 cd = 8'b000_000_00;
    end
endmodule
