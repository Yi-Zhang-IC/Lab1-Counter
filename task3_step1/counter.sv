module counter#(
    parameter WIDTH = 8
)(
    //interface signals
    input logic clk,    //clock
    input logic rst,    //reset
    input logic en,    //counter enable
    input logic load_en, //load ewnable
    input logic [WIDTH-1:0] load_val, //load value
    output logic [WIDTH-1:0] count   //count output
);

always_ff @(posedge clk)
if(rst) count <={WIDTH{1'b0}};
else if(load_en) count<= load_val;
else count <=count+{{(WIDTH-1){1'b0}},en}; 
 

    
endmodule