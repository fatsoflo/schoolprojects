global    _start                                        ;
section   .text                                         

_start:                                                 
    mov     eax,  4                               ; system call number (sys_write)
    mov     ebx,  1                               ; file descriptor (stdout)
    mov     ecx,  msg                             ; address of message to write
    mov     edx,  26                              ; address of message length
    int     80h                                   ; request an interrupt on libc using INT 80h             
exit:   
    mov     eax,  1                               ; system call number (sys_exit)
    mov     ebx,  0                               ; return 0 status on exit
    int     80h                                   ; request an interrupt on libc using INT 80h

section   .data                                         
msg     db "Florence Fong 23670012 MM2", 0Ah      ; message stored