! This program executes pow as a test program using the LC 2200 calling convention
! Check your registers ($v0) and memory to see if it is consistent with this program

                                              !Imm (assuming 8 bit, please sign extend)

main:   addi $t0, $zero, 10
        addi $t1, $zero, 3
        sw   $t0, -2($t1)
        halt
        nand $t2, $t0, $t1
        skpne $t0, $t0
        add  $s0, $t0, $t1
        goto other
        addi $t0, $zero, 50
        halt

other:  skpne $t0, $t1
        addi $t0, $zero, 100
        !lw   $s1, 0($t1)
        lea  $at, shit
        call $at
        halt

shit:   addi $t1, $zero, 5
        !lw   $v0, 0($t1)
        halt
        ret
