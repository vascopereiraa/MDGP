# MDGP

This project has the purpose of representing the maximally diverse group problem algorithm that consists of partitioning a set of n elements (E) into m disjoint groups so that the diversity among the elements in each group is maximised. The diversity among the elements in a group is calculated as the sum of the dissimilarity values between each pair of elements.

The project was developed using C language.

## Run
In order to run the the program you'll just need to compile the code inside src folder using
``` gcc -o mdgp main.c evolutivo.c funcoes.c initDados.c pesquisaLocal.c utils.c ```
and the run the executable by 
``` ./mdgp ``` 
