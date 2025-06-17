START:  LD  MAX
        JZ  FIN
        SUB UNO
        ST  MAX
        LD  PREV
        ST  OUT
        ADD NEXT
        ST  TMP
        LD  NEXT
        ST  PREV
        LD  TMP
        ST  NEXT
        JMP START
FIN:    HLT
PREV:   1
NEXT:   1
TMP:    
MAX:    10
UNO:    1
