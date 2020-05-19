global      _strlen         
        
_strlen:
; Subroutine Prologue
    push    ebp                                     ; save the old base pointer value
    mov     ebp, esp                                ; set the new base pointer value
    sub     esp, 4                                  ; make room for one 4-byte local variable
    push    eax                                     ; save the value of register that strlen uses (eax)
    push    ecx                                     ; save the value of register that strlen uses (ecx)

; Subroutine Body
    mov     eax, 0                                  ; length = 0
    mov     ecx, [ebp+8]                            ; copy the function's first argument (pointer to the first char of string)
    _strlen_loop_start:                             ; this is a label we can jump to
        cmp byte [ecx], 0                           ; dereference that pointer and compare it to null
        je _strlen_loop_end                         ; jump out of the loop if it is equal to null
        inc eax                                     ; add 1 to our return value
        add ecx, 1                                  ; increment to the next character in the string
        jmp _strlen_loop_start                      ; jump back to the top of the loop
    _strlen_loop_end:

; Subroutine Epilogue    
    pop     ecx
    mov     esp, ebp                                ; deallocate local variables
    pop     ebp                                     ; restore the caller's base pointer value
    ret

global      _start                                        
section     .text                                         
_start:                                                 
    mov     eax, 4                                  ; system call number (sys_write)
    mov     ebx, 1               		            ; file descriptor (stdout)
	mov	    ecx, msg                                ; address of message to write
	push	eax                                     ; save the caller-saved registers
	push	ecx
	push	msg                                     ; push strlen's argument (msg)
	call    _strlen                                 ; eax is now equal to the length of the string
	mov     edx, eax                                ; move the length into edx
	add     esp, 4                                  ; remove 4 bytes from the stack (one 4-byte char* argument)
	pop     ecx                                     ; restore caller-saved registers
	pop     eax
	int       80h                  		            ; request an interrupt on libc using INT 80h

exit:  
    mov     eax, 1                                  ; system call number (sys_exit)
    mov     ebx, 0                                  ; return 0 status on exit
    int     80h                                     ; request an interrupt on libc using INT 80h

section     .data                                         
msg     db "A new string", 0Ah                      ; message to write