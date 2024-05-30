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