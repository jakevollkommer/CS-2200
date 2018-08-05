! This program executes pow as a test program using the LC 2200 calling convention
! Check your registers ($v0) and memory to see if it is consistent with this program

!main:   lea $sp, initsp                       !initialize the stack pointer
!        #lw $sp, 0($sp)                        !finish initialization
!        halt
!
!initsp: .fill 0xA00000

main:   addi $t0, $zero, 14
        halt
