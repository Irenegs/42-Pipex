#!/bin/bash

make re && make clean

RED='\033[0;31m'
GR='\033[0;32m'
NC='\033[0m' # No Color

touch input.txt outPipex.txt outBash.txt

ls -lah > input.txt

echo "Am I here?" > outPipex.txt
echo "Am I here?" > outBash.txt

T=1

echo -e "\n\n"


echo "1. INITIAL TESTS"

echo -e "\n\n"
echo "1.1 Does it work?"

echo -e "\n" $T "TEST: cat | wc -l " && T=$((T+1))
./pipex input.txt "cat" "wc -l" outPipex.txt
< input.txt cat | wc -l > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: cat | ls " && T=$((T+1))
./pipex input.txt cat "ls" outPipex.txt
< input.txt cat | ls > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi


echo -e "\n" $T "TEST: rm -f file2 | cat " && T=$((T+1))
touch file1 file2
./pipex input.txt "rm -f file1" cat outPipex.txt
< input.txt rm -f file2 | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n\n"
echo "1.2 Sleep: Watch out when output is ready."

echo -e "\n" $T "TEST: sleep 4 | ls -a " && T=$((T+1))
./pipex input.txt "sleep 4" "ls -a" outPipex.txt
< input.txt sleep 4 | ls -a > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e '#! /bin/bash \n\n sleep 4 && echo "hola"' > sleep_echo.sh
chmod +x sleep_echo.sh
echo -e "\n" $T "TEST: sleep + echo | cat " && T=$((T+1))
./pipex input.txt "./sleep_echo.sh" "cat" outPipex.txt
< input.txt ./sleep_echo.sh | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi


rm -r sleep_echo.sh

echo -e "\n\n"
echo "1.3 Local programs and absolute routes"

echo -e "#! /bin/bash \n\n echo 'Hi, I am a program!!'" > program.sh
chmod +x program.sh
echo -e "\n" $T "TEST: ./program.sh cat" && T=$((T+1))
./pipex input.txt ./program.sh cat outPipex.txt
< input.txt ./program.sh | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: ls ./program.sh" && T=$((T+1))
./pipex input.txt ls ./program.sh outPipex.txt
< input.txt ls | ./program.sh > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

mv program.sh ../program.sh
echo -e "\n" $T "TEST: ../program.sh cat" && T=$((T+1))
./pipex input.txt ../program.sh cat outPipex.txt
< input.txt ../program.sh | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: ls ../program" && T=$((T+1))
./pipex input.txt ls ../program.sh outPipex.txt
< input.txt ls | ../program.sh > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

mkdir folder
mv ../program.sh folder/program.sh
echo -e "\n" $T "TEST: folder/program.sh cat" && T=$((T+1))
./pipex input.txt folder/program.sh cat outPipex.txt
< input.txt folder/program.sh | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: ls folder/program.sh" && T=$((T+1))
./pipex input.txt ls folder/program.sh outPipex.txt
< input.txt ls | folder/program.sh > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi
mv folder/program.sh .
rm -rf folder

echo -e "\n" $T "TEST: /bin/cat cat" && T=$((T+1))
./pipex input.txt /bin/cat cat outPipex.txt
< input.txt /bin/cat | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: ls /bin/cat" && T=$((T+1))
./pipex input.txt ls /bin/cat outPipex.txt
< input.txt ls | /bin/cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi


echo -e "\n\n"
echo "2. FLAGS"

echo -e "\n" $T "TEST:  ls -l     -a | wc -l " && T=$((T+1))
./pipex input.txt "ls -l     -a" "wc -l" outPipex.txt
< input.txt ls -l     -a| wc -l > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: ls -la -h | wc -l " && T=$((T+1))
./pipex input.txt "ls -la -h" "wc -l" outPipex.txt
< input.txt ls -la -h| wc -l > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: awk '/a/' | cat " && T=$((T+1))
./pipex input.txt "awk '/a/'" cat outPipex.txt
< input.txt awk '/a/' | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: cat | awk '/a/'" && T=$((T+1))
./pipex input.txt "cat" "awk '/a/'" outPipex.txt
< input.txt cat | awk '/a/' > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: awk -F'0' '{print $2}'| cat" && T=$((T+1))
./pipex input.txt "awk -F'0' '{print \$2}'" cat outPipex.txt
< input.txt awk -F'0' '{print $2}'| cat  > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: cat | awk '{print \$3 "\t" \$4}'" && T=$((T+1))
./pipex input.txt "ls -l" "awk '{print \$3 \"\\\t\" \$4}'" outPipex.txt
< input.txt ls -l | awk '{print $3 "\t" $4}' > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n\n"
echo "3. ERRORS"

