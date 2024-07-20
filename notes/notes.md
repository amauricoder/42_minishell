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

- "e"'c'"h""o"
- echo "WORD" -> the second token was beggining with space and nor in_DQUOTE (do_lexing)


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