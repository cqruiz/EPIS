`timescale 1ns / 1ps
module ffjk_tb;
    reg j, k, clk=0;
    wire q, qn;

    always begin
        #1 clk = !clk;
    end

    ffjk jk0 ( .j(j),
               .k(k),
               .clk(clk),
               .q(q),
               .qn(qn)
             );

    initial begin
        $dumpfile("ffjk_tb.vcd");
        $dumpvars;

        #0 j = 0; k = 0;
        #5 j = 0; k = 1;
        #5 j = 1; k = 0;
        #5 j = 1; k = 1;
        #15 $finish;
    end
endmodule