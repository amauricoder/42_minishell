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
=====================================================================================


//static char *search_and_replace(char **expanded, char *content);
//static int get_array_strlen(char **arr);
//static int get_dollar_strlen(char *str)

//static int have_spacial_char(char *word);
//'$USER' -> STATE IN_QUOTE && type WORD ~ [output] = $USER
//"$USER" -> state IN_DQUOTE && type WORD ~ [output] = aconceic

//'$USER>amauri' -> STATE IN_QUOTE && type WORD ~ [output] = $USER>amauri
//"$USER>amauri" -> state IN_DQUOTE && type WORD ~ [output] = aconceic>amauri (file is created)

//"$USER $USING" -> state IN_DQUOTE && type WORD ~ [output] = aconceic
//"USER '$USING'" -> state IN_DQUOTE && type WORD ~ [output] = aconceic ''

//"$USER '$USING' $PWD" ->state IN_DQUOTE && type WORD 
// ~ [output] = aconceic '' /home/aconceic/Documents/42_Git/minishell

//"$USER '$USING>a' $PWD" -> state IN_DQUOTE && type WORD
// ~[output] = aconceic '>a' /home/aconceic/Documents/42_Git/minishell

//
//"$'USER' $PWD"
 ~[output] = $'USER' /home/aconceic/Documents/42_Git/minishell
//$BLA -> state GENERAL && type WORD ~ [output] = NULL

//If the word to be expanded is not in ' ' and is valid, it expands.
//Otherwhise, it will be replaced by a NULL character.

