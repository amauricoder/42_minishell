## 30/05/2023 - quinta feira (corpus christi)

Hoje comecei a trabalhar na parte de lexing(tokenizacao).
Criei algumas funcoes e mexi nas estruturas.

Por enquanto, o unico char que reconhece é ' ',
que no type enum é 0.

**O codigo tem leaks**
Dos allocs de 
- char			*content;
- struct s_token	*head;
- struct s_token	*tail;
- struct s_token	*next;
- struct s_token	*prev;

Da funcao int	alloc_tokenstruct(t_mini *mini_d) do arquivo lexing_1.c

======================================================================

## 04/06/2023 - terca feira

Hoje comecei a criar os states para o e_num states.
Estou fazendo baseado nisso
https://github.com/achrafelkhnissi/minishell?tab=readme-ov-file

Agora so reconhece espaco e ".
