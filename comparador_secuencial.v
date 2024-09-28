module comparador_secuencial (
    input wire [7:0] A,    // Primer número a comparar
    input wire [7:0] B,    // Segundo número a comparar
    input wire clk,        // Reloj
    output reg q           // Salida: 1 cuando A > B
);

    always @(posedge clk) begin
        if (A > B) begin
            q <= 1'b1;
        end else begin
            q <= 1'b0;
        end
    end

endmodule