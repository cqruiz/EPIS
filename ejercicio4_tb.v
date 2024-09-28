`timescale 1ns / 1ps
module ejercicio4_tb;
  reg x=0;
  reg clk=0;
  wire z;

    always begin
        #1 clk = !clk;
    end

    ejercicio4 ej40 (.clk(clk), .x(x), .z(z));

    initial begin
        $dumpfile("ejercicio4_tb.vcd");
        $dumpvars;
#2 
x=0;
#2 
x=1;
#2 
x=0;
#2 
x=0;
#2 
x=1;
#100
x=1;
#2 
x=1;
#2 
x=1;
#2 
x=1;
#100
x = 0;

    
    // Fin de la simulación
    #1000 $finish;
    end
endmodule