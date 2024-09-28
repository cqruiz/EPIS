module comparador_secuencial_b (
    input wire [7:0] A,      // Primer número a comparar
    input wire [7:0] B,      // Segundo número a comparar
    input wire clk,          // Reloj
    output reg q,            // Salida: 1 cuando A > B
    output reg q_lt          // Salida: 1 cuando A < B
);

    always @(posedge clk) begin
        if (A > B) begin
            q <= 1'b1;
            q_lt <= 1'b0;
        end else if (A < B) begin
            q <= 1'b0;
            q_lt <= 1'b1;
        end else begin
            q <= 1'b0;
            q_lt <= 1'b0;
        end
    end

endmodule