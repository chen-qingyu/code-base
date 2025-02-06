#lang racket/base

(require racket/trace)


;; Calc factorial, normal recursion.
(define (factorial n)
  (if (= n 0)
      1
      (* n (factorial (- n 1)))))


;; Calc factorial, tail recursion.
(define (factorial-tail n acc)
  (if (not (= n 0))
      (factorial-tail (- n 1) (* n acc))
      acc))


(trace factorial)
(trace factorial-tail)
(factorial 6)
(factorial-tail 6 1)
