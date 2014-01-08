
getC([(H, [_|_])|_], H).

go(Orig,Dest,Perc, CC):-
	go1([(0,[Orig])],Dest,P, Temp, CC),
	reverse(P,Perc).

go1([(_,Prim)|_],Dest,Prim, CC, Final):-Prim=[Dest|_], Final is CC.
go1([(_,[Dest|_])|Resto],Dest,Perc, CC, Final):-!, go1(Resto,Dest,Perc, CC, Final), Final > CC.
go1([(C,[Ult|T])|Outros],Dest,Perc, CCC, Final):-
	findall((NC,[Z,Ult|T]),
		(proximo_no(Ult,T,Z,C1),NC is C+C1),Lista),
	append(Outros,Lista,NPerc),
	sort(NPerc,NPerc1),
	reverse(NPerc1, NPerc2),
	getC(NPerc2, CC),
	go1(NPerc2,Dest,Perc, CC, Final).

proximo_no(X,T,Z,C):-liga(X,Z,Y),atom_number(Y,C), \+ member(Z,T).
