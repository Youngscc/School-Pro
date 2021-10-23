`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 19:06:14
// Design Name: 
// Module Name: compare
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


module compare(
    cd1,cd2,cd3,cd4,num1,num2,num3,num4,result
    );
    input [7:0]cd1;
    input [7:0]cd2;
    input [7:0]cd3;
    input [7:0]cd4;
    input [7:0]num1;
    input [7:0]num2;
    input [7:0]num3;
    input [7:0]num4;
    output result;
    wire result;
    assign result = (num1 == cd1) && (num2 == cd2) && (num3 == cd3) && (num4 == cd4);
endmodule
