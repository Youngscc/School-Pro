`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/18 11:57:11
// Design Name: 
// Module Name: Timer
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


module Timer(
    clk,start,Figure1,DN1,ini
    );
    input clk;
    input start;
    reg [9:0]tm1;
    reg [9:0]tm2;
    reg [9:0]tm3;
    reg [20:0]cntt;
    output reg ini;
    output [7:0]Figure1;
    output [3:0]DN1;
    ShowTime ST(clk,tm1,tm2,tm3,Figure1,DN1);

    initial
    begin
        tm1=32;
        tm2=1;
        tm3=1;
        cntt = 0;
        ini = 0;
    end
    
    always@(negedge clk)
    begin
        if (!start) ini = 0;
        cntt = cntt+1;
        if (cntt == 1000000)
        begin
            cntt = 0;
            if (!start)
            begin
                tm1 = 32;
                tm2 = 1;
                tm3 = 1;
            end
            else
            begin
                tm3 = tm3>>1;
                if (!tm3)
                begin
                    tm3 = 10'b1000000000;
                    tm2 = tm2>>1;
                    if (!tm2)
                    begin
                        tm2 = 10'b1000000000;
                        tm1 = tm1>>1;
                        if (!tm1)
                        begin
                            ini = 1;
                        end
                    end
                end
            end
        end
    end
endmodule
