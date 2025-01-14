; Can this program be successfully returned? Yes!

assume cs:code

code segment

    mov ax, 4c00h
    int 21h

start:
    mov ax, 0

s:
    nop ; replaced by 'jmp short s1' : 'EB F6' : IP -10 byte
    nop

    mov di, offset s
    mov si, offset s2
    mov ax, cs:[si]
    mov cs:[di], ax

s0:
    jmp short s

s1:
    mov ax, 0 ; 3 byte
    int 21h   ; 2 byte
    mov ax, 0 ; 3 byte.

s2:
    jmp short s1 ; 2 byte. 'EB F6' : IP -10 byte
    nop

code ends

end start
