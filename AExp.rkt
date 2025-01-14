;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-beginner-abbr-reader.ss" "lang")((modname AExp) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;; An Arithmetic Expression (AExp) is one of:
;; * Num
;; * OpNode


(define-struct opnode (op args))
;; An OpNode (operator node) is a
;; (make-opnode (anyof '* '+) (listof AExp)).


;; (eval exp) evaluates the arithmetic expression exp.
;; Examples:
(check-expect (eval 5) 5)
(check-expect (eval (make-opnode '+ (list 1 2 3 4))) 10)
(check-expect (eval (make-opnode '* (list 2 3 4))) 24)
(check-expect (eval (make-opnode '+ (list 1 (make-opnode '* (list 2 3)) 3))) 10)
;; AExp -> Num
(define (eval exp)
  (cond
    [(number? exp) exp]
    [(opnode? exp) (apply (opnode-op exp) (opnode-args exp))]
    )
  )


;; (apply op args) applies the arithmetic operator op to args.
;; Examples:
(check-expect (apply '+ (list 1 2 3 4)) 10)
(check-expect (apply '* (list 2 3 4)) 24)
(check-expect (apply '+ (list 1 (make-opnode '* (list 2 3)))) 7)
(check-expect (apply '+ (list )) 0)
(check-expect (apply '* (list )) 1)
;; (anyof '+ '*) (listof AExp) -> Num
(define (apply op args)
  (cond
    [(empty? args)
     (cond
       [(symbol=? op '+) 0]
       [(symbol=? op '*) 1])]
    [(symbol=? op '+) (+ (eval (first args)) (apply op (rest args)))]
    [(symbol=? op '*) (* (eval (first args)) (apply op (rest args)))]
    )
  )
