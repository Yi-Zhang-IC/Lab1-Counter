#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char** argv){
    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    auto top = new Vcounter;
    //init trace dump
    Verilated::traceEverOn(true);
    auto tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // int Vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab1:counter");

    vbdSetMode(1);// set the mod to ONE-SHOT behaviour
    
    //initializs simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 1;
    top->load_val = 0;
    top->load_en = 0;

    //run simulation for many clock sycles

    for(int i=0; i<30000; i++){
        
        //dump variables into VCD file and toggle clock
        for(int clk=0; clk<2; clk++){
            tfp->dump(2*i+clk);//unit is in ps!!!
            top->clk = !top->clk;
            top->eval();
        }

        // ++++ Send count value to Vbuddy

        // vbdPlot(top->count, 0, 255); // a better way to see how it works

        vbdHex(4,(int(top->count) >> 12) & 0xF);
        vbdHex(3,(int(top->count) >> 8) & 0xF);
        vbdHex(2,(int(top->count) >> 4) & 0xF);
        vbdHex(1,(int(top->count) ) & 0xF);
        // ---- end of Vbuddy output section

        // change input stimuli
        top->rst = i == 0;

        top->load_val = vbdValue();

        top->load_en = vbdFlag();

        if (Verilated::gotFinish())exit(0);
    }

    vbdClose(); //++++
    tfp->close();
    exit(0);
}
