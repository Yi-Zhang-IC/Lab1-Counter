#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    auto top = new Vcounter;
    //init trace dump
    Verilated::traceEverOn(true);
    auto tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");
    
    //initializs simulation inputs
    top->clk = 0;
    top->rst = 1;
    top->en = 0;

    //run simulation for many clock sycles

    for(int cycle=0; cycle<300; cycle++){
        
        //dump variables into VCD file and toggle clock
        for(int i=0; i<2; i++){
            tfp->dump(2*cycle+i);//unit is in ps!!!
            top->clk = !top->clk;
            top->eval();
        }
        top->rst = (cycle<2);
        top->en = ((4<cycle&&cycle<14)||cycle>16);
        if (Verilated::gotFinish())exit(0);
    }
    tfp->close();
    exit(0);
}
