module contador_8bits(
    input wire enable,    // Habilitación del contador
    input wire reset,     // Resetear la cuenta
    input wire clk,       // Reloj
    output reg [7:0] count =0,   // Salidas del contador
    output wire tc        // Terminal count
);

    // Lógica del contador
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            count <= 8'b00000000;     // Resetear el contador a 0
        end else if (enable) begin
            count <= count + 1;           // Incrementar el contador si está habilitado
        end
    end

    // Generar un pulso de terminal count cuando q alcanza su valor máximo
    assign tc = (count == 8'b11111111) ? 1'b1 : 1'b0;

endmodule