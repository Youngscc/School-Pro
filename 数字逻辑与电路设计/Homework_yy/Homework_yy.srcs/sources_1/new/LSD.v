`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/18 13:56:11
// Design Name: 
// Module Name: LSD
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


module LSD(
    clk,power1,power2,power3,lsd,lsd2
    );
    output reg [7:0]lsd;
    output reg [5:0]lsd2;
    reg [31:0]cnt;
    reg [31:0]cntt;
    input clk,power1,power2,power3;
    initial
    begin
        lsd = 8'b00000000;
        lsd2 = 6'b000000;
        cnt = 0;
        cntt = 0;
    end
    
    always@(posedge clk)
    begin
        cnt = cnt+1;
        if (cnt == 10000000)
        begin
            cnt = 0;
            if (!power1 && !power2) lsd = 0;
            if (power1)
            begin
                if (lsd && lsd != 8'b11111111) lsd = 0;
                lsd = lsd^(8'b11111111);
            end
            if (power2)
            begin
                lsd = lsd >> 1;
                if (!lsd) lsd = 8'b10000000;
            end
        end
    end
    
    always@(posedge clk)
    begin
        if (power3)
        begin
            cntt = cntt+1;
            if (cntt == 10000000)
            begin
                cntt = 0;
                if (lsd2 != 6'b111111 && lsd2 != 6'b000000) lsd2 = 0;
                lsd2 = lsd2^(6'b111111);
            end
        end
        else lsd2 = 0;
    end
endmodule
