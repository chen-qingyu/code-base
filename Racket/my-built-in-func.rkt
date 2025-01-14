#lang racket


;; (my-len l) Returns the number of elements in list.

;; my-len: (listof Any) -> Num
(define (my-len l)
  (cond
    [(empty? l) 0]
    [else (+ 1 (my-len (rest l)))]))

; Tail Recursion version
(define (my-len-TR l)
  (define (iter l len)
    (cond
      [(empty? l) len]
      [else (iter (rest l) (+ len 1))]))
  (iter l 0))

;; Examples:
(my-len '(1 2 3 4)); => 4
(my-len-TR '(1 2 3 4)); => 4


;; (my-map f l) Constructs a new list by applying a function to each item on list. 

;; my-map: func (listof Any) -> (listof Any)
(define (my-map f l)
  (cond
    [(empty? l) empty]
    [else (cons (f (first l)) (my-map f (rest l)))]))

; Tail Recursion version
(define (my-map-TR f l)
  (define (iter l backward-result)
    (cond
      [(empty? l) (reverse backward-result)]
      [else (iter (rest l) (cons (f (first l)) backward-result))]))
  (iter l empty))

;; Examples:
(my-map string-upcase '("ready" "set" "go")); => '("READY" "SET" "GO")
(my-map-TR string-upcase '("ready" "set" "go")); => '("READY" "SET" "GO")


;; (my-filter p? l) Constructs a list from all those items on a list for which the predicate holds.

;; my-filter: func (listof Any) -> (listof Any)
(define (my-filter p? l)
  (cond
    [(empty? l) empty]
    [(p? (first l)) (cons (first l) (my-filter p? (rest l)))]
    [else (my-filter p? (rest l))]))

;; Examples:
(my-filter odd? '(0 1 2 3 4 5 6 7 8 9)); => '(1 3 5 7 9)
(my-filter even? '(0 1 2 3 4 5 6 7 8 9)); => '(0 2 4 6 8)


;; (my-min l) Determines the smallest number.

;; my-min: (listof Num) -> Num
(define (my-min l)
  (cond
    [(empty? (rest l)) (first l)]
    [(< (first l) (my-min (rest l))) (first l)]
    [else (my-min (rest l))]))

;; Examples:
(my-min '(1 2 3 4)); => 1


;; (my-max l) Determines the largest number.

;; my-max: (listof Num) -> Num
(define (my-max l)
  (cond
    [(empty? (rest l)) (first l)]
    [(> (first l) (my-max (rest l))) (first l)]
    [else (my-max (rest l))]))

;; Examples:
(my-max '(1 2 3 4)); => 4


;; (my-sum l) Returns the summation of elements in list.

;; my-sum: (listof Num) -> Num
(define (my-sum l)
  (cond
    [(empty? l) 0]
    [else (+ (first l) (my-sum (rest l)))]))

;; Examples:
(my-sum '(1 2 3 4)); => 10


;; (my-index l n) Extracts the n-th element from list. 

;; my-index: (listof Any) Num -> Any
(define (my-index l n)
  (cond
    [(zero? n) (first l)]
    [else (my-index (rest l) (- n 1))]))

;; Examples:
(my-index '(1 2 3 4) 3); => 4

