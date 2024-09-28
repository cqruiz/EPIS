`timescale 1ns/1ps

module comparador_secuencial_b_tb;

    // Entradas del DUT (Device Under Test)
    reg [7:0] A;
    reg [7:0] B;
    reg clk;

    // Salidas del DUT
    wire q;
    wire q_lt;

    // Instancia del módulo comparador_secuencial
    comparador_secuencial_b UUT (
        .A(A),
        .B(B),
        .clk(clk),
        .q(q),
        .q_lt(q_lt)
    );

    // Generación de la señal de reloj (50 MHz)
    always #10 clk = ~clk;

    // Procedimiento de testeo
    initial begin
        // Inicializar señales
        clk = 0;
        A = 8'b00000000;
        B = 8'b00000000;

        // Prueba 1: A > B
        #20;
        A = 8'b00010010;  // A = 18
        B = 8'b00001010;  // B = 10
        #20;

        // Prueba 2: A < B
        A = 8'b00001010;  // A = 10
        B = 8'b00010010;  // B = 18
        #20;

        // Prueba 3: A == B
        A = 8'b00100100;  // A = 36
        B = 8'b00100100;  // B = 36
        #20;

        // Finalizar la simulación
        $finish;
    end

    // Guardar resultados en un archivo para visualización en GTKWave
    initial begin
        $dumpfile("comparador_secuencial_b_tb.vcd");
        $dumpvars;
    
    end

endmodule