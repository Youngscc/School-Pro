`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 23:42:46
// Design Name: 
// Module Name: ShowLight_10
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


module ShowLight_10(
    clk,
    password,
    light
    );
    input clk;
    input [9:0]password;
    output reg [7:0]light;
    
    initial
    begin
        light = 0;
    end
    always@(posedge clk)
    begin
        case(password)
            10'b0_000_000_001: light=8'b01111110;
            10'b0_000_000_010: light=8'b00110000;
            10'b0_000_000_100: light=8'b01101101;
            10'b0_000_001_000: light=8'b01111001;
            10'b0_000_010_000: light=8'b00110011;
            10'b0_000_100_000: light=8'b01011011;
            10'b0_001_000_000: light=8'b01011111;
            10'b0_010_000_000: light=8'b01110000;
            10'b0_100_000_000: light=8'b01111111;
            10'b1_000_000_000: light=8'b01111011;
            10'b0_000_000_000: light=8'b00000001;
        endcase
    end
endmodule
