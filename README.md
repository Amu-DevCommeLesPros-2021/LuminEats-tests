Ce fichier `main.c` est une copie du fichier `test/main.c` dans mon propre projet «LuminEats».
Je le met à votre disponibilité pour vous donner une idée des tests que j'écris pour ce projet.
Je le mettrai à jour au fil de son évolution.

Les fonctions et types ne sont pas coulés dans le béton.
Il se peut qu'après un réusinage de certaines parties de mon code, les fonctions changent un tant soit peu.
De plus, les tables que j'utilise pour tester ne sont  pas nécessairement exactement comme les tables données en exemple dans le `README` du projet.

Vous remarquerez que la plupart des fonctions commencent par le préfixe `le_`.
C'est un préfixe que je donne à toutes les fonctions de ma bibliothèque `liblumineats` («le» pour «LuminEats»), une pratique courante en C.
Si je l'écrivais en C++, j'utiliserais plutôt un [namespace](https://fr.cppreference.com/w/cpp/language/namespace) et, par exemple, `le_compte_existe` deviendrait `le::compte_existe`.
