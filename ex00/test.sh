#!/bin/bash

BOLD='\033[1m'
HIGHLIGHT='\033[7m'
YELLOW='\033[1;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

#Nom du programme à exécuter
programme="./convert"

#Tests
test_sujet=("0" "nan" "42.0f")
expected_outputs=(
    "char: non displayable\nint: 0\nfloat: 0.0f\ndouble: 0.0"
    "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan"
    "char: '*'\nint: 42\nfloat: 42.0f\ndouble: 42.0"
)

test_char=("'a'" "'7'" "'~'")
expected_outputs1=(
    "char: 'a'\nint: 97\nfloat: 97.0f\ndouble: 97.0"
    "char: '7'\nint: 55\nfloat: 55.0f\ndouble: 55.0"
    "char: '~'\nint: 126\nfloat: 126.0f\ndouble: 126.0"
)

test_int=("-2" "2147483647" "-2147483648")
expected_outputs2=(
    "char: non displayable\nint: -2\nfloat: -2.0f\ndouble: -2.0"
    "char: impossible\nint: 2147483647\nfloat: 2147483648.0f\ndouble: 2147483647.0"
    "char: impossible\nint: -2147483648\nfloat: -2147483648.0f\ndouble: -2147483648.0"
)

test_float=("3.14f" "1e2f" "-1e+3f" "5e-1f")
expected_outputs3=(
    "char: non displayable\nint: 3\nfloat: 3.1f\ndouble: 3.1"
    "char: 'd'\nint: 100\nfloat: 100.0f\ndouble: 100.0"
    "char: impossible\nint: -1000\nfloat: -1000.0f\ndouble: -1000.0"
    "char: non displayable\nint: 0\nfloat: 0.5f\ndouble: 0.5"
)

test_double=("-127.0" "+92.5" "11e+1" "-1e-1")
expected_outputs4=(
    "char: non displayable\nint: -127\nfloat: -127.0f\ndouble: -127.0"
    "char: '\\\'\nint: 92\nfloat: 92.5f\ndouble: 92.5"
    "char: 'n'\nint: 110\nfloat: 110.0f\ndouble: 110.0"
    "char: non displayable\nint: 0\nfloat: -0.1f\ndouble: -0.1"
)

test_pseudo=("+inf" "-inff" "nanf")
expected_outputs5=(
    "char: impossible\nint: impossible\nfloat: +inff\ndouble: +inf"
    "char: impossible\nint: impossible\nfloat: -inff\ndouble: -inf"
    "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan"
)

test_error=("+-0" "abc" "2.5." "-.2" "-5.0fF" "0.f")
expected_outputs6="char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible"
 

printf "__________________________________________________\n"
printf "${BOLD}${HIGHLIGHT}|                                                |\n"
printf "|  EXECUTION DU PROGRAMME AVEC DIFFERENTS TESTS  |\n"
printf "|________________________________________________|${NC}\n\n" 

function convert2 {
    printf "===================================================\n\n"
    printf "                  ${HIGHLIGHT}${BOLD}  TEST: CHAR  ${NC}               \n\n"

    for i in "${!test_char[@]}"
    do
        test="${test_char[$i]}"
        expected=$(printf "${expected_outputs1[$i]}")
        
        # Afficher l'exécution du programme avec l'argument actuel
        printf "...................................................\n\n"
        printf "${BOLD}${YELLOW}$programme $test${NC}\n"
        
        # Exécuter le programme avec l'argument du test
        $programme $test
        result=$($programme $test)

        # Comparer la sortie avec le résultat attendu
        echo -e "\n${BOLD}Résultat attendu:${NC}"
        echo -e "$expected\n"
        
        # Utiliser diff pour comparer les sorties
        if diff <(printf "%s" "$expected") <(printf "%s" "$result"); then
            echo -e "${BOLD}${GREEN}Test réussi!${NC}\n"
        else
            echo -e "${BOLD}${RED}Test échoué!${NC}\n"
        fi
    done
}

function convert3 {
    printf "===================================================\n\n"
    printf "                  ${HIGHLIGHT}${BOLD}  TEST: INT  ${NC}               \n\n"

    for i in "${!test_int[@]}"
    do
        test="${test_int[$i]}"
        expected=$(printf "${expected_outputs2[$i]}")
        
        # Afficher l'exécution du programme avec l'argument actuel
        printf "...................................................\n\n"
        printf "${BOLD}${YELLOW}$programme $test${NC}\n"
        
        # Exécuter le programme avec l'argument du test
        $programme $test
        result=$($programme $test)

        # Comparer la sortie avec le résultat attendu
        echo -e "\n${BOLD}Résultat attendu:${NC}"
        echo -e "$expected\n"
        
        # Utiliser diff pour comparer les sorties
        if diff <(printf "%s" "$expected") <(printf "%s" "$result"); then
            echo -e "${BOLD}${GREEN}Test réussi!${NC}\n"
        else
            echo -e "${BOLD}${RED}Test échoué!${NC}\n"
        fi
    done
}

