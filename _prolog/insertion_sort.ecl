/* Insertion Sort */

dodaj_na_koniec( [], X, X).
dodaj_na_koniec( [X | Y], A, [X | B]) :- dodaj_na_koniec( Y, A, B).

dodaj_do_listy_we_wlasciwym_miejscu(El, [], List):-
  List = [El].

dodaj_do_listy_we_wlasciwym_miejscu(El, [X], List):-
El >= X,
List = [El,X].
dodaj_do_listy_we_wlasciwym_miejscu(El, [X], List):-
  List = [X,El].

dodaj_do_listy_we_wlasciwym_miejscu(El, [X0,X1|T], List):-
El < X0, X1 \= [], !,
wstaw([X0],El, [X1|T], List).

dodaj_do_listy_we_wlasciwym_miejscu(El, [X0,X1|T], List):-
List = [El,X0,X1|T].

wstaw(Head, El, [X0,X1|T], List) :-
X0 >= El, El >= X1, !,
dodaj_na_koniec(Head, [X0,El,X1|T], L),
List = L.

wstaw(Head, El, [X0,X1|T], List) :-
X0 < El, !,
dodaj_na_koniec(Head, [El, X0 ,X1|T], L),
List = L.

wstaw(Head, El, [X0,X1|T], List) :-
%X1 \= [],
dodaj_na_koniec(Head, [X0], L),
wstaw(L, El, [X1|T], List).

wstaw(Head, El, [X0], List) :-
El =< X0,
dodaj_na_koniec(Head, [X0,El], L),
List = L.

wstaw(Head, El, [X0], List) :-
dodaj_na_koniec(Head, [El,X0], L),
 List = L.

insertion_sort([],[]).
insertion_sort([X],[X]).
insertion_sort(List, Sorted) :-
  sort(List, [], Sorted).

sort([], Sorted, Sorted).
sort([X], New, Sorted) :-
  dodaj_do_listy_we_wlasciwym_miejscu(X, New, L),
  sort([], L, Sorted).

sort([X0|T], New, Sorted) :-
  dodaj_do_listy_we_wlasciwym_miejscu(X0, New, L),
  sort(T, L, Sorted).
