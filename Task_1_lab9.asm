.model small
.stack 100h

.data
    msg1 db 'Enter cents (0-99): $'
    msg2 db 0Dh,0Ah,'Half dollos: $'
    msg3 db 0Dh,0Ah,'quaters: $'
    msg4 db 0Dh,0Ah,'dimes: $'
    msg5 db 0Dh,0Ah,'nikles: $'
    msg6 db 0Dh,0Ah,'pennies: $'

    input db 3,0,3 dup(?) 
    cents db 0
    hds db 0
    qts db 0
    dms db 0
    nks db 0
    pns db 0

.code
MAIN PROC
    mov ax,@data
    mov ds,ax

    mov dx,OFFSET msg1
    mov ah,09h
    int 21h

    mov dx,OFFSET input
    mov ah,0Ah
    int 21h

    mov al,[input+1]
    cmp al,0
    je no_input

    cmp al,2
    je two_digit

no_input:
    mov cents,0
    jmp do_calc


two_digit:
    mov al,[input+2]
    sub al,'0'
    mov bl,10
    mul bl
    mov dl,[input+3]
    sub dl,'0'
    add al,dl
    mov cents,al

do_calc:
    mov al,cents
    mov ah,0
    mov bl,50
    div bl
    mov hds,al
    mov al,ah
    mov cents,al

    mov al,cents
    mov ah,0
    mov bl,25
    div bl
    mov qts,al
    mov al,ah
    mov cents,al

    mov al,cents
    mov ah,0
    mov bl,10
    div bl
    mov dms,al
    mov al,ah
    mov cents,al

    mov al,cents
    mov ah,0
    mov bl,5
    div bl
    mov nks,al
    mov pns,ah

    mov dx,OFFSET msg2
    mov ah,09h
    int 21h
    mov dl,hds
    add dl,30h
    mov ah,02h
    int 21h

    mov dx,OFFSET msg3
    mov ah,09h
    int 21h
    mov dl,qts
    add dl,30h
    mov ah,02h
    int 21h

    mov dx,OFFSET msg4
    mov ah,09h
    int 21h
    mov dl,dms
    add dl,30h
    mov ah,02h
    int 21h

    mov dx,OFFSET msg5
    mov ah,09h
    int 21h
    mov dl,nks
    add dl,30h
    mov ah,02h
    int 21h

    mov dx,OFFSET msg6
    mov ah,09h
    int 21h
    mov dl,pns
    add dl,30h
    mov ah,02h
    int 21h

    mov ah,4Ch
    int 21h

MAIN ENDP
END MAIN