function convert4 {
    printf "===================================================\n\n"
    printf "                 ${HIGHLIGHT}${BOLD}  TEST: FLOAT  ${NC}               \n\n"

    for i in "${!test_float[@]}"
    do
        test="${test_float[$i]}"
        expected=$(printf "${expected_outputs3[$i]}")
        
        # Afficher l'exécution du programme avec l'argument actuel
        printf "...................................................\n\n"
        printf "${BOLD}${YELLOW}$programme $test${NC}\n"
        
        # Exécuter le programme avec l'argument du test
        $programme $test
        result=$($programme $test)

        # Comparer la sortie avec le résultat attendu
        echo -e "\n${BOLD}Résultat attendu:${NC}"
        echo -e "$expected\n"
        
        # Utiliser diff pour comparer les sorties
        if diff <(printf "%s" "$expected") <(printf "%s" "$result"); then
            echo -e "${BOLD}${GREEN}Test réussi!${NC}\n"
        else
            echo -e "${BOLD}${RED}Test échoué!${NC}\n"
        fi
    done
}

function convert5 {
    printf "===================================================\n\n"
    printf "                ${HIGHLIGHT}${BOLD}  TEST: DOUBLE  ${NC}               \n\n"

    for i in "${!test_double[@]}"
    do
        test="${test_double[$i]}"
        expected=$(printf "${expected_outputs4[$i]}")
        
        # Afficher l'exécution du programme avec l'argument actuel
        printf "...................................................\n\n"
        printf "${BOLD}${YELLOW}$programme $test${NC}\n"
        
        # Exécuter le programme avec l'argument du test
        $programme $test
        result=$($programme $test)

        # Comparer la sortie avec le résultat attendu
        echo -e "\n${BOLD}Résultat attendu:${NC}"
        echo -e "$expected\n"
        
        # Utiliser diff pour comparer les sorties
        if diff <(printf "%s" "$expected") <(printf "%s" "$result"); then
            echo -e "${BOLD}${GREEN}Test réussi!${NC}\n"
        else
            echo -e "${BOLD}${RED}Test échoué!${NC}\n"
        fi
    done
}

function convert6 {
    printf "===================================================\n\n"
    printf "                 ${HIGHLIGHT}${BOLD}  TEST: PSEUDO  ${NC}               \n\n"

    for i in "${!test_pseudo[@]}"
    do
        test="${test_pseudo[$i]}"
        expected=$(printf "${expected_outputs5[$i]}")
        
        # Afficher l'exécution du programme avec l'argument actuel
        printf "...................................................\n\n"
        printf "${BOLD}${YELLOW}$programme $test${NC}\n"
        
        # Exécuter le programme avec l'argument du test
        $programme $test
        result=$($programme $test)

        # Comparer la sortie avec le résultat attendu
        echo -e "\n${BOLD}Résultat attendu:${NC}"
        echo -e "$expected\n"
        
        # Utiliser diff pour comparer les sorties
        if diff <(printf "%s" "$expected") <(printf "%s" "$result"); then
            echo -e "${BOLD}${GREEN}Test réussi!${NC}\n"
        else
            echo -e "${BOLD}${RED}Test échoué!${NC}\n"
        fi
    done
}

function convert7 {
    printf "===================================================\n\n"
    printf "                 ${HIGHLIGHT}${BOLD}  TEST: ERROR  ${NC}               \n\n"

    for i in "${!test_error[@]}"
    do
        test="${test_error[$i]}"
        expected=$(printf "${expected_outputs6}")
        
        # Afficher l'exécution du programme avec l'argument actuel
        printf "...................................................\n\n"
        printf "${BOLD}${YELLOW}$programme $test${NC}\n"
        
        # Exécuter le programme avec l'argument du test
        $programme $test
        result=$($programme $test)
        
        # Utiliser diff pour comparer les sorties
        if diff <(printf "%s" "$expected") <(printf "%s" "$result"); then
            echo -e "${BOLD}${GREEN}\nTest réussi!${NC}\n"
        else
            echo -e "${BOLD}${RED}Test échoué!${NC}\n"
        fi
    done
}

convert=(
    convert2
    convert3
    convert4
    convert5
    convert6
    convert7
)

function convert {
    for test in "${convert[@]}"; do
        $test
		printf "===================================================\n"
        printf "${BOLD}Press Enter to proceed to the next test...          ${NC}"
        read
    done
}

convert
