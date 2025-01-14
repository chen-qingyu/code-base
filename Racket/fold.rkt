;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname fold) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
#|
;; (foldl func init lst)
(foldl + 0 '(1 2 3 4))

(foldl * 1 '(1 2 3 4))

(foldl + 0 '(1 2 3 4) '(1 2 3 4))

#|
> (cons 1 '())
(list 1)
> (cons 2 (list 1))
(list 2 1)
> (cons 3 (list 2 1))
(list 3 2 1)
> (cons 4 (list 3 2 1))
(list 4 3 2 1)
|#
(foldl cons '() '(1 2 3 4))

(foldl (lambda (a b) (cons a b)) '() '(1 2 3 4))

;; v: 从左到右遍历列表。l：上一次的运算结果
#|
> (cons 11 '())
(list 11)
> (cons 12 (list 11))
(list 12 11)
> (cons 13 (list 12 11))
(list 13 12 11)
> (cons 14 (list 13 12 11))
(list 14 13 12 11)
|#
(foldl (lambda (v l) (cons (+ 10 v) l)) '() '(1 2 3 4))
|#

;; 向量相乘
;; vector-mul: (listof Num) (listof Num) -> (listof Num)
(define (vector-mul l1 l2)
  (cond
    [(empty? l1) empty]
    [else (cons (* (first l1) (first l2)) (vector-mul (rest l1) (rest l2)))]))
(check-expect (vector-mul '(1 2 3 4) '(2 2 2 2)) (list 2 4 6 8))

#|
> (append (list (* 4 2)) empty)
(list 8)
> (append (list (* 3 2)) (list 8))
(list 6 8)
> (append (list (* 2 2)) (list 6 8))
(list 4 6 8)
> (append (list (* 1 2)) (list 4 6 8))
(list 2 4 6 8)
|#
(foldr (lambda (a b l) (append (list (* a b)) l)) empty '(1 2 3 4) '(2 2 2 2))

(build-list 22 add1)
(build-list 3 (lambda (j) (+ j 3)))
(build-list 5 (lambda (i) (build-list 5 (lambda (j) (if (= i j) 1 0)))))
