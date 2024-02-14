section .text
    global count_char

count_char:
    mov ebx, edi ; String address (entry)
    movzx ecx, byte [esi] ; Character to search for (_c)
    xor edx, edx ; Counter (initialize to 0)
    xor r8d, r8d ; Index (initialize to 0)

.loopBody:
    cmp byte [ebx + r8d], 0 ; Check if we've reached the end of the string
    je .retVal

    cmp byte [ebx + r8d], cl ; Compare the byte at ebx + r8d with the character in cl
    jne .notFound

    inc edx ; Increment the counter
.notFound:
    inc r8d ; Increment the index
    jmp .loopBody

.retVal:
    mov eax, edx ; Move the counter value into eax (return value)
    ret ; Return