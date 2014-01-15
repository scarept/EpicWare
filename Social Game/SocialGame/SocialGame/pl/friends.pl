liga(1,3,2).
liga(3,4,1).
liga(4,5,2).
liga(3,7,3).
liga(3,8,3).
liga(7,2,2).
liga(4,8,1).

tag(1, 'LAPR5').
tag(1, 'ISEP').

getFriendsList(User, FriendsList):-findall(X, liga(User, X, _), FriendsList).

getNextLevel([H|T], NextLevel):-getNextLevel([H|T], [], NextLevel).
getNextLevel([], Final, Final).
getNextLevel([H|T], Temp, Final):-
	getFriendsList(H, L),
	append(Temp, L, NewTemp),
	getNextLevel(T, NewTemp, Final).

getFriendsLV3(User, FriendsList):-
	getFriendsList(User, LV1),
	getNextLevel(LV1, LV2),
	getNextLevel(LV2, LV3),
	append(LV1, LV2, LVTemp),
	append(LVTemp, LV3, TempFriendsList),
	sort(TempFriendsList, FriendsList).

countFriendsLV3(User, N):-
	getFriendsLV3(User, FriendsList),
	length(FriendsList, N).
