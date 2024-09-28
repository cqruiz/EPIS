`timescale 1ns / 1ps

module tb_contador_8bits;

    // Entradas del DUT (Device Under Test)
    reg enable;
    reg reset;
    reg clk;

    // Salidas del DUT
    wire [7:0] count;
    wire tc;

    // Instancia del módulo contador_8bits
    contador_8bits UUT (
        .enable(enable),
        .reset(reset),
        .clk(clk),
        .count(count),
        .tc(tc)
    );

    // Generación de la señal de reloj (50 MHz)
    always #10 clk = ~clk;

    // Procedimiento de testeo
    initial begin
        // Inicializar señales
        clk = 0;
        enable = 0;
        reset = 0;

        // Generar un reset al inicio
        reset = 1;
        #20;
        reset = 0;

        // Habilitar el contador
        enable = 1;
        #200;

        // Deshabilitar el contador
        enable = 0;
        #100;

        // Habilitar el contador de nuevo
        enable = 1;
        #300;

        // Aplicar otro reset mientras está habilitado
        reset = 1;
        #20;
        reset = 0;

        // Continuar por un tiempo más
        #6000;

        // Finalizar la simulación
        $finish;
    end

    // Guardar resultados en un archivo para visualización en GTKWave
    initial begin
        $dumpfile("contador_8bits_tb.vcd");
        $dumpvars(0, tb_contador_8bits);
    end

endmodule
