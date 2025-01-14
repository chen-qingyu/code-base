assume cs:code

data segment

    db "I LOVE YOU!", '$'

data ends

code segment

start:
    mov ah, 2 ; Set cursor
    mov bh, 0 ; 0 page
    mov dh, 0 ; row 0
    mov dl, 0 ; col 0
    int 10h

    mov ax, data
    mov ds, ax
    mov dx, 0 ; Set ds:dx to string
    mov ah, 9 ; Show string
    int 21h

    mov ax, 4c00h
    int 21h

code ends

end start
