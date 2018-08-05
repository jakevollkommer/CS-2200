! This program executes pow as a test program using the LC 2200 calling convention
! Check your registers ($v0) and memory to see if it is consistent with this program

                                              !Imm (assuming 8 bit, please sign extend)
main:	  lea $sp, initsp                       !initialize the stack pointer
        lw $sp, 0($sp)                        !finish initialization

        lea $a0, BASE                         !load base for pow
        lw $a0, 0($a0)
        lea $a1, EXP                          !load power for pow
        lw $a1, 0($a1)
        lea $at, POW                          !load address of pow
        call $at                              !run pow
        lea $a0, ANS                          !load base for pow
        sw $v0, 0($a0)

        halt

BASE:   .fill 2
EXP:    .fill 10
ANS:    .fill 0                               ! should come out to 1024

POW:    addi $sp, $sp, -1                     ! allocate space for old frame pointer
        sw $fp, 0($sp)
        addi $fp, $sp, 0                      !set new frame pinter
        skpne $a1, $zero                      ! check if $a1 is zero (if not, skip the goto)
        goto RET1                             ! if the power is 0 return 1
        skpne $a0, $zero
        goto RET0                             ! if the base is 0 return 0 (otherwise, the goto was skipped)
        addi $a1, $a1, -1                     ! decrement the power
        lea $at, POW                          ! load the address of POW
        addi $sp, $sp, -2                     ! push 2 slots onto the stack
        sw $ra, -1($fp)                       ! save RA to stack
        sw $a0, -2($fp)                       ! save arg 0 to stack
        call $at                              ! recursively call POW
        add $a1, $v0, $zero                   ! store return value in arg 1
        lw $a0, -2($fp)                       ! load the base into arg 0
        lea $at, MULT                         ! load the address of MULT
        call $at                              ! multiply arg 0 (base) and arg 1 (running product)
        lw $ra, -1($fp)                       ! load RA from the stack
        addi $sp, $sp, 2
        goto FIN                              ! return
RET1:   addi $v0, $zero, 1                    ! return a value of 1
        skple $zero, $v0                      ! convenient use of skple to get to FIN (0 <= 1)
RET0:   add $v0, $zero, $zero                 ! return a value of 0
FIN:	lw $fp, 0($fp)                          ! restore old frame pointer
        addi $sp, $sp, 1                      ! pop off the stack
        ret



MULT:   add $v0, $zero, $zero                 ! zero out return value
        addi $t0, $zero, 1
AGAIN:  add $v0,$v0, $a0                      ! multiply loop
        addi $t0, $t0, 1
        skple $t0, $a1                       ! if $t0 <= $a1, keep looping
        ret
        goto AGAIN                           ! loop again

initsp: .fill 0xA00000
