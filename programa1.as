        LD  IN
START:  JZ  FIN
        ST  OUT
        SUB UNO
        JMP START
FIN:    HLT
UNO:    1
