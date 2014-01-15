/*  Part of SWI-Prolog

    Author:        Edison Mera
    E-mail:        efmera@gmail.com
    WWW:           http://www.swi-prolog.org
    Copyright (C): 2013, Process Design Center, Breda, The Netherlands.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    As a special exception, if you link this library with other files,
    compiled with a Free Software compiler, to produce an executable, this
    library does not by itself cause the resulting executable to be covered
    by the GNU General Public License. This exception does not however
    invalidate any other reasons why the executable file might be covered by
    the GNU General Public License.
*/

%% Migrated from Ciao to SWI-Prolog

:- package(basicmodes).
:- use_module(engine(hiord_rt)).

:- op(500,  fx,(?)).
:- op(500,  fx,(@)).

%% "ISO-like" modes
:- modedef '+'(A) : nonvar(A).
:- modedef '-'(A) : var(A).
:- modedef '?'(_).
:- modedef '@'(A) + not_further_inst(A).

%% Useful input-output modes
:- modedef in(A)  : ground(A) => ground(A).
:- modedef out(A) : var(A)    => ground(A).
:- modedef go(A)              => ground(A).

% :- push_prolog_flag(read_hiord,on).

%% Parametric versions of above
:- modedef '+'(A,X) :: call(X, A) : nonvar(A).
:- modedef '-'(A,X) :: call(X, A) : var(A).
:- modedef '?'(A,X) :: call(X, A).
:- modedef '@'(A,X) :: call(X, A) + not_further_inst(A).
:- modedef in(A,X)  :: call(X, A) : ground(A) => ground(A).
:- modedef out(A,X) :: call(X, A) : var(A)    => ground(A).
:- modedef go(A,X)  :: call(X, A)             => ground(A).

% :- pop_prolog_flag(read_hiord).
