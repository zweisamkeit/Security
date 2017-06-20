#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Attaque de Weiner
# Zweisamkeit
# 28/12/15
# GNU/GPL v3

import sys
import random
import Crypto.PublicKey.RSA

# Accueil

def accueil():

  print ("\n")
  print ("\t~~~~~~~~~~~~~~~~~~~~~~~~~")
  print ("\t      Weiner Attack      ")
  print ("\t       Zweisamkeit       ")
  print ("\t    GNU GPL v3 License   ")
  print ("\t~~~~~~~~~~~~~~~~~~~~~~~~~")
  print ("\n")

# Retourne le couple (q,r) de la division euclidienne a = bq + r

def division_euclidienne(a, b):

  return (a // b, a % b)

# Retourne le développement en fraction continue du nombre rationnel n/d

def fraction_continue(n, d):

  developpement = []
  a = n
  b = d

  while b != 0:

    (q,r) = division_euclidienne(a,b)

    developpement.append(q)

    a = b
    b = r

  return (developpement)

# Renvoie les réduites d'une fraction continue a

def reduites_fraction_continue(a):

  l=len(a)
  
  # Initialisation des sous-suites

  reduites=[]

  h0 = 1
  h1 = 0
  k0 = 0
  k1 = 1

  count = 0

  # Construction des réduites

  while count < l:

    h = a[count] * h1 + h0
    h0 = h1
    h1 = h

    k = a[count] * k1 + k0
    k0 = k1
    k1 = k

    reduites.append((k,h))
    
    count += 1

  return (reduites)

# Attaque de Weiner 

def weiner(n, e):

  # Décomposition de e/n en fraction continue

  fc = fraction_continue(e, n)

  # Calcul des réduites de la fraction continue

  reduites = reduites_fraction_continue(fc)

  # Recherche de la clé privée parmi les dénominateurs des réduites

  message_clair = random.randint(10**1,10**5)

  message_chiffre = pow(message_clair, e, n)

  l = len(reduites)

  i = 0

  while i < l and pow(message_chiffre, reduites[i][1], n) != message_clair:
  
    i += 1
  
  if i != l:
  
    return (reduites[i][1])
    
  else:

    print("\tThis RSA public key isn't a valid candidate to a Weiner Attack\n")
    exit(0)

# Main (Pour une fois que j'en fais un... :))

if __name__ == "__main__":

  accueil()

  if len(sys.argv) != 3:
    
    print("\n\tArgument Error: modulus exponent (decimal)\n")
    exit(0)
 
  try:

    n = int(sys.argv[1])
    e = int(sys.argv[2])

  except:

    print("\n\tArgument Error: modulus exponent (decimal)\n")
    exit(0)

  d = weiner(n, e)

  print ("\tPrivate exponent:",d,"\n")

  key = Crypto.PublicKey.RSA.construct((n,e,d))
  
  print("\tPrivate key: \n\n",Crypto.PublicKey.RSA._RSAobj.exportKey(key).decode('utf-8'),"\n")
