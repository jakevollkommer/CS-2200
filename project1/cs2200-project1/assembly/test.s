! This program executes pow as a test program using the LC 2200 calling convention
! Check your registers ($v0) and memory to see if it is consistent with this program

!        halt
!

main:   lea     $sp, initsp                       !initialize the stack pointer
        lw      $sp, 0($sp)                        !finish initialization
        addi    $t0, $zero, 14
        add     $t1, $t0, $t0
        nand    $t2, $t0, $t1
        skpne   $t0, $t1
        addi    $s0, $zero, 10
        skple   $t0, $t0
        addi    $t0, $zero, 100
        skple   $t0, $t1
        addi    $t0, $zero, 200
        goto    hi
        addi    $s1, $zero, 20
hi:     lea     $s2, other
        call    $s2
        sw      $s0, 0($s1)
        lw      $s1, 0($s1)
        halt

other:  addi    $s0, $zero, 30
        ret

initsp:    .fill 0xA00000
otheradd:  .fill 0x14
