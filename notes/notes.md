## Articles

Article about construction a shell, with some interesting points about it.

- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

Another article about construction of a shell

- https://yannick.eu/minishell/

Article about parsing "Precedence Climbing Parsing".

- https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing

Useful Github with Useful Information
- https://github.com/DimitriDaSilva/42_minishell

## About leaks
=====================================================================================
Ignoring leaks by readline and add_history

You can use this command.
valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell
To "ignore" leaks related to the readline and add_history functions, create a file called readline.supp with the following content:
{ 
    leak readline
    Memcheck:Leak
    ...
    fun:readline
}
{
    leak add_history
    Memcheck:Leak
    ...
    fun:add_history
}

or 

Yop, normally it's not a problem. It is normal that readline leaks.

Try this to ignore readline leaks :

alias minishell_leaks='valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell'
Into a.ignore_readline 
{
   ignore_libreadline_conditional_jump_errors
   Memcheck:Leak
   ...
   obj:*/libreadline.so.*
}

OR

{
    ignore_libreadline_leaks
    Memcheck:Leak
    ...
    obj:/libreadline.so.*
}
Thx to tsignore.



valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell

make re && clear && valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all --suppressions=.ignore_readline -q ./minishell

--leak-check=full --show-leak-kinds=all
=====================================================================================

## TESTES EXPANSION
### 

- '$USER' ~ [output] = $USER
- "$USER" ~ [output] = aconceic
- '$USER>amauri' ~ [output] = $USER>amauri
- "$USER>amauri" ~ [output] = aconceic>amauri
- "$USER $USING" ~ [output] = aconceic
- "$USER '$USING'" ~ [output] = aconceic ''
- "$USER '$USING' $PWD" ~ [output] = aconceic '' /home/aconceic/Documents/42_Git/minishell
- "$USER '$USING>a' $PWD" ~ [output] = aconceic '>a' /home/aconceic/Documents/42_Git/minishell
- "$USER $PWD $PWD $PWD" ~ [output] = Tem que expandir as 4.
- "$'USER' $PWD" ~ [output] = $'USER' /home/aconceic/Documents/42_Git/minishell
- $BLA ~ [output] = NULL
- "$'$USER $'USER'" ~ [output] = $'aconceic $'USER'
- "$'USER$'USER'"~ [output] = $'USER$'USER'
- "$'USER $'USER" ~ [output] = $'USER $'USER'
- $"USER$""USER"~ [output] = USER$USER
- "p""wd" ~ [output] = /home/aconceic/Documents/42_Git/minishell
- "p"'wd' ~ [output] = /home/aconceic/Documents/42_Git/minishell
- "p" "wd" ~ [output] = p: command not found
- "p" 'wd' ~ [output] = p: command not found
- amaur"lisbo" ~ [output] = amaurlisbo
- palavra"$" ~ [output] = palavra$
- palavra"$"palavra ~ [output] = palavra$palavra
- palavra"$USER"palavra ~ [output] = palavraaconceicpalavra ---> LEAK HERE
- $12USER ~ [output] = 2USER
- $123456789USER ~ [output] = $23456789USER
- $0 ~[output] ./minishell  --- sozinho executa (abrir o programa dnv)
- $0USER ~[output] ./minishellUSER --- nao executa
- cat arquivo.txt | grep "banana" | sort | wc -l
- "e"'c'"h""o"
- echo "WORD" -> the second token was beggining with space and nor in_DQUOTE (do_lexing)

cat -e << EOF | cat -e << EOF2 | cat -e << EOF3 | cat -e << EOF4

- << EOF amauri --------- not working as expected
- > "" ---------------- not wokrking as expected

===== test heredoc ====
- cat << "EOF" > abc
> ola $USER
> que fixe $PWD
> EOF


=====================================================================================


TESTS TREE

cmd > file >> file2 < file3


======================================================================================

PROBLEMS TO BE SOLVED

--- amauri > $po --> error here (syntax error)

--- > > > ---> error here (This is syntax error, easy to resolver)
redirect withou nothing is syntax error (TO SOLVE)

--- export LS="ls -la | wc -l" --> Verificar como acontece no bash(pra depois)
--- export LS="ls -la" --> Verificar como acontece no bash (pra depois)

--- $LS -> SEGFAULT(RESOLVIDO)

--- ls | exit 1 --> nao sai do programa, mas muda o exit_status para 1

--- export a=a | wc -l --> resultado 0 e nao exporta o "a"
        * export e unset nao funciona em pipe

-- pwd | echo oi | ls

-- > $po --- Ambigous redirect (implementar isso)
---> meucu | ls - atualizar exit code para comand bem executado

---> cd ~ -> tratar
---> cd - -> tratar

-- > "" --- SEG FAULT
-- > '' --- SEG FAULT
https://codeshare.io/KWwAOM


===============================================================================

/* Redirecionamento de Saída (>)

O redirecionamento > cria um arquivo novo ou sobrescreve um arquivo existente. Para replicar esse comportamento com open(), você deve usar as seguintes flags:

    O_WRONLY: Abre o arquivo para escrita.
    O_CREAT: Cria o arquivo se ele não existir.
    O_TRUNC: Trunca (esvazia) o arquivo para zero bytes se ele já existir.

Redirecionamento de Saída com Append (>>)

O redirecionamento >> anexa ao final de um arquivo existente ou cria um novo arquivo se ele não existir. Para replicar esse comportamento, você deve usar:

    O_WRONLY: Abre o arquivo para escrita.
    O_CREAT: Cria o arquivo se ele não existir.
    O_APPEND: Adiciona dados ao final do arquivo, sem truncá-lo. */

===================================================================================

HERE_DOC

command <<EOF
line 1
line 2
line 3
EOF

cat <<EOF
Hello
World
EOF

cat <<EOF > output.txt
This is a test.
EOF
cat output.txt

name="Alice"
cat <<EOF
Hello, $name
EOF

name="Alice"
cat <<'EOF'
Hello, $name
EOF

grep "test" <<EOF
This is a test.
This is another line.
EOF

cat <<END
This is a custom delimiter.
END

cat <<EOF | grep "data"
Here is some data
Another line
More data
EOF

cat << EOF1 > file1 | cat << EOF2 > file2


nm -g ./minishell | grep U
