% Solve Sudoku problems using Prolog

:- use_module(library(clpfd)). % for `all_different` and `ins`

sudoku(Puzzle, Solution) :-
    Solution = Puzzle,

    Solution = [S11, S12, S13, S14,
                S21, S22, S23, S24,
                S31, S32, S33, S34,
                S41, S42, S43, S44],

    Solution ins 1 .. 4,

    all_different([S11, S12, S13, S14]), % Row1
    all_different([S21, S22, S23, S24]), % Row2
    all_different([S31, S32, S33, S34]), % Row3
    all_different([S41, S42, S43, S44]), % Row4

    all_different([S11, S21, S31, S41]), % Col1
    all_different([S12, S22, S32, S42]), % Col2
    all_different([S13, S23, S33, S43]), % Col3
    all_different([S14, S24, S34, S44]), % Col4

    all_different([S11, S12, S21, S22]), % Square1
    all_different([S13, S14, S23, S24]), % Square2
    all_different([S31, S32, S41, S42]), % Square3
    all_different([S33, S34, S43, S44]). % Square4

% Output complete results without truncation.
:- set_prolog_flag(answer_write_options, [max_depth(0)]).

% ?- sudoku([_, _, 2, 3, _, _, _, _, _, _, _, _, 3, 4, _, _], Solution).
% Solution = [4,1,2,3,2,3,4,1,1,2,3,4,3,4,1,2].
