#lang racket

;; node: '(data left right)

(define (get-data node) (car node))

(define (get-left node) (car (cdr node)))

(define (get-right node) (car (cdr (cdr node))))

(define (tree-find node data)
  (cond [(empty? node) false]
        [(= data (get-data node)) true]
        [(< data (get-data node)) (tree-find (get-left node) data)]
        [(> data (get-data node)) (tree-find (get-right node) data)]))

(tree-find '()
           1)

(tree-find '(2
             (1 () ()) (3 () ()))
           1)

(tree-find '(2
             (1 () ()) (3 () ()))
           2)

(tree-find '(2
             (1 () ()) (3 () ()))
           3)

(tree-find '(2
             (1 () ()) (3 () ()))
           4)

(tree-find '(2
             (1 () ()) (3 ()
                          (4 () ())))
           4)

; #f
; #t
; #t
; #t
; #f
; #t
