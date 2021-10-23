`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/17 20:13:32
// Design Name: 
// Module Name: ShowStatus
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


module ShowStatus(
    clk,sta1,sta2,maintain,open
    );
    input clk,open,maintain;
    output sta1,sta2;
    reg sta1,sta2;
    initial
        begin
            sta1 = 0;
            sta2 = 1;
        end
    
    always@(posedge clk)
    begin
    if (!maintain)
        if (open)
           begin
               sta1 <= 1;
               sta2 <= 0;
           end
        else 
            begin
                sta2 <= 1;
                sta1 <= 0;
            end
    else
    begin
        sta1 <= 1;
        sta2 <= 1;
    end
    end
endmodule
