! AUTHOR: Jake Vollkommer
!============================================================
! CS 2200 Homework 2
!
! Please do not change main's functionality,
! except to change the argument for fibonacci or to meet your
! calling convention
!============================================================

main:
    la      $sp, stack            ! load ADDRESS of stack label into $sp
    lw      $sp, 0($sp)           ! load address of stack from the stack label
    la      $at, fibonacci        ! load address of factorial label into $at
    addi    $a0, $zero, 6         ! $a0 = 5, the number n to compute fibonacci(n)
    jalr    $at, $ra              ! jump to fibonacci, set $ra to return addr
    halt                          ! when we return, just halt

fibonacci:
    addi    $sp, $sp , -3         ! allocate 3 spaces on stack
    sw      $a0, 2($sp)           ! store argument on the stack
    sw      $ra, 0($sp)           ! store return address on stack

    beq     $a0, $zero, base0     ! branch to base0 if n == 0
    addi    $t0, $zero, 1         ! store 1 into t1 to check base case n == 1
    beq     $a0, $t0, base1       ! branch to base1 if n == 1

    beq     $zero, $zero, fib_rec ! jump to recursion

base0:
    add     $v0, $zero, $zero     ! load 0 into v0 to return
    beq     $zero, $zero, return
base1:
    addi    $v0, $zero, 1         ! load 1 into v0 to return
    beq     $zero, $zero, return

fib_rec:
    addi    $a0, $a0, -1          ! decrement a0 to pass new arg fib(n - 1)
    jalr    $at, $ra              ! call fib(n-1)

    sw      $v0, 1($sp)           ! store return value on the stack
    lw      $a0, 2($sp)           ! load a0 from the stack

    addi    $a0, $a0, -2          ! decrement a0 to pass new arg fib(n - 2)
    jalr    $at, $ra              ! call fib(n-2)

    lw      $t2, 1($sp)           ! load return value from fib(n-1) into t2
    add     $v0, $v0, $t2         ! store fib(n-1) + fib(n-2) in v0

return:
    lw   $ra, 0($sp)              ! return address
    addi $sp, $sp, 3              ! pop 3 off the stack
    jalr $ra, $t1                 ! return

stack: .word 0x4000               ! the stack begins here (for example, that is)
