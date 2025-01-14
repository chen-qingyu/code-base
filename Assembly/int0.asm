assume cs:code

code segment

start:
    mov ax, cs
    mov ds, ax
    mov si, offset int0 ; Set ds:si to the source address

    mov ax, 0
    mov es, ax
    mov di, 200h ; Set es:di to destination address

    mov cx, offset int0end - offset int0
    cld
    rep movsb

    ; Set Interrupt Vector Table 
    mov ax, 0
    mov es,ax
    mov word ptr es:[0*4], 200h
    mov word ptr es:[0*4+2], 0

    ; Divide overflow trigger
    mov ax, 1000h
    mov bh, 1
    div bh

    mov ax, 4c00h
    int 21h

int0:
    jmp short int0start
    db "I LOVE YOU!"

int0start:
    mov ax, cs
    mov ds, ax
    mov si, 202h ; Set ds:si to the string

    mov ax, 0b800h
    mov es, ax
    mov di, 0 ; Set es:di to the VRAM

    mov cx, 0bh
s:
    mov al, [si]
    mov es:[di], al
    inc si
    add di, 2
    loop s

    mov ax, 4c00h
    int 21h

int0end:
    nop

code ends

end start
