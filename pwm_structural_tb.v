`timescale 1ns/1ps

module pwm_structural_tb;

    // Entradas del DUT (Device Under Test)
    reg clk;
    reg [7:0] period;
    reg [7:0] duty;
    reg enable;

    // Salidas del DUT
    wire pwm;

    // Instancia del módulo pwm_structural
    pwm_structural UUT (
        .clk(clk),
        .period(period),
        .duty(duty),
        .pwm(pwm),
        .enable(enable)
    );

    // Parámetros para las pruebas
    real pwm_frequency;  // Frecuencia PWM en Hz
    real pwm_percent;    // Ciclo de trabajo PWM en porcentaje
    integer clk_frequency = 50000000; // Frecuencia del reloj en Hz (50 MHz)

    // Generación de la señal de reloj (50 MHz)
    always #10 clk = ~clk;

    // Procedimiento de testeo
    initial begin
        // Inicializar señales
        clk = 0;

        enable = 0;
        #50;
        enable = 1;  // Pulso en el enable para activar el contador
        
        
        // Configuración 1: Frecuencia PWM de 10 kHz, Ciclo de trabajo del 50%
        pwm_frequency = 5000;   // Frecuencia PWM = 5 kHz
        pwm_percent = 25.0;     // Ciclo de trabajo = 50%
        period = clk_frequency / pwm_frequency;  // Calcular el período
        duty = (period * pwm_percent) / 100;     // Calcular el duty cycle

        #20000;

        // Configuración 2: Frecuencia PWM de 5 kHz, Ciclo de trabajo del 75%
        pwm_frequency = 5000;   // Frecuencia PWM = 5 kHz
        pwm_percent = 50.0;     // Ciclo de trabajo = 75%
        period = clk_frequency / pwm_frequency;  // Calcular el período
        duty = (period * pwm_percent) / 100;     // Calcular el duty cycle

        #20000;

        // Configuración 3: Frecuencia PWM de 20 kHz, Ciclo de trabajo del 25%
        pwm_frequency = 5000;   // Frecuencia PWM = 5 kHz
        pwm_percent = 75.0;     // Ciclo de trabajo = 25%
        period = clk_frequency / pwm_frequency;  // Calcular el período
        duty = (period * pwm_percent) / 100;     // Calcular el duty cycle

        #20000;

        // Configuración 4: Frecuencia PWM de 10 kHz, Ciclo de trabajo del 50%
        pwm_frequency = 10000;   // Frecuencia PWM = 10 kHz
        pwm_percent = 25.0;     // Ciclo de trabajo = 50%
        period = clk_frequency / pwm_frequency;  // Calcular el período
        duty = (period * pwm_percent) / 100;     // Calcular el duty cycle

        #20000;

        // Configuración 5: Frecuencia PWM de 5 kHz, Ciclo de trabajo del 75%
        pwm_frequency = 10000;   // Frecuencia PWM = 10 kHz
        pwm_percent = 50.0;     // Ciclo de trabajo = 75%
        period = clk_frequency / pwm_frequency;  // Calcular el período
        duty = (period * pwm_percent) / 100;     // Calcular el duty cycle

        #20000;

        // Configuración 6: Frecuencia PWM de 20 kHz, Ciclo de trabajo del 25%
        pwm_frequency = 10000;   // Frecuencia PWM = 10 kHz
        pwm_percent = 75.0;     // Ciclo de trabajo = 25%
        period = clk_frequency / pwm_frequency;  // Calcular el período
        duty = (period * pwm_percent) / 100;     // Calcular el duty cycle

        #20000;



        $finish;
    end

    // Guardar resultados en un archivo para visualización en GTKWave
    initial begin
        $dumpfile("pwm_structural_tb.vcd");
        $dumpvars;
    end

endmodule
