;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname intermediate) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
#|;; Example 1
(define x 5)

(define (fun a)
  (local [(define x 3)] (+ a x)))

(fun 4)


;; Example 2
(define (t-area a b c)
  (local
    [(define s (/ (+ a b c) 2))]
    (sqrt (* s (- s a) (- s b) (- s c)))))

(t-area 3 4 5)

;; Example 3
(define (foo x)
  (local
    [(define a (+ x x))
     (define b (* x x))
     (define c (+ a b))]
    (+ a b c x)))

(foo 5)

;; Example 4
(define (foo x y)
  (+ (local
       [(define x y)
        (define z (+ x y))]
       (+ x z)) x))

(foo 2 3)
|#

;; Example 5
(check-expect (norm '(4 2 14)) '(0.2 0.1 0.7))
(check-expect (norm empty) empty)
; norm: (listof Num) -> (listof Num)
(define (norm l)
  (local
    [; sum: (listof Num) -> Num
     (define (sum l)
       (cond
         [(empty? l) 0]
         [else (+ (first l) (sum (rest l)))]))

     ; div-lst: (listof Num) Num -> (listof Num)
     (define (div-lst l n)
       (cond
         [(empty? l) empty]
         [else (cons (/ (first l) n) (div-lst (rest l) n))]))]

    (div-lst l (sum l))))

