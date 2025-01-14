#lang racket

 
(let*
    (
     [x (random 4)]
     [o (random 4)]
     [diff (number->string (abs (- x o)))]
     )
  (cond
    [(> x o) (string-append "X wins by " diff)]
    [(> o x) (string-append "O wins by " diff)]
    [else "cat's game"]
    )
  )
