`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/16 23:18:24
// Design Name: 
// Module Name: Main
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


module Main(
    clk,psd,Figure0,Figure1,DN0,DN1,sta1,sta2,lsd,reset,maintain,lsd2
    );
    input clk;
    input [7:0]psd;
    input reset;
    input maintain;
    output [7:0]Figure0;
    output [7:0]Figure1;
    output [3:0]DN0;
    output [3:0]DN1;
    output [7:0]lsd;
    output [5:0]lsd2;
    output reg sta1;
    output reg sta2;
    reg [7:0]cd1;
    reg [7:0]cd2;
    reg [7:0]cd3;
    reg [7:0]cd4;    
    reg [7:0]num1;
    reg [7:0]num2;
    reg [7:0]num3;
    reg [7:0]num4;
    reg change,open,start,init,clk_1ms,clk_1;
    reg [3:0]count;
    reg [20:0]cnt;
    reg First;
    reg Maintain;
    reg lsdpower1,lsdpower2,lsdpower3,changeopt;
    wire status1,status2;
    wire result,ini;
    
    ShowNumber SN(clk,cd1,cd2,cd3,cd4,Figure0,DN0);
    compare CP(cd1,cd2,cd3,cd4,num1,num2,num3,num4,result);
    ShowStatus SS(clk,status1,status2,Maintain,open);
    Timer T(clk,start,Figure1,DN1,ini);
    LSD Lsd(clk,lsdpower1,lsdpower2,lsdpower3,lsd,lsd2);
    
    initial
    begin
        cd1=0;
        cd2=0;
        cd3=0;
        cd4=0;

        num1=1;
        num2=1;
        num3=1;
        num4=1;
        change=0;
        count=0;
        open=0;
        init=0;
        cnt=0;
        clk_1ms=0;
        clk_1=0;
        sta1=0;
        sta2=1;
        start = 0;
        lsdpower1 = 0;
        lsdpower2 = 0;
        lsdpower3 = 0;
        changeopt = 0;
        First = 0;
        Maintain = 0;
    end
    
    always@(posedge clk)
    begin
        cnt = cnt+1;
        if (cnt == 100000)
            begin
                cnt = 0;
                clk_1ms = clk_1ms^1;
            end
    end
    
    always@(negedge clk_1ms)
    begin
        if (psd > 0)
            change = 1;
        else 
            change = 0;
        if(ini) change = 0;
    end
   
always@(posedge clk_1ms)
begin
    if (reset)
        begin
            cd1<=0;
            cd2<=0;
            cd3<=0;
            cd4<=0;
            start = 0;
            count = 0;
            First = 0;
            open = 0;
            lsdpower1 = 0;
            lsdpower2 = 0;
            lsdpower3 = 0;
            Maintain = 0;
            changeopt = 0;
        end
    if (maintain && open)
    begin
        cd1<=0;
        cd2<=0;
        cd3<=0;
        cd4<=0;
        Maintain = 1;
        lsdpower3 = 1;
        count = 0;
    end
    sta1 = status1;
    sta2 = status2;
    if (ini)
    begin
        cd1<=0;
        cd2<=0;
        cd3<=0;
        cd4<=0;
        start = 0;
        count = 0;
        lsdpower1 = 1;
        lsdpower2 = 0;
    end
    if (start)
    begin
        lsdpower1 = 0;
        lsdpower2 = 0;
    end
    if (First && !start)
        if (result)
            begin
                lsdpower2 = 1;
                lsdpower1 = 0;
            end
        else
            begin
                lsdpower1 = 1;
                lsdpower2 = 0;
            end
    
    if (!Maintain)
        if (result && !start)
            begin 
                open = 1;
                First = 0;
            end
        else open = 0;
    else open = 1;
    if (!change) init=0;        
    if (change && !init && !Maintain)
    begin
        if (!open)
        begin
            init = 1;
            if (count == 0)
            begin
                cd1 <= psd;
                cd2 <= 0;
                cd3 <= 0;
                cd4 <= 0;
                start = 1;
                lsdpower1 = 0;
            end
            else if (count == 1)
                cd2 <= psd;
            else if (count == 2)
                cd3 <= psd;
            else if (count == 3)
                cd4 <= psd;
            count = count+1;
            if (count == 4)
            begin
                count = 0;
                start = 0;
                First = 1;
            end
        end
    end
    
    if ((change || count == 4) && !init && Maintain && !changeopt)
        begin
            init = 1;
            if (count == 0)
            begin
                cd1 <= psd;
            end
            else if (count == 1)
            begin
                cd2 <= psd;
            end
            else if (count == 2)
            begin
                cd3 <= psd;
            end
            else if (count == 3)
            begin
                cd4 <= psd;
            end
            
            else if (count == 4)
            begin
                count = 0;
                num1 = cd1;
                num2 = cd2;
                num3 = cd3;
                num4 = cd4;
                lsdpower3 = 0;
                changeopt = 1; 
            end
            count = count+1;
        end
end

endmodule