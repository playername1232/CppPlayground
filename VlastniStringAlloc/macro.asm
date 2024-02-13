section .data

section .text
    global remove_constant

remove_constant:
    push ebp
    mov epb, esp

    mov ebx, 0 ; counter
    moc ecx, len ; length
    mov edx, elemSize ; Element size

copy_loop:
    mov d1 [eax + ecx]
    