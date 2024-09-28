`include "comparador_secuencial.v"
`include "contador_8bits.v"

module pwm_structural (
    input wire clk,             // Señal de reloj
    input wire [7:0] period,    // Periodo del PWM
    input wire [7:0] duty,      // Ciclo de trabajo
    input wire enable,          // Habilitación del contador
    output wire pwm             // Salida PWM
);

    // Señales internas
    wire [7:0] count;       // Salida del contador
    wire reset_count;       // Señal de reset generada por el comparador
    wire duty_compare;      // Señal que indica si el contador es menor que el duty

    // Instancia del contador de 8 bits
    contador_8bits u_counter (
        .enable(enable),
        .clk(clk),
        .reset(reset_count),
        .count(count)
    );

    // Instancia del comparador secuencial para comparar contador con periodo
    comparador_secuencial u_comparador_periodo (
        .A(count),
        .B(period),
        .clk(clk),
        .q(reset_count)  // Usamos la salida del comparador como señal de reset para el contador
    );

    // Instancia del comparador secuencial para comparar contador con duty
    comparador_secuencial u_comparador_duty (
        .A(duty),
        .B(count),
        .clk(clk),
        .q(duty_compare)  // Comparar el contador con el duty cycle para generar la salida PWM
    );

    // La salida PWM es alta cuando el contador es menor que el duty
    assign pwm = duty_compare;

endmodule
