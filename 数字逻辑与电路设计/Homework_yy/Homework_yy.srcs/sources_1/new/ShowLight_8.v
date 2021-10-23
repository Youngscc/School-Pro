`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/16 23:20:22
// Design Name: 
// Module Name: ShowLight_8
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


module ShowLight_8(
    clk,
    password,
    light
    );
    input clk;
    input [7:0]password;
    output reg [7:0]light;
    
    initial
    begin
        light = 0;
    end
    always@(posedge clk)
    begin
        case(password)
            8'b00_000_001: light=8'b01111110;
            8'b00_000_010: light=8'b00110000;
            8'b00_000_100: light=8'b01101101;
            8'b00_001_000: light=8'b01111001;
            8'b00_010_000: light=8'b00110011;
            8'b00_100_000: light=8'b01011011;
            8'b01_000_000: light=8'b01011111;
            8'b10_000_000: light=8'b01110000;
            8'b00_000_000: light=8'b00000001;
        endcase
    end
endmodule
