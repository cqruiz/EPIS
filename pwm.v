module pwm (
    input wire [7:0] period,  // Período de la señal PWM (7 bits)
    input wire [7:0] duty,    // Ciclo de trabajo de la señal PWM (7 bits)
    input wire clk,           // Reloj de entrada
    output reg pwm_out            // Salida PWM (1 bit)
);

    reg [7:0] counter;        // Contador para la señal PWM

    always @(posedge clk) begin
        if (counter < period) begin
            counter <= counter + 1;
        end else begin
            counter <= 0;
        end

        if (counter < duty) begin
            pwm_out <= 1;
        end else begin
            pwm_out <= 0;
        end
    end

endmodule