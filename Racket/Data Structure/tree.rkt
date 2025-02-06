#lang racket

(require rackunit)


(define (tree-find tree item)
  (define (root-data node) (car node))
  (define (tree-left node) (car (cdr node)))
  (define (tree-right node) (car (cdr (cdr node))))
  (cond [(empty? tree) null]
        [(eq? item (root-data tree)) item]
        [(< item (root-data tree)) (tree-find (tree-left tree) item)]
        [(> item (root-data tree)) (tree-find (tree-right tree) item)]))


(check-equal? (tree-find '() 1) null)
(check-equal? (tree-find '(2 (1 () ()) (3 () ())) 1) 1)
(check-equal? (tree-find '(2 (1 () ()) (3 () ())) 2) 2)
(check-equal? (tree-find '(2 (1 () ()) (3 () ())) 3) 3)
(check-equal? (tree-find '(2 (1 () ()) (3 () ())) 4) null)
(check-equal? (tree-find '(2 (1 () ()) (3 () (4 () ()))) 4) 4)
