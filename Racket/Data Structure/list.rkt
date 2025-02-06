#lang racket

(require rackunit)


(define (list-at list index)
  (cond [(or (null? list) (negative? index)) null]
        [(zero? index) (car list)]
        [else (list-at (cdr list) (- index 1))]))

(define (list-size list)
  (cond [(empty? list) 0]
        [else (+ 1 (list-size (cdr list)))]))

(define (list-contains list item)
  (cond [(empty? list) false]
        [(eq? item (car list)) true]
        [else (list-contains (cdr list) item)]))

(define (list-insert list index item)
  (cond [(zero? index) (cons item list)]
        [else (cons (car list) (list-insert (cdr list) (- index 1) item))]))

(define (list-remove list item)
  (cond [(empty? list) list]
        [(eq? item (car list)) (cdr list)]
        [else (cons (car list) (list-remove (cdr list) item))]))


(check-equal? (list-at '(1 2 3) 0) 1)
(check-equal? (list-at '(1 2 3) 2) 3)
(check-equal? (list-at '(1 2 3) 3) null)

(check-equal? (list-size '()) 0)
(check-equal? (list-size '(1)) 1)
(check-equal? (list-size '(1 2)) 2)

(check-equal? (list-contains '(1 2 3) 1) #t)
(check-equal? (list-contains '(1 2 3) 0) #f)

(check-equal? (list-insert '() 0 1) '(1))
(check-equal? (list-insert '(1 2) 2 3) '(1 2 3))
(check-equal? (list-insert '(1 2) 1 3) '(1 3 2))
(check-equal? (list-insert '(1 2) 0 3) '(3 1 2))

(check-equal? (list-remove '(1 2 3) 1) '(2 3))
(check-equal? (list-remove '(1 2 3) 2) '(1 3))
(check-equal? (list-remove '(1 2 3) 3) '(1 2))
(check-equal? (list-remove '(1 2 3) 4) '(1 2 3))
