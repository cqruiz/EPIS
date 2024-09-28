module ejercicio4(
    input x, clk, reset,
    output reg z
);

parameter A = 3'b000,
          B = 3'b001,
          C = 3'b010,
          D = 3'b011,
          E = 3'b100;

reg [2:0] current_state=A, next_state=A;

always @(posedge clk, posedge reset)
begin
    if(reset)
        current_state <= A;
    else
        current_state <= next_state;
end

always @(current_state, x)
begin
    z = 0;
    case(current_state)
        A: 
            if (x == 1)
                next_state = A;
            else
                next_state = B;
        B: 
            if (x == 1)
                next_state = C;
            else
                next_state = B;
        C: 
            if (x == 1)
                next_state = B;
            else
                next_state = D;
        D: 
            if (x == 1)
                next_state = C;
            else
                next_state = E;
        E: 
            if (x == 1)
            begin
                z = 1;
                next_state = A;
            end
            else
                next_state = B;
    endcase
end
endmodule
