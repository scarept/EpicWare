
go(Orig,Dest,Perc) :- go1([[Orig]],Dest,P), inverte(P,Perc).
go1([Prim|Resto],Dest,Prim) :- Prim=[Dest|_].
go1([[Dest|T]|Resto],Dest,Perc) :- !, go1(Resto,Dest,Perc).
go1([[Ult|T]|Outros],Dest,Perc):-findall([Z,Ult|T],proximo_no(Ult,T,Z),Lista),
append(Outros,Lista,NPerc),
go1(NPerc,Dest,Perc).

proximo_no(X,T,Z) :- liga(X,Z), \+ member(Z,T).

inverte(L,LI) :- inverte(L,[],LI).
inverte([],LI,LI).
inverte([H|T],L,LI) :- inverte(T,[H|L],LI).
