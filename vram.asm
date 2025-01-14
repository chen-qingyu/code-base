assume cs:code

code segment

    mov     ax, 0b800h
    mov     ds, ax

    mov [000h], 'I'
    mov [002h], ' '
    mov [004h], 'L'
    mov [006h], 'O'
    mov [008h], 'V'
    mov [00ah], 'E'
    mov [00ch], ' '
    mov [00eh], 'Y'
    mov [010h], 'O'
    mov [012h], 'U'
    mov [014h], '!'

    mov cx, 0bh
    mov di, 01h
c:
    mov [di], 00011001b ; BL R G B I R G B
    add di, 2
    loop c    

    mov ax, 4c00h
    int 21h

code ends

end
