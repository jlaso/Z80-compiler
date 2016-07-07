#ifndef CPU_H
#define CPU_H

#include "general.h"
#include "Memory.h"
#include <string>

using namespace std;

class Cpu
{
private:

    /**
     * REGISTERS
     */

    // MAIN REGISTERS
    record16 _AF;
    word* AF = &_AF.rr;
    byte* A  = &_AF.r.hi;
    byte* F  = &_AF.r.lo;
    record16 _BC;
    word* BC = &_BC.rr;
    byte* B  = &_BC.r.hi;
    byte* C  = &_BC.r.lo;
    record16 _DE;
    word* DE = &_DE.rr;
    byte* D  = &_DE.r.hi;
    byte* E  = &_DE.r.lo;
    record16 _HL;
    word* HL = &_HL.rr;
    byte* H  = &_HL.r.hi;
    byte* L  = &_HL.r.lo;

    // ALTERNATE REGISTERS
    record16 _AF_;
    word* AF_ = &_AF_.rr;
    byte* A_  = &_AF_.r.hi;
    byte* F_  = &_AF_.r.lo;
    record16 _BC_;
    word* BC_ = &_BC_.rr;
    byte* B_  = &_BC_.r.hi;
    byte* C_  = &_BC_.r.lo;
    record16 _DE_;
    word* DE_ = &_DE_.rr;
    byte* D_  = &_DE_.r.hi;
    byte* E_  = &_DE_.r.lo;
    record16 _HL_;
    word* HL_ = &_HL_.rr;
    byte* H_  = &_HL_.r.hi;
    byte* L_  = &_HL_.r.lo;

    // Program Counter and Stack Pointer
    word PC, SP;

    // Index Registers
    record16 _IX;
    word* IX = &_IX.rr;
    byte* Ix = &_IX.r.hi;
    byte* X  = &_IX.r.lo;
    record16 _IY;
    word* IY = &_IY.rr;
    byte* Iy = &_IY.r.hi;
    byte* Y  = &_IY.r.lo;

    // Special registers
    byte I,R;
    bool IFF1,IFF2;
    byte IM;

    /**
     * auxiliary variables
     */

    char currentInstruction[250] = "\0";
    static const int align = 25;     // to align the PC + opcodes to the left in the currentInstruction string
    long cycles;   // cycles consumed by the currentInstruction in order to adjust the real time consumed
    byte opcode; // current opcode that is been decoded and executed
    byte registersBank;
    byte bPrev, bAfter;
    word wPrev, wAfter;
    int offset;
    bool cc;

    /**
     * FREQUENCY
     */
    unsigned long clock_herzs;
    double clock_cycle;
    long start_clock;
    double current_clock;

    /**
     * Memory
     */
    Memory memory;
    byte readByte(word addr);
    word readWord(word addr);

    /**
     * methods that executes instructions
     */
    int jp_nn();
    void add_a_r(byte r);
    void adc_a_r(byte r);
    void sub_a(byte r);

    /**
     * internal methods
     */
    void handleInterrupts();

    /**
     * FLAG's stuff
     */
    void setFlags(byte result, int sign, int zero, int half_carry, int par_over, int add_sub, int carry);

    static const byte SIGN_FLAG     = 0b10000000;
    static const byte ZERO_FLAG     = 0b01000000;
    static const byte ADD_SUB_FLAG  = 0b00010000;
    static const byte PAR_OV_FLAG   = 0b00000100;
    static const byte CARRY_FLAG    = 0b00000001;
    static const word H_CARRY_FLAG = 0b100000000;   // fake flag to control other behaviour of H

    //byte* r[8] = { &_BC.r.hi,&_BC.r.lo,&_DE.r.hi,&_DE.r.lo,&_HL.r.hi, 0, &_HL.r.lo, &_AF.r.hi };
    //char * rName[8] = { "B", "C", "D", "E", "H", "L", "(HL)", "A" };

    char* rName(byte rCode);
    char* rrName(byte rCode);
    byte r(byte rCode);
    char* ccName(byte rCode);

public:

    Cpu(unsigned long clock_freq);
    void attachMemory(Memory memory);
    void run(word startAddress);
    int step();
    void reset();

    /**
     * INSTRUCTIONS OP_CODES
     */
    static const byte NOP            = 0x00;

    static const byte LD_BC_NN       = 0x01;
    static const byte LD_DE_NN       = 0x11;
    static const byte LD_HL_NN       = 0x21;
    static const byte LD_SP_NN       = 0x31;

    static const byte LD_B_N         = 0x06;
    static const byte LD_C_N         = 0x0E;
    static const byte LD_D_N         = 0x16;
    static const byte LD_E_N         = 0x1E;
    static const byte LD_H_N         = 0x26;
    static const byte LD_L_N         = 0x2E;
    static const byte LD_HL_CONTENT  = 0x36;
    static const byte LD_A_N         = 0x3E;

    static const byte INC_B          = 0x04;
    static const byte INC_C          = 0x0C;
    static const byte INC_D          = 0x14;
    static const byte INC_E          = 0x1C;
    static const byte INC_H          = 0x24;
    static const byte INC_L          = 0x2C;
    static const byte INC_HL_CONTENT = 0x34;
    static const byte INC_A          = 0x3C;

    static const byte ADD_A_B        = 0x80;
    static const byte ADD_A_C        = 0x81;
    static const byte ADD_A_D        = 0x82;
    static const byte ADD_A_E        = 0x83;
    static const byte ADD_A_H        = 0x84;
    static const byte ADD_A_L        = 0x85;
    static const byte ADD_A_HL_CONTENT= 0x86;
    static const byte ADD_A_A        = 0x87;

    static const byte ADC_A_B        = 0x88;
    static const byte ADC_A_C        = 0x89;
    static const byte ADC_A_D        = 0x8A;
    static const byte ADC_A_E        = 0x8B;
    static const byte ADC_A_H        = 0x8C;
    static const byte ADC_A_L        = 0x8D;
    static const byte ADC_A_HL_CONTENT= 0x8E;
    static const byte ADC_A_A        = 0x8F;

    static const byte SUB_B          = 0x90;
    static const byte SUB_C          = 0x91;
    static const byte SUB_D          = 0x92;
    static const byte SUB_E          = 0x93;
    static const byte SUB_H          = 0x94;
    static const byte SUB_L          = 0x95;
    static const byte SUB_HL_CONTENT = 0x96;
    static const byte SUB_A          = 0x97;

    static const byte LD_B_B         = 0x40;
    static const byte HALT           = 0x76;
    static const byte JP_NN          = 0xC3;
    static const byte JP_Z_NN        = 0xCA;
    static const byte JP_NZ_NN       = 0xC2;
    static const byte JP_C_NN        = 0xDA;
    static const byte JP_NC_NN       = 0xD2;
    static const byte JP_P_NN        = 0xF2;
    static const byte JP_PO_NN       = 0xE2;
    static const byte JP_PE_NN       = 0xEA;
    static const byte JP_M_NN        = 0xFA;

    static const byte DJNZ           = 0x10;

    static const byte EI             = 0xFB;
    static const byte DI             = 0xF3;

};

#endif // CPU_H
