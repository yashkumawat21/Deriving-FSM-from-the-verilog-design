module my_fsm (clk, rst, start, skip3, wait3, Zot);
input clk, rst, start, skip3, wait3;
output [2:0] Zot; // Zot is declared reg so that it can
reg [2:0] Zot; // be assigned in an always block.
parameter state0=0, state1=1, state2=2, state3=3;
reg [1:0] state, nxt_st;
always @ (state or start or skip3 or wait3)
begin : next_state_logic //Name of always procedure.
case (state)
state0: 
begin
if (start) nxt_st = state1 ;
else nxt_st = state0 ;
end 
state1: begin
nxt_st = state2 ;
end
state2: begin
if (skip3) nxt_st = state0 ;
else nxt_st = state3 ;
end
state3: begin
if (wait3) nxt_st = state3 ;
else nxt_st = state0 ;
end
default: nxt_st = state0 ;
endcase // default is optional since all 4 cases are
end // covered specifically. Good practice says uses it.
always @(posedge clk or posedge rst) 
begin : register_generation
if (rst) state = state0; 
else state = nxt_st;
end
always @(state) begin : output_logic
case (state)
state0: Zot = 3’b000;
state1: Zot = 3’b101;
state2: Zot = 3’b111;
state3: Zot = 3’b001;
default: Zot = 3’b000;// default avoids latches
endcase
end
endmodule