echo -e "\n\n"
echo "3.1 Input"

T=1
echo -e "\n" $T "TEST: no-input.txt cat | wc -l" && T=$((T+1))
./pipex no-input.txt "cat" "wc -l" outPipex.txt
< no-input.txt cat | wc -l > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: no-input.txt ls | cat" && T=$((T+1))
./pipex no-input.txt "ls" "cat" outPipex.txt
< no-input.txt ls | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

touch input-r.txt
chmod -r input-r.txt
echo -e "\n" $T "TEST: input-r.txt cat | wc -l" && T=$((T+1))
./pipex input-r.txt "cat" "wc -l" outPipex.txt
< input-r.txt cat | wc -l > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi
rm input-r.txt

echo -e "\n\n"
echo "3.2 cmd 1"

echo -e "\n" $T "TEST: nocmd | wc -l " && T=$((T+1))
./pipex input.txt nocmd "wc -l" outPipex.txt
< input.txt nocmd | wc -l > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: ./nocmd | wc -l " && T=$((T+1))
./pipex input.txt ./nocmd "wc -l" outPipex.txt
< input.txt ./nocmd | wc -l > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: nocmd | ls " && T=$((T+1))
./pipex input.txt nocmd "ls" outPipex.txt
< input.txt nocmd | ls > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

chmod -x program.sh
echo -e "\n" $T "TEST: ./program.sh cat" && T=$((T+1))
./pipex input.txt ./program.sh cat outPipex.txt
< input.txt ./program.sh | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n\n"
echo "3.3 cmd 2"

echo -e "\n" $T "TEST: cat | nocmd " && T=$((T+1))
./pipex input.txt cat nocmd outPipex.txt
< input.txt cat | nocmd > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: cat | ./nocmd " && T=$((T+1))
./pipex input.txt cat ./nocmd outPipex.txt
< input.txt cat | ./nocmd > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi


echo -e "\n" $T "TEST: ls ./program.sh" && T=$((T+1))
./pipex input.txt ls ./program.sh outPipex.txt
< input.txt ls | ./program.sh > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n\n"
echo "3.4 Output"

echo -e "\n" $T "TEST: cat | wc -l no-output" && T=$((T+1))
./pipex input.txt "cat" "wc -l" no-outputPipex
< input.txt cat | wc -l > no-outputBash
if [[ $(diff no-outputPipex no-outputBash | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi
rm -f no-outputPipex no-outputBash

touch output-w.txt
chmod -w output-w.txt
echo -e "\n" $T "TEST: cat | wc -l output-w.txt" && T=$((T+1))
./pipex input.txt "cat" "wc -l" output-w.txt
< input.txt cat | wc -l > output-w.txt
rm -f output-w.txt

echo -e "\n\n"
echo "3.5 Flags"

echo -e "\n" $T "TEST: wc -v | cat" && T=$((T+1))
./pipex input.txt "wc -v" cat outPipex.txt
< input.txt wc -v | cat > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n" $T "TEST: cat | wc -v " && T=$((T+1))
./pipex input.txt cat "wc -v" outPipex.txt
< input.txt cat | wc -v > outBash.txt
if [[ $(diff outPipex.txt outBash.txt | wc -l) -eq 0 ]];
	then echo -e "${GR}OK${NC}";
	else echo -e "${RED}KO${NC}"
fi

echo -e "\n\n"
echo "3.6 Environment"


rm -f outPipex.txt outBash.txt
#env -i ./pipex outPipex.txt cat "echo $PATH" outBash.txt
