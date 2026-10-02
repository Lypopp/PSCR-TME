# TME2 : réponses et traces

Un titre par question. Sous chaque titre : la réponse si la question en demande une, et la trace de l'exécution
de votre code, collée telle quelle entre triples backquotes. On peut couper le milieu d'une trace longue, on garde
les dernières lignes, avec le temps d'exécution.

## Machine de mesure

Collez ici le bloc produit par `./machine-info.sh`, puis complétez le contexte de mesure.

```text
Date : 2026-10-02 08:59 UTC
Système : Darwin 25.5.0 arm64
macOS : 26.5.1
CPU : Apple M1 Pro
Cœurs physiques : 8
CPU logiques : 8
Fréquence maximale : non exposée par le système
Compilateur par défaut : Apple clang version 21.0.0 (clang-2100.1.1.101)
```

## Question 1

```
$ ./build-debug/countword WarAndPeace.txt count
565500: to
Finished parsing.
Found a total of 565527 words.
Total runtime (wall clock) : 2401 ms
```

```
$ ./build-release/countword WarAndPeace.txt count
565500: to
Finished parsing.
Found a total of 565527 words.
Total runtime (wall clock) : 381 ms
```
Il y a donc 565 527 mots.

## Question 2

            debug       release
Avec trace  2401 ms     381 ms
Sans Trace  2224 ms     322 ms



## Question 3

Found 20332 unique words

## Question 4

War : 298
Peace : 114
Toto : 0

## Question 5

```
$ ./build-release/countword WarAndPeace.txt freq                 
Parsing WarAndPeace.txt (mode=freq)
Found 20332 unique words.
War : 298
Peace : 114
1. the
2. and
3. to
4. of
5. a
6. he
7. in
8. his
9. that
10. was
Total runtime (wall clock) : 1629 ms
```

## Question 6

```
$ ./build-release/countword WarAndPeace.txt freq   
Parsing WarAndPeace.txt (mode=freqstd)
Found 20332 unique words.
War : 298
Peace : 114
Toto : 0
1. the
2. and
3. to
4. of
5. a
6. he
7. in
8. his
9. that
10. was
Total runtime (wall clock) : 344 ms
```

## Question 7

On remarque qu'on a presque un facteur 5 entre freqstd et freq.
Cela est principalement dû dans freq au parcours de seen à chaque mot pour vérifier
qu'il est dans le vecteur ou non contrairement à dans freqstd ou on calcul le hash du mot
et ainsi le retrouver dans la hash est beaucoup plus rapide.

## Question 8

## Question 9

## Question 10 (bonus)
