	.file	"find_max_template.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"The length of the array is %d\n"
	.text
	.globl	Find_Max
	.type	Find_Max, @function
Find_Max:
// prologue - write code for the prologue here
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
// printf("The length of the array is %d\n", n);
// update this code if necessary to print the length of the array
// this block prints the value of register %edi
// initially the parameter n
	subq	$32, %rsp	#allocate 32 bytes for extra spaces of 4 * 4bytes, 4 int variable
	movl 	%edi, -20(%rbp)	#use register %edi to store n
	movq	%rsi, -32(%rbp)	#use register %rsi to store a
	movl	-20(%rsp), %eax	#store n in %eax
	//TODO

	movl	%edi, %esi	#%esi = %edi, directly use parameter n, prepare for call print
	leaq	.LC0(%rip), %rdi	#get string message to print
	movl	$0, %eax	#clear %eax before call
	call	printf@PLT
	movl	$0, -8(%rbp)	#store 0 in %rbp-8
	movl	$1, -4(%rbp)	#store 1 in %rbp-4
// reserve space for local variables
/* make a table here the variables from 
 * your c code and the addresses used in assembly 
 * n - address of n    
 * a - address of a
 * i - address of i
 * ....
*/
	//todo
	//subq	$32, %rsp	//allocate 32 bytes for extra spaces of 4 * 4bytes, 4 int variable
	//movl 	%edi, -20(%rbp)	//use register %edi to store n
	//movq	%rsi, -32(%rbp)	//use register %rsi to store a
	//movl	-20(%rsp), %eax	//store n in %eax
	jmp	.IF
// this code calls Print_One_Number to 
// print the number found in register %eax - use this code to debug 
// replace $999 with a register or memory address you wish to print
.LOOP:
    	movl    -4(%rbp), %eax	#store i from -4(%rbp) into %eax
	cltq	#extend %eax to %rax
	leaq	0(,%rax,4), %rdx	#create a space(%rbp * 4 as length) to store 4bytes int
	movq	-32(%rbp), %rax		#move *a in %rax
	addq	%rdx, %rax		#a + 4 * int
	//TODO
	//maybe need two lines
	movl	(%rax), %edi		#store a[i] in %edi
	//movl	%eax, %edi
	call	Print_One_Number@PLT	#call print method
// write your code to find the index of the maximum value here
        movl    -8(%rbp), %eax
	cltq
	leaq    0(,%rax,4), %rdx
	movq    -32(%rbp), %rax
	addq    %rdx, %rax
	movl    (%rax), %edx
	movl    -4(%rbp), %eax
	cltq
	leaq    0(,%rax,4), %rcx
	movq    -32(%rbp), %rax
	addq    %rcx, %rax
	movl    (%rax), %eax
	cmpl    %eax, %edx
	jge     .INCREMENT
	movl    -4(%rbp), %eax
	movl    %eax, -8(%rbp)		
// prepare the return value
// the template returns -1, you will need to update this
.INCREMENT:
	addl	$1, -4(%rbp)	#increment i++ in for loop, i stored in -4(%rbp)
// epilogue - complete the epilogue below
.IF:
	movl	-4(%rbp), %eax	#move i to %eax
	cmpl	-20(%rbp), %eax	#compare -4(%rbp) and -20(%rbp), which is i and n
	jl	.LOOP
	movl	-8(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	Find_Max, .-Find_Max
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
