liga(a,b,63).
liga(a,c,53).
liga(a,d,57).
liga(b,e,60).
liga(c,e,50).
liga(c,f,46).
liga(d,f,58).
liga(e,g,50).
liga(g,j,49).
liga(j,m,65).
liga(m,k,57).
liga(m,l,62).
liga(k,h,34).
liga(l,h,48).
liga(h,l,48).
liga(k,i,46).
liga(i,k,46).
liga(h,i,35).
liga(i,h,35).
liga(f,h,45).
liga(f,i,47).
liga(a,z,1).
liga(z,l,1000).

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
	write(NPerc2),nl,
	go1(NPerc2,Dest,Perc, CC, Final).

proximo_no(X,T,Z,C):-liga(X,Z,C), \+ member(Z,T).
