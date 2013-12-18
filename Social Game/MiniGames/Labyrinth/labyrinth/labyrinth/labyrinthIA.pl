:-dynamic liga/2.
/*
liga('(0,0)','(0,1)').
liga('(0,1)','(0,2)').
liga('(0,2)','(0,3)').
liga('(0,4)','(0,5)').
liga('(0,3)','(0,4)').
liga((0,5),(0,3)).
liga((0,6),(0,7)).
liga((0,1),(0,1)).
*/

% pesquisa((X,Y),([X1,X2]|T),Sol):-findall(((CX,CY)|T), (
% liga((X1,X2),(CX,CY)), not(member(CX,CY),T),L1 ), L1).

path(Inicio,Fim,Perc):- go1([[Inicio]],Fim,P),Perc = P.
go1([Prim|_],Fim,Prim):- Prim=[Fim|_].
go1([[Fim|_]|Resto],Fim,Perc):-!.
go1([[Ult|T]|Outros],Fim,Perc):-
		findall([Z,Ult|T],(liga(Ult,Z),not(member(Z,T))),Lista),
		%append(Lista,Outros,NPerc), % pesquisa 1º em profundidade
		append(Outros,Lista,NPerc),% pesquisa 1º em largura
		%write('NPerc:'), write(NPerc),nl,
		go1(NPerc,Fim,Perc).
