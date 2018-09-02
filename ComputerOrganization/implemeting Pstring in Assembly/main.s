	.file	"main.c"
	.section	.rodata
.intDig:
	.string	"%d"
.stringParameter:
	.string	"%s"
	.text
	.globl	main
	.type	main, @function
main:
    movq %rsp, %rbp #for correct debugging
    pushq   %rbp			# push rbp into the stack
    movq    %rsp, %rbp		# save the begining of the frame of main in rbp
    
    #save the first pstring
    sub     $4, %rsp		#save 4 bytes
    movq    %rsp, %rsi		#save rsp in register rsi for
    movq    $.intDig, %rdi	#save %d in rdi
    movq    $0, %rax        #reset rax with 0
    call    scanf           #call scanf
    movq    $0, %r8		#reset r8 with 0
    movzbl	 (%rsp), %r8d    #take the value of rsp and assign it into r8 (take the length)
    add	$4, %rsp		#earse the value of the int that we recieved
    leaq -1(%rsp), %rsp     #save 1 byte in the stack for the \0
    movb	$0, (%rsp)		#reset the rsp value
    subq	%r8, %rsp		#save r8 places in rsp for the string
    leaq 1(%rsp), %rsi     #save rsi value with rsp and incrase the value with 1- for the len
    movb	%r8b, (%rsp)	#save the value of len in 1 byte
    movq	$.stringParameter, %rdi #save the %s value in rdi for parameter for function
    leaq 1(%rsp), %rsi	      #save rsi value with rsp and incrase the value with 1- for the len
    movq	$0, %rax		#reset rax with 0
    call scanf			#call scanf
    movq    $0, %r13        #reset r13 with 0
    leaq	(%rsp), %r13     #save the rsp value in register r13
					
    sub     $4, %rsp		#save 4 bytes
    movq    %rsp, %rsi		#save rsp in register rsi for
    movq    $.intDig, %rdi	#save %d in rdi
    movq    $0, %rax        #reset rax with 0
    call    scanf           #call scanf	
     movq    $0, %r9		#reset r8 with 0
    movzbl	 (%rsp), %r9d    #take the value of rsp and assign it into r8 (take the length)
    add	$4, %rsp		#earse the value of the int that we recieved	
      leaq -1(%rsp), %rsp     #save 1 byte in the stack for the \0
    movb	$0, (%rsp)		#reset the rsp value
    subq	%r9, %rsp		#save r8 places in rsp for the string	
	subq	$1, %rsp		
	movb	%r9b, (%rsp)				
     leaq    1(%rsp), %rsi	
	movq	$.stringParameter, %rdi	
	movq	$0, %rax		
	call scanf			
	leaq	(%rsp), %r14  
    sub	 $4, %rsp		
    movq	%rsp, %rsi		
    movq	$.intDig, %rdi	
    movq	$0, %rax		
    call	scanf		
    movq    $0, %r12
    movzbl	(%rsp), %r12d		# save the number in rax
    
    movq %r12, %rdi                     #hold the number
    movq %r13, %rsi                     #hold the first string
    movq %r14, %rdx                     #hold the second string
    call run_func      
    
.L3:
	leave
	ret
