.MODEL SMALL
.STACK 100h

.DATA
msg1 db 'Type text (128 chars max): $'
msg2 db 0Dh,0Ah,'Encrypted: $'
msg3 db 0Dh,0Ah,'Decrypted: $'

input db 128,0,128 dup(?)    ; DOS buffered input
enc db 128 dup(?)             ; encrypted output

tbl db 'QWERTYUIOPASDFGHJKLZXCVBNMabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?/'
tbl2 db 'MNBVCXZLKJHGFDSAPOIUYTREqwertyuiopasdfghjklzxcvbnm9876543210)(*&^%$#@!~_+=}{][|;:,.<>?/'

.CODE
start:
    mov ax,@data
    mov ds,ax
    mov es,ax

    ; prompt
    mov dx,offset msg1
    mov ah,09h
    int 21h

    ; read line
    mov dx,offset input
    mov ah,0Ah
    int 21h

    mov cl,[input+1]         ; number of chars typed
    mov si,offset input+2
    mov di,offset enc

; encrypt loop
encrypt:
    cmp cl,0
    je enc_done
    mov al,[si]
    ; simple ASCII range check (skip non-table chars)
    cmp al,32
    jb skip
    cmp al,126
    ja skip
    mov bx,offset tbl
    sub al,32
    xlat
    mov [di],al
skip:
    inc si
    inc di
    dec cl
    jmp encrypt
enc_done:

    ; print encrypted
    mov dx,offset msg2
    mov ah,09h
    int 21h
    mov dx,offset enc
    mov ah,09h
    int 21h

; decrypt loop
    mov cl,[input+1]
    mov si,offset enc
decrypt:
    cmp cl,0
    je dec_done
    mov al,[si]
    cmp al,32
    jb skip2
    cmp al,126
    ja skip2
    mov bx,offset tbl2
    sub al,32
    xlat
    mov [si],al
skip2:
    inc si
    dec cl
    jmp decrypt
dec_done:

    ; print decrypted
    mov dx,offset msg3
    mov ah,09h
    int 21h
    mov dx,offset enc
    mov ah,09h
    int 21h

    mov ah,4Ch
    int 21h
END start
