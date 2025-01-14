#lang racket

(define (list-contains list data)
  (cond [(empty? list) false]
        [(eq? data (car list)) true]
        [else (list-contains (cdr list) data)]))

(define (list-remove list data)
  (cond [(empty? list) list]
        [(eq? data (car list)) (cdr list)]
        [else (cons (car list) (list-remove (cdr list) data))]))

(define (list-insert list data index)
  (cond [(zero? index) (cons data list)]
        [else (cons (car list) (list-insert (cdr list) data (- index 1)))]))

(define (list-size list)
  (cond [(empty? list) 0]
        [else (+ 1 (list-size (cdr list)))]))

(list-contains '(1 2 3) 1)
(list-contains '(1 2 3) 0)

(list-remove '(1 2 3) '1)
(list-remove '(1 2 3) '2)
(list-remove '(1 2 3) '3)
(list-remove '(1 2 3) '4)

(list-insert '() 1 0)
(list-insert '(1) 2 1)
(list-insert '(1 2) 3 2)
(list-insert '(1 2) 3 1)
(list-insert '(1 2) 3 0)

(list-size '())
(list-size '(1))
(list-size '(1 2))

; #t
; #f
; '(2 3)
; '(1 3)
; '(1 2)
; '(1 2 3)
; '(1)
; '(1 2)
; '(1 2 3)
; '(1 3 2)
; '(3 1 2)
; 0
; 1
; 2
