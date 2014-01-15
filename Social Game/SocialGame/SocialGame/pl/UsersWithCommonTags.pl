
countCommonTags(User1,User2,N):-
	findall(X,tag(User1,X),TagList1),
	findall(Y,tag(User2,Y),TagList2),
	equalElements(TagList1,TagList2,L3),
	length(L3,N).

equalElements([],_,[]).
equalElements([H|T1],L,[H|T]):-
	member(H,L),!,
	equalElements(T1,L,T).
equalElements([_|T],L1,L2):- equalElements(T,L1,L2).


getFriendsWithCommonTags(N,User,[],[]).
getFriendsWithCommonTags(N,User,[H|T], [H|T1]):-
	countCommonTags(User,H,Y),
	not(Y < N),
	getFriendsWithCommonTags(N,User,T,T1).
getFriendsWithCommonTags(N,User,[_|T],L):-
	getFriendsWithCommonTags(N,User,T,L).
