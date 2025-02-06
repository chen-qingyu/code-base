;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname number-to-list) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define (number->list n) (map string->number (map list->string (map (lambda (c) (cons c empty)) (string->list (number->string n))))))

(define (get-digit n) (cond [(zero? n) empty] [else (cons (remainder n 10) (get-digit (quotient n 10)))]))

(number->list 12345)
(number->list 54321)
(number->list 0)
(number->list 10086)
(number->list 999999999999999)

(get-digit 12345)
